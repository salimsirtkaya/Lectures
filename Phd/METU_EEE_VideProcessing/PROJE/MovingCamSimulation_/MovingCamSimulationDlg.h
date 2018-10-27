// MovingCamSimulationDlg.h : header file
//

#if !defined(AFX_MOVINGCAMSIMULATIONDLG_H__96D3CAC1_11E9_4047_B699_52691863620A__INCLUDED_)
#define AFX_MOVINGCAMSIMULATIONDLG_H__96D3CAC1_11E9_4047_B699_52691863620A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "auxiliaryClasses.h"

/////////////////////////////////////////////////////////////////////////////
// CMovingCamSimulationDlg dialog

class CMovingCamSimulationDlg : public CDialog
{
// Construction
public:
	CMovingCamSimulationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMovingCamSimulationDlg)
	enum { IDD = IDD_MOVINGCAMSIMULATION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovingCamSimulationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMovingCamSimulationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CList<C3DMotion, C3DMotion> m_camMotionPathPoints;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVINGCAMSIMULATIONDLG_H__96D3CAC1_11E9_4047_B699_52691863620A__INCLUDED_)
