#include "stdafx.h"
#include ".\quiver.h"

#define ARROW_PORTION 1.0/3.0

CQuiver::CQuiver(void)
{
	m_zoomIntoRect.SetRectEmpty();
}

CQuiver::~CQuiver(void)
{
}

BOOL CQuiver::DisplayQuiver(CWnd* wnd, const CImge & U, const CImge & V)
// Draws the displacement vector of each cell provided by U&V matrices to the given window
// Arguments:
//		o	wnd	:the quiver image will be displayed in the wnd
//		o	U	:horizontal displacement
//		o	V	:vertical displacement
{
	if ((U.height != V.height)||(U.width != V.width))
	{
		return 0;
	}

	CRect	r;
	CPen	pen(PS_SOLID, 1, 0xff0000);
	CDC*	pDC = wnd->GetDC();
	CPen*	oldPen = pDC->SelectObject(&pen);

	if (m_zoomIntoRect.IsRectEmpty())
	{
		m_zoomIntoRect.SetRect(0, 0, U.width, U.height);
		m_zoomIntoRect.NormalizeRect();
	}

	wnd->GetClientRect(r);
	m_xResolution = r.Width()/m_zoomIntoRect.Width();
	m_yResolution = r.Height()/m_zoomIntoRect.Height();
	m_xResolution = (m_xResolution > 0) ? m_xResolution : 1;
	m_yResolution = (m_yResolution > 0) ? m_yResolution : 1;

	m_xMagnify = U.width/m_zoomIntoRect.Width();
	m_yMagnify = U.height/m_zoomIntoRect.Height();

	for (int i = m_zoomIntoRect.TopLeft().y; i < m_zoomIntoRect.BottomRight().y; i ++)
	{
		for (int j = m_zoomIntoRect.TopLeft().x; j < m_zoomIntoRect.BottomRight().x; j++)
		{
			DrawSingle(pDC, i, j, U.Image[i][j], V.Image[i][j]);
		}
	}

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	wnd->ReleaseDC(pDC);
	return 1;
}

void CQuiver::SetZoom(CRect zoomR)
{
	m_zoomIntoRect = zoomR;
}

void CQuiver::ResetZoom()
{
	m_zoomIntoRect.SetRectEmpty();
}
void CQuiver::DrawSingle(CDC* pDC, int i, int j, double u, double v)
// Draws the displacement vector of a single cell
// Arguments:
//		o	pDC	:Device context to draw the vectors
//		o	i	:the row of the location of the cell in concern
//		o	j	:the column of the location of the cell in concern
//		o	u	:the horizontal component of the displacement
//		o	v	:the vertical component of the displacement
{
	u = u*m_xMagnify;
	v = v*m_yMagnify;

	ResetArrowCoords();
	LengthenArrow(sqrt((u*u + v*v)/*(m_xResolution*m_xResolution + m_yResolution*m_yResolution)*/));
	RotateArrow(u, v);
	TranslateArrow(CPoint((j+0.5)*m_xResolution, (i+0.5)*m_yResolution));

	pDC->MoveTo(m_startPt);
	pDC->LineTo(m_endPt);
	pDC->LineTo(m_upperArrEndPt);
	pDC->MoveTo(m_endPt);
	pDC->LineTo(m_lowerArrEndPt);
}

void CQuiver::RotatePoint(CPoint &p, double cosUV, double sinUV)
// Rotates a point by the angle arcsin(sinUV)
// Arguments: 
//		o	p		:point to be rotated
//		o	cosUV	:cosinus of the rotation angle
//		o	sinUV	:sinus of the rotation angle
{
	p.x = p.x*cosUV+p.y*sinUV;
	p.y = -p.x*sinUV+p.y*cosUV;
}

void CQuiver::RotateArrow(double u, double v)
// Rotates the unit arrow as much as the angle that is represented by the pair (u,v)
// in cartesian coordinates
//		o	u	:Cartesian x-component that represents the rotation angle
//		o	v	:Cartesian x-component that represents the rotation angle
{
	double mag = sqrt(u*u + v*v);
	double cosUV = (mag > 0) ? (u/mag) : 0;
	double sinUV = (mag > 0) ? (v/mag) : 0;
	
	RotatePoint(m_startPt, cosUV, sinUV);
	RotatePoint(m_endPt, cosUV, sinUV);
	RotatePoint(m_lowerArrEndPt, cosUV, sinUV);
	RotatePoint(m_upperArrEndPt, cosUV, sinUV);
}

void CQuiver::LengthenArrow(double mag)
// Adjusts the length of the unit arrow and its head accordingly
// Arguments:
//		o	mag	:the desired length of the arrow
{
	m_endPt.x = mag;
	m_upperArrEndPt.x = mag*(1.-ARROW_PORTION);
	m_upperArrEndPt.y = -mag*ARROW_PORTION/2;
	m_lowerArrEndPt.x = mag*(1-ARROW_PORTION);
	m_lowerArrEndPt.y = mag*ARROW_PORTION/2;
}

void CQuiver::TranslateArrow(CPoint trans)
// Shifts the arrow
// Arguments:
//		o	trans	:shift amount
{
	m_startPt += trans;
	m_endPt += trans;
	m_lowerArrEndPt += trans;
	m_upperArrEndPt += trans;
}

void CQuiver::ResetArrowCoords()
// Resets the single arrow properties of the class to the unit arrow
{
	m_startPt.x = 0;
	m_startPt.y = 0;
	m_endPt.x = 1;
	m_endPt.y = 0;
}