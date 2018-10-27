#pragma once

#include "afxtempl.h"

class CGraphPoint
{
	friend class CCompGraphObject;
private:
	int x, y, z, h;
public:
	CGraphPoint(int x=0, int y=0, int z = 0, int h= 1);
	int GetX() { return this->x; }
	int GetY() { return this->y; }
	int GetZ() { return this->z; }

	void Translate2D(int delx, int dely);
	void RotateAround2D(CGraphPoint centerOfRotation, double angleOfRotation );
	void RotateAroundOrigin2D(double angleOfRotation);
	void ShearX(double shearScale);
	void ShearY(double shearScale);
	void Scale(double scaleFactor);
	void ReflectX();
	void ReflectY();
	void ReflectArbitrary(int m, int n);
	void Arbitrary2DTransformation();
};

class CCompGraphObject
{
protected:
	CList<CGraphPoint, CGraphPoint> m_points;
public:
	CCompGraphObject(void);
	virtual ~CCompGraphObject(void);
	virtual void ShearX(CCompGraphObject& transformedObj, double shearScale);
	virtual void ShearY(CCompGraphObject& transformedObj, double shearScale);
	virtual void Scale(CCompGraphObject& transformedObj, double scaleFactor);
	virtual void Translate2D(CCompGraphObject& transformedObj, int delX, int delY);
	virtual void ReflectX(CCompGraphObject& transformedObj);
	virtual void ReflectY(CCompGraphObject& transformedObj);
	virtual void ReflectArbitrary(CCompGraphObject& transformedObj, int m, int n);
	virtual void RotateAround2D(CCompGraphObject& transformedObj, CGraphPoint centerOfRotation, double angleOfRotation);
	virtual void RotateAroundOrigin(CCompGraphObject& transformedObj, double angle);
	int GetPointCount() {m_points.GetCount();};
	void AddNewPoint(int x=0, int y=0, int z = 0, int h= 1);
	virtual void DrawGraphObject(CDC &dc);
	void CopyData(CCompGraphObject& replica);
};


class CLineObject :
	public CCompGraphObject
{
public:
	CLineObject(void);
	~CLineObject(void);
};