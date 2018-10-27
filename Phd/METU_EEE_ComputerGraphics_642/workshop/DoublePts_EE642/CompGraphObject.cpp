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

CGraphPoint::CGraphPoint(double x, double y, double z, double h)
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

void CGraphPoint::Translate3D(int delx, int dely, int delz)
{
	// Translate the point with an amount of delx in x-axis, and dely amount in y-axis
	this->x = this->x + delx;
	this->y = this->y + dely;
	this->z = this->z + delz;
}

void CGraphPoint::RotateAround2D(CGraphPoint centerOfRotation, double angleOfRotation)
{
	// Rotate the point with an amount of theta degrees about the arbitrary point p
	double xTemp;
	//translate the point to origin first
	this->Translate2D(-centerOfRotation.x, -centerOfRotation.y);

	//rotate about the origin
	xTemp = (cos(angleOfRotation) * (double) this->x - sin(angleOfRotation) * (double) this->y);
	this->y = (sin(angleOfRotation) * (double) this->x + cos(angleOfRotation) * (double) this->y);

	this->x = xTemp;
	//back-translate to the original point
	this->Translate2D(centerOfRotation.x, centerOfRotation.y);
}

void CGraphPoint::RotateAroundOrigin2D(double angleOfRotation)
{
	//rotate about the origin
	double xTemp;

	xTemp = (cos(angleOfRotation) * (double) this->x - sin(angleOfRotation) * (double) this->y);
	this->y = (sin(angleOfRotation) * (double) this->x + cos(angleOfRotation) * (double) this->y);
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

void CGraphPoint::ReflectZ()
{
	//reflect the point wrt Z-axis
	this->z = -this->z;
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
	this->x = (scaleFactor * this->x);
	this->y = (scaleFactor * this->y);
}

void CGraphPoint::ShearX(double shearScale)
{
	this->x = (this->x + shearScale *this->y);
}


void CGraphPoint::ShearY(double shearScale)
{
	this->y = (this->y + shearScale * this->x);
}

void CCompGraphObject::AddNewPoint(double x, double y, double z, double h)
{
	m_points.AddTail(CGraphPoint(x, y, z, h));
}

void CCompGraphObject::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pt = m_points.GetNext(pos);

	dc.MoveTo(pt.RoundNum(pt.x), -pt.RoundNum(pt.y));
	for(int i = 0; i < m_points.GetCount()-1; i++)
	{
		pt = m_points.GetNext(pos);
		dc.LineTo(pt.RoundNum(pt.x), -pt.RoundNum(pt.y));
	}
	if (closed)
	{
		pt = m_points.GetHead();
		dc.LineTo(pt.RoundNum(pt.x), -pt.RoundNum(pt.y));
	}
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

void CCompGraphObject::ReflectZ(CCompGraphObject& transformedObj)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ReflectZ();
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

int CGraphPoint::RoundNum(double number)
{
	int temp;
	temp = (int) number;
	if ((number>=0) && ((number- temp)>=0.5))
		return(temp+1);
	else if ((number>=0) && ((number- temp)<0.5))
		return(temp);
	else if ((number<0) && ((temp - number)>=0.5))
		return(temp-1);
	else
		return(temp);
}

void CCompGraphObject::Translate3D(CCompGraphObject& transformedObj, int delX, int delY, int delZ)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Translate3D(delX, delY, delZ);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::Scale3D(double scaleFactor)
{
	this->x = (scaleFactor * this->x);
	this->y = (scaleFactor * this->y);
	this->z = (scaleFactor * this->z);
}

void CCompGraphObject::Scale3D(CCompGraphObject& transformedObj, double scaleFactor)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Scale3D(scaleFactor);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::ShearZ(double shearScale)
{
	this->z = ((double) this->z + shearScale * (double) this->z);
}

void CCompGraphObject::ShearZ(CCompGraphObject& transformedObj, double scaleFactor)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ShearZ(scaleFactor);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::Rotate3Dx(double angleOfRotation)
{
	double yTemp;

	yTemp = (-sin(angleOfRotation) * (double) this->z + cos(angleOfRotation) * (double) this->y);
	this->z = (cos(angleOfRotation) * (double) this->z + sin(angleOfRotation) * (double) this->y);
	this->y = yTemp;
}

void CCompGraphObject::Rotate3Dx(CCompGraphObject& transformedObj, double angleOfRotation)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Rotate3Dx(angleOfRotation);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::Rotate3Dy(double angleOfRotation)
{
	double xTemp;
	xTemp = (sin(angleOfRotation) * (double) this->z + cos(angleOfRotation) * (double) this->x);
	this->z = (cos(angleOfRotation) * (double) this->z - sin(angleOfRotation) * (double) this->x);
	this->x = xTemp;
}

void CCompGraphObject::Rotate3Dy(CCompGraphObject& transformedObj, double angleOfRotation)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Rotate3Dy(angleOfRotation);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::Rotate3Dz(double angleOfRotation)
{
	double xTemp;
	xTemp = (-sin(angleOfRotation) * (double) this->y + cos(angleOfRotation) * (double) this->x);
	this->y = (cos(angleOfRotation) * (double) this->y + sin(angleOfRotation) * (double) this->x);
	this->x = xTemp;
}


void CGraphPoint::Rotate3DAboutAnyLine(double Tmatrix[4][4])
{
	this->Transform3D(Tmatrix);
}

void CCompGraphObject::Rotate3Dz(CCompGraphObject& transformedObj, double angleOfRotation)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Rotate3Dz(angleOfRotation);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}


void CCompGraphObject::Rotate3DAboutAnyLine(CCompGraphObject &transformedObj, double n1, double n2, double n3, double theta)
{
	double Tmatrix[4][4];
	CalculateTransformMatrix(Tmatrix, n1, n2, n3, theta);

	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.Rotate3DAboutAnyLine(Tmatrix);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

void CGraphPoint::Transform3D(double Tmatrix[4][4])
{
	double xTemp, yTemp;

	xTemp = Tmatrix[0][0]*x + Tmatrix[0][1]*y + Tmatrix[0][2]*z;
	yTemp = Tmatrix[1][0]*x + Tmatrix[1][1]*y + Tmatrix[1][2]*z;
	this->z = (Tmatrix[2][0]*x + Tmatrix[2][1]*y + Tmatrix[2][2]*z);
	this->x = (xTemp);
	this->y = (yTemp);
}

void CCompGraphObject::CalculateTransformMatrix(double T[4][4], double n1, double n2, double n3, double theta)
{
	T[0][0] = pow(n1, 2) + cos(theta)*(1-pow(n1,2));
	T[0][1] = n1*n2*(1-cos(theta)) + n3*sin(theta);
	T[0][2] = n1*n3*(1-cos(theta)) - n2*sin(theta);
	T[0][3] = 0;

	T[1][0] = n1*n2*(1-cos(theta)) - n3*sin(theta);
	T[1][1] = pow(n2,2) + (1-pow(n2,2))*cos(theta);
	T[1][2] = n2*n3*(1-cos(theta)) + n1*sin(theta);
	T[1][3] = 0;

	T[2][0] = n1*n3*(1-cos(theta)) + n2*sin(theta);
	T[2][1] = n2*n3*(1-cos(theta)) - n1*sin(theta);
	T[2][2] = pow(n3,2) + (1-pow(n3,2))*cos(theta);
	T[2][3] = 0;

	T[3][0] = 0;
	T[3][1] = 0;
	T[3][2] = 0;
	T[3][3] = 1;
}

void CGraphPoint::ProjectPerspective(double xp, double yp, double zp)
{
	double p, q, r;

	p = (xp==0)?(0):(1/xp);
	q = (yp==0)?(0):(1/yp);
	r = (zp==0)?(0):(1/zp);
	double divider = (p*x + q*y + r*z + 1);

	x = (x / divider );
	y = (y / divider);	
}

void CCompGraphObject::ProjectPerspective(CCompGraphObject& transformedObj, double xp, double yp, double zp)
{
	this->CopyData(transformedObj);
	POSITION pos = transformedObj.m_points.GetHeadPosition();
	for (int i = 0; i < m_points.GetCount(); i++)
	{
		POSITION curPos = pos;
		CGraphPoint pt = transformedObj.m_points.GetNext(pos);
		pt.ProjectPerspective(xp, yp, zp);
		transformedObj.m_points.SetAt(curPos, pt);
	}
}

CCompGraphObject* CCompGraphObject::GetNewInstance()
{
	CCompGraphObject* newObj;

	if (dynamic_cast<CTriCube*>(this) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(this) != 0)
		{
			newObj = new CPrism();
		}
		else
		{
			newObj = new CCompGraphObject();
		}
	}
	return newObj;
}
