#if !defined(AFX_MOTIONPATHENTRANCEDLG_H__62103BC8_E1DD_4DB5_BD6F_60092DA4B7B3__INCLUDED_)
#define AFX_MOTIONPATHENTRANCEDLG_H__62103BC8_E1DD_4DB5_BD6F_60092DA4B7B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionPathEntranceDlg.h : header file
//
#include "afxtempl.h"
#include "auxiliaryClasses.h"

/////////////////////////////////////////////////////////////////////////////
// CMotionPathEntranceDlg dialog

class CMotionPathEntranceDlg : public CDialog
{
// Construction
public:
	CMotionPathEntranceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMotionPathEntranceDlg)
	enum { IDD = IDD_DIALOG1 };
	CListBox	m_pathPointsList;
	CString	m_pathPointString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionPathEntranceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DDX_PathPoint( CDataExchange* pDX, int nIDC, CString& value);
	// Generated message map functions
	//{{AFX_MSG(CMotionPathEntranceDlg)
	afx_msg void OnMovePointDown();
	afx_msg void OnMovePointUp();
	afx_msg void OnDeletePoint();
	afx_msg void OnChangePoint();
	afx_msg void OnAddNewPoint();
	afx_msg void OnSelchangePathPointsList();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CList<C3DMotion, C3DMotion>* m_camMotionPathPoints;

public:
	void RegisterPathPointsList(CList<C3DMotion, C3DMotion>* points);
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONPATHENTRANCEDLG_H__62103BC8_E1DD_4DB5_BD6F_60092DA4B7B3__INCLUDED_)
