/**************************************************************

DirectShowWrapper.cpp

Implementation file for class CDirectShowWrapper

Two DirectShow libraries, quartz.lib strmiids.lib must be 
linked with this file. quartz.dll and qedit.dll must also be
registered.

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Yagiz Yasaroglu
TUBITAK BILTEN
November 20, 2002

--

This file ("DirectShowWrapper.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
DirectShowWrapper.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with DirectShowWrapper.cpp
or the use or other dealings in DirectShowWrapper.cpp.

DirectShow is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/

// Replace the following header (stdafx.h)  
// with Windows standard headers if not 
// using pre-compiled headers.
#include "stdafx.h"

#include <dshow.h>
#include <qedit.h>
#include "directshowwrapper.h"
#include <math.h>

/**************************************************************

  class CDirectShowWrapper

  This class is a wrapper capable of basic Direct Show actions
  such as opening a file, playing, stopping, seeking and
  grabbing.

  quartz.lib and strmiids.lib should be linked too.

**************************************************************/


// Default constructor.
CDirectShowWrapper::CDirectShowWrapper()
{
	m_bSetUp = FALSE;
	m_currentFrame = 0;
	m_filterState = State_Stopped;

	m_pSeek = NULL;
	m_pGraph = NULL;
	m_pMediaControl = NULL;
	m_pVidWin = NULL;
	m_pF = NULL;
	m_pEvent = NULL;
	m_pVideoGrab = NULL;

	m_hr = E_FAIL;
}

// Alternate constructor.
CDirectShowWrapper::CDirectShowWrapper(const CMpegFile & mpegFile)
{
	m_bSetUp = FALSE;
	m_currentFrame = 0;
	m_filterState = State_Stopped;

	m_pSeek = NULL;
	m_pGraph = NULL;
	m_pMediaControl = NULL;
	m_pVidWin = NULL;
	m_pF = NULL;
	m_pEvent = NULL;
	m_pVideoGrab = NULL;

	m_hr = E_FAIL;

	m_mpegFile = mpegFile;

	CreateFilterGraph();
}

// Alternate constructor.
CDirectShowWrapper::CDirectShowWrapper(const char * fileName)
{
	m_bSetUp = FALSE;
	m_currentFrame = 0;
	m_filterState = State_Stopped;

	m_pSeek = NULL;
	m_pGraph = NULL;
	m_pMediaControl = NULL;
	m_pVidWin = NULL;
	m_pF = NULL;
	m_pEvent = NULL;
	m_pVideoGrab = NULL;

	m_hr = E_FAIL;

	m_mpegFile.SetFileName(fileName);

	CreateFilterGraph();
}

// Default destructor.
CDirectShowWrapper::~CDirectShowWrapper()
{
	if (m_bSetUp)
		DestroyFilterGraph();
}

//
// VideoSeekTo
//
// Seeks to the given frame.
//
HRESULT CDirectShowWrapper::VideoSeekTo(REFERENCE_TIME seekPos)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	CHECK_FAILED_DSW(m_pSeek->SetPositions(&seekPos,
									 AM_SEEKING_AbsolutePositioning,
									 &seekPos,
									 AM_SEEKING_AbsolutePositioning));

	
	long evCode;
	CHECK_FAILED_DSW(m_pMediaControl->Run());
	CHECK_FAILED_DSW(m_pEvent->WaitForCompletion(INFINITE, &evCode));

	CHECK_FAILED_DSW(m_pMediaControl->Pause());
	m_filterState = State_Paused;

	m_currentFrame = seekPos;

	return S_OK;
}

//
// VideoRun
//
// Plays the video, starting from the given frame.
// If no statrt frame is given starts from the 
// current frame.
//
HRESULT CDirectShowWrapper::VideoRun(REFERENCE_TIME seekPos /* = -1*/)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;
	if (m_filterState == State_Running)
		return S_OK;

	REFERENCE_TIME endTime = m_mpegFile.frameCount - 1;

	if (seekPos < 0)
		seekPos = m_currentFrame;
	
	CHECK_FAILED_DSW(m_pSeek->SetPositions(&seekPos,
										   AM_SEEKING_AbsolutePositioning,
										   &endTime,
										   AM_SEEKING_AbsolutePositioning));

	
	CHECK_FAILED_DSW(m_pMediaControl->Run());
	//long evCode;
	//CHECK_FAILED_DSW(m_pEvent->WaitForCompletion(INFINITE, &evCode));

	m_filterState = State_Running;

	return S_OK;
}

//
// VideoPause
//
// Pauses the video and returns the current frame number.
//
HRESULT CDirectShowWrapper::VideoPause(REFERENCE_TIME & lastFrame)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;
	if (m_filterState == State_Paused)
		return S_OK;

	CHECK_FAILED_DSW(m_pMediaControl->Pause());

	REFERENCE_TIME endPosition;
	CHECK_FAILED_DSW(m_pSeek->GetPositions(&lastFrame, &endPosition));

	m_currentFrame = lastFrame;
	m_filterState = State_Paused;

	return S_OK;
}

//
// VideoStop
//
// Stops the video and seeks to the start of the video.
//
HRESULT CDirectShowWrapper::VideoStop()
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;
	if (m_filterState == State_Stopped)
		return S_OK;

	CHECK_FAILED_DSW(m_pMediaControl->Stop());
	m_filterState = State_Stopped;

	CHECK_FAILED_DSW(VideoSeekTo(VIDEO_START_FRAME));

	return S_OK;
}

//
// CreateFilterGraph
//
// Calls MakeFilterGraph to create a filter graph and 
// open (render) the file that is currently selected.
//
HRESULT CDirectShowWrapper::CreateFilterGraph()
{
	m_hr = MakeFilterGraph();
	if (FAILED(m_hr))
		DestroyFilterGraph();

	return m_hr;
}

//
// MakeFilterGraph
//
// Creates a filter graph and opens (renders) the file
// that is currently selected.
//
HRESULT CDirectShowWrapper::MakeFilterGraph()
{
	if (m_bSetUp)
		DestroyFilterGraph();

	if (!m_mpegFile.GetFileName())
		return E_INVALIDARG;

	WCHAR wFile[255];

	// Convert filename to proper format.
	#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, 0, m_mpegFile.GetFileName(), -1, wFile, MAX_PATH);
	#else
		lstrcpy(wFile, mpegFile.GetFileName());
	#endif
	
	// Initialize DirectX.	
	CoInitialize(NULL);

	// Create the filter graph manager.
	CHECK_FAILED_DSW(CoCreateInstance(CLSID_FilterGraph,
								  NULL, 
								  CLSCTX_INPROC,
								  IID_IGraphBuilder, 
								  (void **)&m_pGraph));
    
	// Query for the interfaces exposed by the graph manager.
	CHECK_FAILED_DSW(m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl));
	CHECK_FAILED_DSW(m_pGraph->QueryInterface(IID_IVideoWindow, (void **)&m_pVidWin));
	CHECK_FAILED_DSW(m_pGraph->QueryInterface(IID_IMediaSeeking, (void **)&m_pSeek));
	CHECK_FAILED_DSW(m_pGraph->QueryInterface(IID_IMediaEvent, (void **)&m_pEvent));

	// Create the video grabber object, get interface and connect it to graph.
	CHECK_FAILED_DSW(CoCreateInstance(CLSID_SampleGrabber,
								  NULL,
								  CLSCTX_INPROC_SERVER,
								  IID_IBaseFilter,
								  (LPVOID *)&m_pF));
	CHECK_FAILED_DSW(m_pF->QueryInterface(IID_ISampleGrabber, (void **)&m_pVideoGrab));
	CHECK_FAILED_DSW(m_pGraph->AddFilter(m_pF, L"VideoGrabber"));

	// Set media type for video grabber interface.
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo; 
	CHECK_FAILED_DSW(m_pVideoGrab->SetMediaType(&mt));

	// Build graph.
	CHECK_FAILED_DSW(m_pGraph->RenderFile(wFile, NULL));

	// Get mpeg info.
	CHECK_FAILED_DSW(m_pVideoGrab->GetConnectedMediaType(&mt)); 

	// Get a pointer to the video header.
	VIDEOINFOHEADER *m_pVideoHeader = (VIDEOINFOHEADER*)mt.pbFormat;

	// Obtain the width and height of the video.
	m_mpegFile.width = m_pVideoHeader->bmiHeader.biWidth;
	m_mpegFile.height = m_pVideoHeader->bmiHeader.biHeight;
	if (!(m_mpegFile.width || m_mpegFile.height))
		return E_FAIL;

	// Get the frame rate.
	m_mpegFile.framesPerSecond = (float) floor(1.0/(100e-9 * m_pVideoHeader->AvgTimePerFrame));
	if (m_mpegFile.framesPerSecond <= 0)
		return E_FAIL;
	
	// Set video time format to frames.
	CHECK_FAILED_DSW(m_pSeek->SetTimeFormat(&TIME_FORMAT_FRAME));
	
	// Obtain the duration of the video
	LONGLONG a;
	CHECK_FAILED_DSW(m_pSeek->GetDuration(&a));
	m_mpegFile.frameCount = a;
	if (!m_mpegFile.frameCount)
		return E_FAIL;

	//CHECK_FAILED_DSW(m_pVidWin->put_AutoShow(OATRUE));

	m_bSetUp = TRUE;

	return S_OK;
}

//
// DestroyFilterGraph
//
// Safely destroys the filter graph.
//
HRESULT CDirectShowWrapper::DestroyFilterGraph()
{
	if (!m_bSetUp)
		return S_OK;

	if (m_pVidWin) m_pVidWin->put_Visible(OAFALSE);
	if (m_pVidWin) m_pVidWin->put_Owner(NULL);   
	if (m_pMediaControl) m_pMediaControl->Stop();

	SAFE_RELEASE_DSW(m_pMediaControl);
	SAFE_RELEASE_DSW(m_pVidWin);
	SAFE_RELEASE_DSW(m_pGraph);
	SAFE_RELEASE_DSW(m_pF);
	SAFE_RELEASE_DSW(m_pVideoGrab);
	SAFE_RELEASE_DSW(m_pSeek);
	SAFE_RELEASE_DSW(m_pEvent);

	CoUninitialize();

	m_bSetUp = FALSE;

	return S_OK;
}

//
// AttachMpegFile
//
// Attaches an mpeg file to the class. Call this
// function with the desired video file before 
// creating a filter graph.
//
HRESULT CDirectShowWrapper::AttachMpegFile(const CMpegFile & mpegFile)
{
	if (m_bSetUp)
		return E_FAIL;

	m_mpegFile = mpegFile;
	return S_OK;
}

//
// GetMpegFile
//
// Returns the attached mpeg file.
//
HRESULT CDirectShowWrapper::GetMpegFile(CMpegFile & mpegFile)
{
	mpegFile = m_mpegFile;
	return S_OK;
}

//
// GrabCurrentFrame
//
// Copies the contents of the current frame into the given buffer.
// The video must be paused before this function is called.
//
// The function allocates the buffer to be returned.
//
HRESULT CDirectShowWrapper::GrabCurrentFrame(unsigned char * & image,long &bitmapSize,long& w,long& h)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	// Return if not paused.
	FILTER_STATE filterState;
	CHECK_FAILED_DSW(m_pMediaControl->GetState(INFINITE, (long *) &filterState));
	if (filterState == State_Running)
		return E_INVALIDARG;

	// Configure sample grabber.
	CHECK_FAILED_DSW(m_pVideoGrab->SetBufferSamples(TRUE));
	CHECK_FAILED_DSW(m_pVideoGrab->SetOneShot(TRUE));

	// Seek to current frame.
	CHECK_FAILED_DSW(m_pSeek->SetPositions(&m_currentFrame,
										 AM_SEEKING_AbsolutePositioning,
										 &m_currentFrame,
										 AM_SEEKING_AbsolutePositioning));

	// Run the graph and wait for completion.
	CHECK_FAILED_DSW(m_pMediaControl->Run());
	long evCode;
	CHECK_FAILED_DSW(m_pEvent->WaitForCompletion(INFINITE, &evCode));
	CHECK_FAILED_DSW(m_pMediaControl->Pause());

	// copy the information contained in the current buffer to the 
	// location pointed to by the data_of_bitmap pointer.
/***	long*/ bitmapSize = m_mpegFile.height * m_mpegFile.width;
/*_______________________________________*/
	w=m_mpegFile.width;
	h=m_mpegFile.height;


	image = (unsigned char *) malloc(3 * bitmapSize * sizeof(unsigned char));
	if (!image)
		return E_OUTOFMEMORY;
	CHECK_FAILED_DSW(m_pVideoGrab->GetCurrentBuffer(&bitmapSize, (long *)image));

	CHECK_FAILED_DSW(m_pVideoGrab->SetBufferSamples(FALSE));
	CHECK_FAILED_DSW(m_pVideoGrab->SetOneShot(FALSE));

	return S_OK;
}

//
// ShowWindow
//
// Makes the video vindow visible.
//
HRESULT CDirectShowWrapper::ShowWindow(BOOL bShow /*= TRUE*/)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	if (bShow)
	{
		//CHECK_FAILED_DSW(m_pVidWin->put_AutoShow(OATRUE));
		CHECK_FAILED_DSW(m_pVidWin->put_Visible(OATRUE));
	}
	else
	{
		//CHECK_FAILED_DSW(m_pVidWin->put_AutoShow(OAFALSE));
		CHECK_FAILED_DSW(m_pVidWin->put_Visible(OAFALSE));
	}

	return S_OK;
}

//
// SetWindowPosition
//
// Sets the position of the video vindow
// relative to its owner.
//
HRESULT CDirectShowWrapper::SetWindowPosition(long left, 
											  long top, 
											  long width, 
											  long height)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	return m_pVidWin->SetWindowPosition(left,
										top,
										width,
										height);
}

//
// SetOwnerWindow
//
// Sets the owner of the video vindow.
//
HRESULT CDirectShowWrapper::SetOwnerWindow(OAHWND hWnd)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	CHECK_FAILED_DSW(m_pVidWin->put_Owner(hWnd));
	CHECK_FAILED_DSW(m_pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS));

	m_owner = hWnd;

	return S_OK;
}

//
// SetWindowSize
//
// Sets the size of the video vindow
// relative to its owner. Has four
// modes.
//
// 0: Scale video window to match parent window.
// 1: Don't scale video window.
// 2: Compress if bigger than parent window.
// 3: Strech to fit if smaller than parent window.
//
HRESULT CDirectShowWrapper::SetWindowSize(int type)
{
	_ASSERT (m_owner != 0x0000);

	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	RECT bigRect;
	RECT vidRect;
	
	::GetClientRect((HWND)m_owner, &bigRect);

	switch (type)
	{
	case 0:
		// Scale the video window to match the
		// size of the owner window.
		vidRect.top = bigRect.top;
		vidRect.bottom = bigRect.bottom;
		vidRect.left = bigRect.left;
		vidRect.right = bigRect.right;
		break;
	case 1:
		// Don't scale the video window,
		// and center it in owner window's
		// client area.
		vidRect.top = (bigRect.bottom - m_mpegFile.height) / 2;
		vidRect.bottom = m_mpegFile.height;
		vidRect.left = (bigRect.right - m_mpegFile.width) / 2;
		vidRect.right = m_mpegFile.width;
		break;
	case 2:
		// Compress the video window if it is
		// bigger than the owner window's 
		// client area, but don't stretch it
		// otherwise. Center the video window.
		if (bigRect.bottom > m_mpegFile.height)
		{
			vidRect.top = (bigRect.bottom - m_mpegFile.height) / 2;
			vidRect.bottom = m_mpegFile.height;
		}
		else
		{
			vidRect.top = bigRect.top;
			vidRect.bottom = bigRect.bottom;
		}

		if (bigRect.right > m_mpegFile.width)
		{
			vidRect.left = (bigRect.right - m_mpegFile.width) / 2;
			vidRect.right = m_mpegFile.width;
		}
		else
		{
			vidRect.left = bigRect.left;
			vidRect.right = bigRect.right;
		}
		break;
	case 3:
		// Stretch video window to fit the
		// client area if it is smaller than it.
		// Don't compress otherwise. Center the
		// video window.
		if (bigRect.bottom < m_mpegFile.height)
		{
			vidRect.top = (bigRect.bottom - m_mpegFile.height) / 2;
			vidRect.bottom = m_mpegFile.height;
		}
		else
		{
			vidRect.top = bigRect.top;
			vidRect.bottom = bigRect.bottom;
		}

		if (bigRect.right < m_mpegFile.width)
		{
			vidRect.left = (bigRect.right - m_mpegFile.width) / 2;
			vidRect.right = m_mpegFile.width;
		}
		else
		{
			vidRect.left = bigRect.left;
			vidRect.right = bigRect.right;
		}
		break;
	}

	CHECK_FAILED_DSW(m_pVidWin->SetWindowPosition (vidRect.left, 
												   vidRect.top, 
												   vidRect.right, 
												   vidRect.bottom));

	return S_OK;
}

//
// SetOwnerAndResize
//
// Sets the owner window and resizes the video window
// so that is  compressed if it doesn't fit, but it
// is not strecthed to fit.
//
HRESULT CDirectShowWrapper::SetOwnerAndResize(OAHWND hWnd)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	CHECK_FAILED_DSW(SetOwnerWindow(hWnd));

	CHECK_FAILED_DSW(SetWindowSize(2));

	return S_OK;
}


//
// GetCurrentFrame
//
// Returns the current frame number.
//
HRESULT CDirectShowWrapper::GetCurrentFrame(REFERENCE_TIME & currentFrame)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	if (FAILED(m_pSeek->GetCurrentPosition(&m_currentFrame)))
		return E_FAIL;

	currentFrame = m_currentFrame;

	return S_OK;
}

HRESULT CDirectShowWrapper::GetState(FILTER_STATE & state)
{
	if (!m_bSetUp)
		return CO_E_NOTINITIALIZED;

	HRESULT hr = m_pMediaControl->GetState(5000, (OAFilterState *) &m_filterState);	// Wait 5000 msecs for query to complete.

	if (FAILED(hr))
		return hr;

	state = m_filterState;

	return S_OK;
}

//
// OpenFile
//
// Attaches the given file name to the object
// and creates a filter graph.
//
HRESULT CDirectShowWrapper::OpenFile(const char * fileName)
{
	_ASSERT(fileName);

	CMpegFile mpegFile;
	mpegFile.SetFileName(fileName);

	CHECK_FAILED_DSW(AttachMpegFile(mpegFile));
	CHECK_FAILED_DSW(CreateFilterGraph());

	return S_OK;
}


