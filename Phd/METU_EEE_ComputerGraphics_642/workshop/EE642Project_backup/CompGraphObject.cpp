#include "stdafx.h"
#include "compgraphobject.h"
#include "math.h"

CCompGraphObject::CCompGraphObject(void)
{
	//m_points.
}

CCompGraphObject::~CCompGraphObject(void)
{
}

CGraphPoint::CGraphPoint(int x, int y, int z, int h)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->h = h;
}

//implementations of the transformation functions

void CGraphPoint::Translate2D(int delx, int dely)
{
	// Translate the point with an amount of delx in x-axis, and dely amount in y-axis
	this->x = this->x + delx;
	this->y = this->y + dely;
}

void CGraphPoint::RotateAround2D(CGraphPoint centerOfRotation, double angleOfRotation)
{
	// Rotate the point with an amount of theta degrees about the arbitrary point p
	int xTemp;
	//translate the point to origin first
	this->Translate2D(-centerOfRotation.x, -centerOfRotation.y);

	//rotate about the origin
	xTemp = (int) ceil(cos(angleOfRotation) * (double) this->x - sin(angleOfRotation) * (double) this->y);
	this->y = (int) ceil(sin(angleOfRotation) * (double) this->x + cos(angleOfRotation) * (double) this->y);

	this->x = xTemp;
	//back-translate to the original point
	this->Translate2D(centerOfRotation.x, centerOfRotation.y);
}

void CGraphPoint::RotateAroundOrigin2D(double angleOfRotation)
{
	//rotate about the origin
	int xTemp;
	xTemp = (int) ceil(cos(angleOfRotation) * (double) this->x - sin(angleOfRotation) * (double) this->y);
	this->y = (int) ceil (sin(angleOfRotation) * (double) this->x + cos(angleOfRotation) * (double) this->y);
	this->x = xTemp;
}

void CGraphPoint::ReflectX()
{
	//reflect the point wrt X-axis
	this->y = - this->y;
}

void CGraphPoint::ReflectY()
{
	//reflect the point wrt Y-axis
	this->x = -this->x;
}

void CGraphPoint::ReflectArbitrary(int m, int n)
{
	this->Translate2D(0,-n);

	this->RotateAroundOrigin2D(-atan(m));

	this->ReflectX();

	this->RotateAroundOrigin2D(atan(m));

	this->Translate2D(0,n);
}

void CGraphPoint::Scale(double scaleFactor)
{
	this->x = (int) ceil (scaleFactor * (double) this->x);
	this->y = (int) ceil (scaleFactor * (double) this->y);
}

void CGraphPoint::ShearX(double shearScale)
{
	this->x = (int)ceil((double) this->x + shearScale *(double) this->y);
}


void CGraphPoint::ShearY(double shearScale)
{
	this->y = (int) ceil((double) this->y + shearScale * (double) this->x);
}

void CCompGraphObject::AddNewPoint(int x, int y, int z, int h)
{
	m_points.AddTail(CGraphPoint(x, y, z, h));
}

void CCompGraphObject::DrawGraphObject(CDC &dc)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pt = m_points.GetNext(pos);

	dc.MoveTo(pt.x, -pt.y);
	for(int i = 0; i < m_points.GetCount()-1; i++)
	{
		pt = m_points.GetNext(pos);
		dc.LineTo(pt.x, -pt.y);
	}
	pt = m_points.GetHead();
	dc.LineTo(pt.x, -pt.y);
}

void CCompGraphObject::Translate2D(CCompGraphObject& transformedObj, int delX, int delY)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Translate2D(delX, delY);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::ReflectX(CCompGraphObject& transformedObj)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ReflectX();
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::Scale(CCompGraphObject& transformedObj, double scaleFactor)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Scale(scaleFactor);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::ShearX(CCompGraphObject& transformedObj, double scaleFactor)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ShearX(scaleFactor);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::ShearY(CCompGraphObject& transformedObj, double scaleFactor)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ShearY(scaleFactor);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::ReflectY(CCompGraphObject& transformedObj)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ReflectY();
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::ReflectArbitrary(CCompGraphObject& transformedObj, int m, int n)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ReflectArbitrary(m, n);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}


void CCompGraphObject::RotateAround2D(CCompGraphObject& transformedObj, CGraphPoint centerOfRotation, double angleOfRotation)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.RotateAround2D(centerOfRotation, angleOfRotation);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CCompGraphObject::RotateAroundOrigin(CCompGraphObject& transformedObj, double angle)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.RotateAroundOrigin2D(angle);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}


void CCompGraphObject::CopyData(CCompGraphObject& replica)
{
	replica.m_points.RemoveAll();
	POSITION pos = this->m_points.GetHeadPosition();

	for (int i = 0; i < this->m_points.GetCount(); i++)
	{
		CGraphPoint pt = this->m_points.GetNext(pos);
		replica.m_points.AddTail(pt);
	}
}
