// RenderingArea.cpp : implementation file
//

#include "stdafx.h"
#include "EE642Project.h"
#include "RenderingArea.h"

#include "CompGraphObject.h" //TUBA

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
	m_gridPen.CreatePen(PS_DOT, 1, 0x563514);
	m_principalGridPen.CreatePen(PS_SOLID, 1, 0xa06326);
	m_currentObjectPen.CreatePen(PS_SOLID, 2, 0x0080ff);
	m_previousObjectPen.CreatePen(PS_SOLID, 2, 0x00ff80);
}

CRenderingArea::~CRenderingArea()
{
	m_gridPen.DeleteObject();
	m_principalGridPen.DeleteObject();
	m_currentObjectPen.DeleteObject();
	m_previousObjectPen.DeleteObject();
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
	
	double pi = 3.1415926535;

	CPaintDC dc(this); // device context for painting

	FillArea(dc, 0x280000);
	Grid(dc, 50, 50, true);
	CGraphPoint r1(100,70);
	CGraphPoint p1(0,0);
	CGraphPoint p2(100, 100);
	dc.SelectObject(m_currentObjectPen);
	dc.MoveTo(p1.GetX(), -p1.GetY());
	dc.LineTo(p2.GetX(), -p2.GetY());
	p1.ShearY(0.5);
	p2.ShearY(0.5);
	dc.SelectObject(m_previousObjectPen);
	dc.MoveTo(p1.GetX(), -p1.GetY());
	dc.LineTo(p2.GetX(), -p2.GetY());
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CRenderingArea::FillArea(CDC &dc, COLORREF clr)
{
	CRect clientRect;
	GetClientRect(clientRect);
	dc.FillSolidRect(clientRect, clr);
}

void CRenderingArea::Grid(CDC &dc, int xSpace, int ySpace, bool gridOn)
{
	if (gridOn)
	{
		dc.SetBkMode(TRANSPARENT);
		CPen* oldPen = dc.SelectObject(&m_gridPen);
		CRect clientRect;
		this->GetClientRect(clientRect);
		int xOrg = clientRect.Width()/2;
		int yOrg = clientRect.Height()/2;
		dc.SetViewportExt(clientRect.Size());
		dc.SetViewportOrg(xOrg, yOrg);
		
		//vertical lines:
		for (int x = 0; x < xOrg; x= x+xSpace)
		{
			dc.MoveTo(x, -yOrg);
			dc.LineTo(x,  yOrg);
			dc.MoveTo(-x, -yOrg);
			dc.LineTo(-x, yOrg);
		}
		//horizontal lines:
		for (int y = 0; y < yOrg; y= y+ySpace)
		{
			dc.MoveTo(-xOrg, y);
			dc.LineTo(xOrg,  y);
			dc.MoveTo(-xOrg, -y);
			dc.LineTo(xOrg,  -y);
		}
		//principal lines:
		dc.SelectObject(&m_principalGridPen);
		dc.MoveTo(-xOrg, 0);
		dc.LineTo(xOrg, 0);
		dc.MoveTo(0, -yOrg);
		dc.LineTo(0, yOrg);
		
		dc.SelectObject(oldPen);
	}
}