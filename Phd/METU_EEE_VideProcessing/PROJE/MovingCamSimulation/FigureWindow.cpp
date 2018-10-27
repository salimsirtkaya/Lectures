// FigureWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "FigureWindow.h"
#include ".\figurewindow.h"


// CFigureWindow dialog

IMPLEMENT_DYNAMIC(CFigureWindow, CDialog)
CFigureWindow::CFigureWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CFigureWindow::IDD, pParent)
{
}

CFigureWindow::~CFigureWindow()
{
}

void CFigureWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_canvasFrame);
}


BEGIN_MESSAGE_MAP(CFigureWindow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFigureWindow message handlers

void CFigureWindow::OnBnClickedButton1()
{
	CQuiver quiver;
this->SetWindowText("Figure 1");
	CImge u(10,10);
	CImge v(10,10);

	u.SetAllPxlsTo(15);
	v.SetAllPxlsTo(15);
	int i= 0,j =0;

    u(i,j++) = 20; u(i, j++) = 10, u(i++, j)=-40;
	j = 0;
	u(i,j++) = 20; u(i, j++) = 30, u(i++, j)=-40;
	j = 0;
    u(i,j++) = 20; u(i, j++) = 10, u(i++, j)=20;
	i = 0, j = 0;

    v(i,j++) = 20; v(i, j++) = 10, v(i++, j)=20;
	j = 0;
	v(i,j++) = 20; v(i, j++) = 10, v(i++, j)=-20;
	j = 0;
    v(i,j++) = 20; v(i, j++) = 10, v(i++, j)=-20;

	quiver.SetZoom(CRect(0,0,4,3));
	quiver.DisplayQuiver(&m_canvasFrame, u, v);
}


void CFigureWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
		int i = 0;
		CWnd* pw = GetFocus();
	if (pw->GetDlgCtrlID() == IDC_STATIC1)
	{
		i++;
	}

	CDialog::OnLButtonDown(nFlags, point);
}
