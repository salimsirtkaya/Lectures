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
#include "afxwin.h"

#define MAX_MENU_COUNT 9
/////////////////////////////////////////////////////////////////////////////
// CEE642ProjectDlg dialog

class CEE642ProjectDlg : public CDialog, public C642Manager
{
// Construction
public:
	void ShowApplyBtn(int nCmd);
	void Exit();
	void WriteMouseLocInfo(int x, int y);
	void ReleaseRenderAreaDC(CDC* pDC);
	CDC* GetRenderAreaDC();
	void SetMenuTitle(CString str);
	void SetInfoAreaText(CString str);
	void DrawLine(CPoint p1, CPoint p2);
	void ChangeContext(CUserContext* newContext);
	CEE642ProjectDlg(CWnd* pParent = NULL);	// standard constructor
	void SetCurrentGraphObject(CCompGraphObject *obj, bool clearPrevious = false);
	double GetInput1();
	double GetInput2();
	void SetRadio1(CString str);
	void SetRadio2(CString str);
	void SetRadio3(CString str);
	void SetRadio4(CString str);
	void SetRadio5(CString str);
	void SetInput3Name(CString name);
	double GetInput3();
	void SetInput4Name(CString name);
	double GetInput4();
	void SetInput5Name(CString name);
	double GetInput5();
	void SetInput6Name(CString name);
	double GetInput6();
	void ClearRadio();
	void LineParametersShow(int cmd);
	int GetRadioSel();
	void SetRadioSel(int sel);
	double GetLineParamA();
	double GetLineParamB();
// Dialog Data
	//{{AFX_DATA(CEE642ProjectDlg)
	enum { IDD = IDD_EE642PROJECT_DIALOG };
	CStatic	m_statusAreaWnd;
	CEdit	m_input8Edit;
	CEdit	m_input7Edit;
	CEdit	m_input6Edit;
	CStatic	m_input6Name;
	CStatic	m_input5Name;
	CStatic	m_input4Name;
	CStatic	m_input3Name;
	CEdit	m_edit5;
	CStatic	m_menuTitleBar;
	CEdit	m_gridInfo;
	CStatic	m_infoArea;
	CStatic	m_statY;
	CStatic	m_statX;
	CEdit	m_edit4;
	CEdit	m_edit3;
	CButton	m_radioBtn;
	CRenderingArea	m_renderArea;
	int		m_radioSelection;
	double	m_edit3Value;
	double	m_edit4Value;
	double	m_edit5Value;
	double	m_input6Value;
	double	m_input7Value;
	double	m_input8Value;
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
	virtual void OnOK();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnButtonCls();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMenuArea m_menuArea;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CButton m_menuButtons[MAX_MENU_COUNT];
	CStatic m_input1Name;
	CStatic m_input2Name;
	CEdit m_input1Edit;
	CEdit m_input2Edit;
	double m_input1Value;
	double m_input2Value;
	void ClearInputArea(void);
	void SetInput1Name(CString name);
	void SetInput2Name(CString name);
	CButton m_applyButton;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonApply();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EE642PROJECTDLG_H__C652D27B_8226_404B_8F2F_CFDE626209D9__INCLUDED_)
