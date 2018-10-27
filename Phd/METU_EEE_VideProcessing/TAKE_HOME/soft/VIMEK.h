// VIMEK.h : main header file for the VIMEK application
//

#if !defined(AFX_VIMEK_H__1ACA9B8C_4258_47FB_9704_F4D60DA70372__INCLUDED_)
#define AFX_VIMEK_H__1ACA9B8C_4258_47FB_9704_F4D60DA70372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVIMEKApp:
// See VIMEK.cpp for the implementation of this class
//

class CVIMEKApp : public CWinApp
{
public:
	CVIMEKApp();

	BOOL m_bThreadAlive;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVIMEKApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVIMEKApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	ULONG_PTR m_gdiplusToken;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIMEK_H__1ACA9B8C_4258_47FB_9704_F4D60DA70372__INCLUDED_)
