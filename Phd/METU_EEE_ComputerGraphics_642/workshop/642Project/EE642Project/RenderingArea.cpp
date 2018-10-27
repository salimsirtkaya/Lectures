// RenderingArea.cpp : implementation file
//

#include "stdafx.h"
#include "EE642Project.h"
#include "RenderingArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenderingArea

CRenderingArea::CRenderingArea()
{
	m_bkGndBrush.CreateStockObject(BLACK_BRUSH);
}

CRenderingArea::~CRenderingArea()
{
}


BEGIN_MESSAGE_MAP(CRenderingArea, CStatic)
	//{{AFX_MSG_MAP(CRenderingArea)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenderingArea message handlers

void CRenderingArea::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect clientRect;

	int s = dc.GetMapMode();
s = MM_TEXT;
	GetClientRect(clientRect);
	dc.FillSolidRect(clientRect, 0);
	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(0xff0000);
	dc.SetTextColor(0xffffff);
	dc.SelectStockObject(WHITE_PEN);
	dc.MoveTo(0,0);
	dc.LineTo(100,100);

	Grid(dc, 2, 2);
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CRenderingArea::Grid(CDC &dc, int xSpace, int ySpace)
{
	CSize s = dc.GetViewportExt();
}
