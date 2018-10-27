#pragma once
#include "quiver.h"
#include "afxwin.h"
#include "quiverCanvas.h"
// CFigureWindow dialog

class CFigureWindow : public CDialog
{
	DECLARE_DYNAMIC(CFigureWindow)

public:
	CFigureWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFigureWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CQuiverCanvas m_canvasFrame;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
