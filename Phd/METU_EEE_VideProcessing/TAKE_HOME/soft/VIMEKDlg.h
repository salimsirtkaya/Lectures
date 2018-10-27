// VIMEKDlg.h : header file
//

#if !defined(AFX_VIMEKDLG_H__AAE0C8D4_D008_4A98_ADEF_5B4841EA8D95__INCLUDED_)
#define AFX_VIMEKDLG_H__AAE0C8D4_D008_4A98_ADEF_5B4841EA8D95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VIMEKLayer.h"
#include "DirectShowWrapper.h"
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CVIMEKDlg dialog

class CVIMEKDlg : public CDialog
{
// Construction
public:
	CVIMEKDlg(CWnd* pParent = NULL);	// standard constructor

	CFont myFont1,myFont2;
	
	CDirectShowWrapper m_wrapper;

	bool GetVideoFileName(CString & name);

	static UINT MyThreadFunction(LPVOID pParam);
	void Process();

	CWinThread* myThread;

// Dialog Data
	//{{AFX_DATA(CVIMEKDlg)
	enum { IDD = IDD_VIMEK_DIALOG };
	CListBox	m_txtOut;
	CComboBox	m_blockSize;
	CStatic	m_FR2;
	CStatic	m_FR1;
	CButton	m_grpVideo;
	CButton	m_grpImage;
	CStatic	m_motion;
	UINT	m_startframe;
	UINT	m_endframe;
	UINT	m_nDColor;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVIMEKDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
private:
	CVIMEK	m_vimek;
	// Generated message map functions
	//{{AFX_MSG(CVIMEKDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTrackFeatures();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOpenVideo();
	afx_msg void OnBeginProcessThread();
	afx_msg void OnSelendokCOMBOblockSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIMEKDLG_H__AAE0C8D4_D008_4A98_ADEF_5B4841EA8D95__INCLUDED_)
