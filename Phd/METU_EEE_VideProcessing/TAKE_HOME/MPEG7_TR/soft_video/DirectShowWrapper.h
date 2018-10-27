/**************************************************************

DirectShowWrapper.h

Header file for class CDirectShowWrapper

Two DirectShow header files, dshow.h and qedit.h must be
#included before this header.

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Yagiz Yasaroglu
TUBITAK BILTEN
November 20, 2002

--

This file ("DirectShowWrapper.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
DirectShowWrapper.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with DirectShowWrapper.h 
or the use or other dealings in DirectShowWrapper.h.

DirectShow is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/


#ifndef __YY_DIRECTSHOWWRAPPER_H
#define __YY_DIRECTSHOWWRAPPER_H

#include "MpegFile.h"
#include <dshow.h>
#include <qedit.h>


/**************************************************
* class DirectShowWrapper                         *
**************************************************/

class CDirectShowWrapper
{

#define CHECK_FAILED_DSW(aa) { if(FAILED(m_hr = aa)) return m_hr; }
#define SAFE_RELEASE_DSW(aa) { if (aa) aa->Release(); aa = NULL; }
#define VIDEO_START_FRAME 12

protected:
	// DirectShow interface pointers.
	IMediaPosition	* m_pMedPos;
	IMediaSeeking   * m_pSeek;
	IGraphBuilder   * m_pGraph;
	IMediaControl   * m_pMediaControl;
	IVideoWindow    * m_pVidWin;
	IBaseFilter     * m_pF;
	IBaseFilter     * m_pF2;
	IBasicVideo	    * m_pBasVid;
	IMediaEvent     * m_pEvent;
	ISampleGrabber  * m_pVideoGrab;

	OAHWND m_owner;

	// Return value.
	HRESULT m_hr;

	BOOL m_bSetUp;
	FILTER_STATE m_filterState;
	REFERENCE_TIME m_currentFrame;
	CMpegFile m_mpegFile;

	HRESULT MakeFilterGraph();

public:
	CDirectShowWrapper();
	CDirectShowWrapper(const CMpegFile & fileName);
	CDirectShowWrapper(const char * fileName);
	~CDirectShowWrapper();

	HRESULT OpenFile(const char * fileName);

	HRESULT CreateFilterGraph();
	HRESULT DestroyFilterGraph();
	
	HRESULT AttachMpegFile(const CMpegFile & mpegFile);
	HRESULT GetMpegFile(CMpegFile & mpegFile);
	
	HRESULT VideoSeekTo(REFERENCE_TIME seekPos);
	HRESULT VideoRun(REFERENCE_TIME seekPos = -1);
	HRESULT VideoPause(REFERENCE_TIME & lastFrame);
	HRESULT VideoStop();
	HRESULT GrabCurrentFrame(unsigned char * & image,long &bitmapSize,long& w,long& h);

	HRESULT ShowWindow(BOOL bShow = TRUE);
	HRESULT SetWindowPosition(long left, 
							  long top, 
							  long width, 
							  long height);
	HRESULT SetOwnerWindow(OAHWND hWnd);
	HRESULT SetOwnerAndResize(OAHWND hWnd);
	HRESULT SetWindowSize(int type);

	HRESULT GetCurrentFrame(REFERENCE_TIME & currentFrame);
	HRESULT GetState(FILTER_STATE & state);
};

#endif