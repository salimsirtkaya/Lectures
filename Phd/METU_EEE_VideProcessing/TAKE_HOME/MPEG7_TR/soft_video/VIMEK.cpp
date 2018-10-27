// VIMEK.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VIMEK.h"
#include "VIMEKDlg.h"
#include "DirectShowWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVIMEKApp

BEGIN_MESSAGE_MAP(CVIMEKApp, CWinApp)
	//{{AFX_MSG_MAP(CVIMEKApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVIMEKApp construction

CVIMEKApp::CVIMEKApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVIMEKApp object

CVIMEKApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVIMEKApp initialization

BOOL CVIMEKApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	GdiplusStartupInput gdiplusstartupinput;
	GdiplusStartup (&m_gdiplusToken, &gdiplusstartupinput, NULL);

	CVIMEKDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if (m_bThreadAlive)
			dlg.myThread->SuspendThread();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
		if (m_bThreadAlive)
			dlg.myThread->SuspendThread();
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CVIMEKApp::ExitInstance() 
{
	GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}