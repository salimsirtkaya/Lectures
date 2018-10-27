#include "stdafx.h"
#include "compgraphobject.h"

CTriCube::CTriCube(void)
{
}

CTriCube::~CTriCube(void)
{
}

void CTriCube::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pts[10];
	pts[0] = m_points.GetNext(pos);
	dc.MoveTo(pts[0].x, -pts[0].y);
	int i;
	for(i = 1; i < 5; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[0].x, -pts[0].y);

	pts[i] = m_points.GetNext(pos);
	dc.LineTo(pts[i].x, -pts[i].y);

	for(i = 6; i < 9; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[5].x, -pts[5].y);

	pts[i] = m_points.GetNext(pos);
	
	dc.MoveTo(pts[7].x, -pts[7].y);
	dc.LineTo(pts[9].x, -pts[9].y);
	dc.LineTo(pts[3].x, -pts[3].y);
	dc.MoveTo(pts[9].x, -pts[9].y);
	dc.LineTo(pts[2].x, -pts[2].y);
	dc.MoveTo(pts[6].x, -pts[6].y);
	dc.LineTo(pts[1].x, -pts[1].y);
	dc.MoveTo(pts[8].x, -pts[8].y);
	dc.LineTo(pts[4].x, -pts[4].y);
}

void CTriCube::DefaultTriCube()
{
	this->AddNewPoint(0, 0, 100, 1);
	this->AddNewPoint(100, 0, 100, 1);
	this->AddNewPoint(100, 50, 100, 1);
	this->AddNewPoint(50, 100, 100, 1);
	this->AddNewPoint(0, 100, 100, 1);
	this->AddNewPoint(0, 0, 0, 1);
	this->AddNewPoint(100, 0, 0, 1);
	this->AddNewPoint(100, 100, 0, 1);
	this->AddNewPoint(0, 100, 0, 1);
	this->AddNewPoint(100, 100, 50, 1);
}


/***************************************************/
CPrism::CPrism(void)
{
}

CPrism::~CPrism(void)
{
}

void CPrism::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pts[10];
	pts[0] = m_points.GetNext(pos);
	dc.MoveTo(pts[0].x, -pts[0].y);
	int i;
	for(i = 1; i < 8; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[0].x, -pts[0].y);
	dc.MoveTo(pts[7].x, -pts[7].y);
	dc.LineTo(pts[4].x, -pts[4].y);
	dc.MoveTo(pts[2].x, -pts[2].y);
	dc.LineTo(pts[5].x, -pts[5].y);
	dc.MoveTo(pts[1].x, -pts[1].y);
	dc.LineTo(pts[6].x, -pts[6].y);
	dc.MoveTo(pts[0].x, -pts[0].y);
	dc.LineTo(pts[3].x, -pts[3].y);
}

void CPrism::DefaultPrism()
{
	int a = 50;
	this->AddNewPoint(0, 0, 0, 1);
	this->AddNewPoint(0, a, 0, 1);
	this->AddNewPoint(2*a, a, 0, 1);
	this->AddNewPoint(2*a, 0, 0, 1);
	this->AddNewPoint(2*a, 0, a/2, 1);
	this->AddNewPoint(2*a, a, a/2, 1);
	this->AddNewPoint(0, a, a/2, 1);
	this->AddNewPoint(0, 0, a/2, 1);
}

