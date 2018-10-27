/**************************************************************

GdiplusWrapper.h

Header file for class CGdiplusWrapper

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Medeni Soysal			
TUBITAK BILTEN
November 20, 2002

--

This file ("GdiplusWrapper.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
GdiplusWrapper.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with GdiplusWrapper.h
or the use or other dealings in GdiplusWrapper.h.

GDI+ is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/

#if !defined(AFX_GDIPLUSWRAPPER_H__06961828_0E2C_4F51_B936_80B39E34FDE5__INCLUDED_)
#define AFX_GDIPLUSWRAPPER_H__06961828_0E2C_4F51_B936_80B39E34FDE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

#define BMP	1
#define JPG	2
#define GIF	3
#define PNG 4
#define TIFF 5

class CGdiplusWrapper
{
public:
	void InitializeBmp(CString fileName);
	BOOL LoadPixelData(BYTE*,Point);
	BOOL SaveAsType(int,CString);
	BYTE* GetPixels(BitmapData& bmpdata);
	BOOL Display(HWND, Rect);
	CGdiplusWrapper();
	CGdiplusWrapper(CString filename);
	virtual ~CGdiplusWrapper();
	Bitmap* m_pBmp;

private:
	Graphics* m_pGraph;
	Bitmap* m_pResim;

};


#endif // !defined(AFX_GDIPLUSWRAPPER_H__06961828_0E2C_4F51_B936_80B39E34FDE5__INCLUDED_)
