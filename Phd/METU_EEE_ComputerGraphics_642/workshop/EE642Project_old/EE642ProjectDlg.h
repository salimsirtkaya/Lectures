// EE642ProjectDlg.h : header file
//

#if !defined(AFX_EE642PROJECTDLG_H__C652D27B_8226_404B_8F2F_CFDE626209D9__INCLUDED_)
#define AFX_EE642PROJECTDLG_H__C652D27B_8226_404B_8F2F_CFDE626209D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RenderingArea.h"
#include "menuarea.h"
#include "642Manager.h"
/////////////////////////////////////////////////////////////////////////////
// CEE642ProjectDlg dialog

class CEE642ProjectDlg : public CDialog, public C642Manager
{
// Construction
public:
	CEE642ProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEE642ProjectDlg)
	enum { IDD = IDD_EE642PROJECT_DIALOG };
	CRenderingArea	m_renderArea;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEE642ProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEE642ProjectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMenuArea m_menuArea;
	void AddMenu();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EE642PROJECTDLG_H__C652D27B_8226_404B_8F2F_CFDE626209D9__INCLUDED_)
