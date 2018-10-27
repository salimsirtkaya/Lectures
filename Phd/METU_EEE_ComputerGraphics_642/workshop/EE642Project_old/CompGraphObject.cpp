#include "stdafx.h"
#include "compgraphobject.h"
#include "math.h"

CCompGraphObject::CCompGraphObject(void)
{
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
	xTemp = cos(angleOfRotation) * this->x - sin(angleOfRotation) * this->y;
	this->y = sin(angleOfRotation) * this->x + cos(angleOfRotation) * this->y;

	this->x = xTemp;
	//back-translate to the original point
	this->Translate2D(centerOfRotation.x, centerOfRotation.y);
}

void CGraphPoint::RotateAroundOrigin2D(double angleOfRotation)
{
	//rotate about the origin
	int xTemp;
	xTemp = cos(angleOfRotation) * this->x - sin(angleOfRotation) * this->y;
	this->y = sin(angleOfRotation) * this->x + cos(angleOfRotation) * this->y;
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
	this->x = scaleFactor * this->x;
	this->y = scaleFactor * this->y;
}

void CGraphPoint::ShearX(double shearScale)
{
	this->x = this->x + shearScale * this->y;
}


void CGraphPoint::ShearY(double shearScale)
{
	this->y = this->y + shearScale * this->x;
}
