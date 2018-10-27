// EE642Project.h : main header file for the EE642PROJECT application
//

#if !defined(AFX_EE642PROJECT_H__9EEF6A6D_8E64_4E1E_BE9F_DFB402AF0DBF__INCLUDED_)
#define AFX_EE642PROJECT_H__9EEF6A6D_8E64_4E1E_BE9F_DFB402AF0DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEE642ProjectApp:
// See EE642Project.cpp for the implementation of this class
//

class CEE642ProjectApp : public CWinApp
{
public:
	CEE642ProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEE642ProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEE642ProjectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EE642PROJECT_H__9EEF6A6D_8E64_4E1E_BE9F_DFB402AF0DBF__INCLUDED_)
