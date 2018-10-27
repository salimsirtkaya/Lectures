// RenderingArea.cpp : implementation file
//

#include "stdafx.h"
#include "EE642Project.h"
#include "RenderingArea.h"
#include "642Manager.h"

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
	m_previousObjectPen.CreatePen(PS_DOT, 1, 0x00ff80);
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
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
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

	dc.SelectObject(m_currentObjectPen);
	m_manager->DrawCurrentGraphObject(dc);

	dc.SelectObject(m_previousObjectPen);
	m_manager->DrawPreviousGraphObject(dc);
	// Do not call CStatic::OnPaint() for painting messages

	if (m_manager->GetHandleMouse())
	{
		dc.MoveTo(m_manager->GetMouseLoc());
		CBrush br;
		br.CreateSolidBrush(0xff);
		CPoint p1 = m_manager->GetMouseLoc();
		CRect r(p1.x-2, -(p1.y-2), p1.x+2, -(p1.y+2));
		dc.FillRect(r, &br);
	}
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
void CRenderingArea::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect r;
	this->GetClientRect(r);

	int x = r.Width()/2;
	int y = r.Height()/2;
	CPoint p;
	p.x = point.x-x;
	p.y = -(point.y-y);
	m_manager->SetMouseLoc(p);
	m_manager->RenderAreaLButton(nFlags, point);
	if(m_manager->GetHandleMouse())
	{
		this->RedrawWindow();
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CRenderingArea::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		CRect r;
	this->GetClientRect(r);

	int x = r.Width()/2;
	int y = r.Height()/2;
	CPoint p;
	p.x = point.x-x;
	p.y = -(point.y-y);
	
	CStatic::OnMouseMove(nFlags, point);
}
