// MovingCamSimulation.h : main header file for the MOVINGCAMSIMULATION application
//

#if !defined(AFX_MOVINGCAMSIMULATION_H__2195B518_1686_4B32_B956_9D72ED96A7F0__INCLUDED_)
#define AFX_MOVINGCAMSIMULATION_H__2195B518_1686_4B32_B956_9D72ED96A7F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMovingCamSimulationApp:
// See MovingCamSimulation.cpp for the implementation of this class
//

class CMovingCamSimulationApp : public CWinApp
{
public:
	CMovingCamSimulationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovingCamSimulationApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMovingCamSimulationApp)
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

#endif // !defined(AFX_MOVINGCAMSIMULATION_H__2195B518_1686_4B32_B956_9D72ED96A7F0__INCLUDED_)
