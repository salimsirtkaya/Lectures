/**************************************************************

GdiplusWrapper.cpp

Implementation file for class CGdiplusWrapper

GDI+ library gdiplus.lib must be linked with this file.

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Medeni Soysal			
TUBITAK BILTEN
November 20, 2002

--

This file ("GdiplusWrapper.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
GdiplusWrapper.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with GdiplusWrapper.cpp
or the use or other dealings in GdiplusWrapper.cpp.

GDI+ is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//These are standart windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "GdiplusWrapper.h"
#include <string.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
/*Above line is commented out since it redefines the new operator
and therefore causes error in debug version*/
#endif
//using namespace Gdiplus;
#include <gdiplus.h>
using namespace Gdiplus;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGdiplusWrapper::CGdiplusWrapper()
{
	m_pBmp = new Bitmap(10,10,PixelFormat24bppRGB);
}

CGdiplusWrapper::CGdiplusWrapper(CString filename)
{
	m_pBmp = new Bitmap(filename.AllocSysString());

}

CGdiplusWrapper::~CGdiplusWrapper()
{
	delete m_pBmp;
}

BOOL CGdiplusWrapper::Display(HWND hwnd, Rect target)
{
	HDC hdc = ::GetDC(hwnd);
	m_pGraph = new Graphics(hdc);
	Status result;
	result = (Status) m_pGraph->DrawImage(m_pBmp,target);
	delete m_pGraph;//This dynamic variable is free now.
	if (result == Ok) return 1;
	else return 0;
	
}


BYTE* CGdiplusWrapper::GetPixels(BitmapData& bmpdata)
//Don't forget to free pixels pointer when you are finished
{
	BYTE* pixels;
	int width,height;
	Rect rect(0,0,width=m_pBmp->GetWidth(),height=m_pBmp->GetHeight()); //Get all pixels of the image
	m_pBmp->LockBits(rect, ImageLockModeRead, PixelFormat24bppRGB, &bmpdata);
	
	
	if (bmpdata.Stride > 0){
		pixels = (BYTE*)malloc((bmpdata.Stride)*(height));//Allocate memory
		memcpy(pixels,
				(BYTE*)bmpdata.Scan0,
				((bmpdata.Stride)*(height)));//Copy temporary buffer into allocated memory
		m_pBmp->UnlockBits(&bmpdata);//free temporary buffer
		bmpdata.Scan0 = pixels;//set the pointer to the safe memory

	}

	else if (bmpdata.Stride < 0){
		pixels = (BYTE*)malloc((-bmpdata.Stride)*(height));//Allocate memory
		memcpy(pixels,
				(BYTE*)bmpdata.Scan0 - ((-bmpdata.Stride)*(height-1)),
				((-bmpdata.Stride)*(height)));//Copy temporary buffer into allocated memory
		m_pBmp->UnlockBits(&bmpdata);//free temporary buffer
		bmpdata.Scan0 = pixels + (-bmpdata.Stride)*(height-1);//set the pointer to the safe memory
	}
		
	return pixels;//Always top of the memory is returned(free it when you're finished with it)
}


BOOL CGdiplusWrapper::LoadPixelData(BYTE* pixels, Point dimensions)
{
	delete m_pBmp;

	int stride = 4-((dimensions.X*3) % 4);
	if (stride == 4)
		stride = 0;
	stride += dimensions.X*3;

	if (dimensions.Y < 0)
	{
		dimensions.Y *= -1; //Dimensions will be used as (+)ive
		pixels += (dimensions.Y-1)*stride;
		stride *= -1; //Stride (-)ive 
	}

	m_pBmp = new Bitmap(dimensions.X, dimensions.Y, stride, PixelFormat24bppRGB, pixels);

	if (m_pBmp) return 1;
	else return 0;


}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


BOOL CGdiplusWrapper::SaveAsType(int Type, CString filename)
{
	
	CLSID Encoder;

	if (Type == BMP) GetEncoderClsid(L"image/bmp",&Encoder);
	else if (Type == JPG) GetEncoderClsid(L"image/jpeg",&Encoder);
	else if (Type == GIF) GetEncoderClsid(L"image/gif",&Encoder);
	else if (Type == PNG) GetEncoderClsid(L"image/png",&Encoder);
	else if (Type == TIFF) GetEncoderClsid(L"image/tiff",&Encoder);
	
	Status res = m_pBmp->Save(filename.AllocSysString(),&Encoder,NULL);
	if (res == Ok) return 1;
	return 0;


}


