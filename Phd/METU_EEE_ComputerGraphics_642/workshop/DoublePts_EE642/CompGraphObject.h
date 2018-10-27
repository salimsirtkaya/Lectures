#pragma once

#include "afxtempl.h"

class CCubicSplineContext;

class CGraphPoint
{
	friend class CCompGraphObject;
	friend class CTriCube;
	friend class CPrism;
	friend class CCubicSplineContext;
	
private:
	double x, y, z, h;
public:
	void ProjectPerspective(double xp, double yp, double zp);
	void Transform3D(double Tmatrix[4][4] );
	void Rotate3DAboutAnyLine(double Tmatrix[4][4]);
	CGraphPoint(double x=0, double y=0, double z = 0, double h= 1);
	double GetX() { return this->x; }
	double GetY() { return this->y; }
	double GetZ() { return this->z; }

	void Translate2D(int delx, int dely);
	void Translate3D(int delx, int dely, int delz);
	void RotateAround2D(CGraphPoint centerOfRotation, double angleOfRotation );
	void RotateAroundOrigin2D(double angleOfRotation);
	void ShearX(double shearScale);
	void ShearY(double shearScale);
	void Scale(double scaleFactor);
	void ReflectX();
	void ReflectY();
	void ReflectZ();
	void ReflectArbitrary(int m, int n);
	void Arbitrary2DTransformation();
	int RoundNum(double number);
	void Scale3D(double scaleFactor);
	void ShearZ(double shearScale);
	void Rotate3Dx(double angle);
	void Rotate3Dy(double angle);
	void Rotate3Dz(double angle);
};
class CCompGraphObject
{
protected:
	CList<CGraphPoint, CGraphPoint> m_points;
public:
	void RemoveAllPoints() {m_points.RemoveAll();};
	CCompGraphObject* GetNewInstance();
	void ProjectPerspective(CCompGraphObject& transformedObj, double xp, double yp, double zp);
	void Rotate3DAboutAnyLine(CCompGraphObject &transformedObj, double n1, double n2, double n3, double theta);
	CCompGraphObject(void);
	virtual ~CCompGraphObject(void);
	virtual void ShearX(CCompGraphObject& transformedObj, double shearScale);
	virtual void ShearY(CCompGraphObject& transformedObj, double shearScale);
	virtual void Scale(CCompGraphObject& transformedObj, double scaleFactor);
	virtual void Translate2D(CCompGraphObject& transformedObj, int delX, int delY);
	virtual void ReflectX(CCompGraphObject& transformedObj);
	virtual void ReflectY(CCompGraphObject& transformedObj);
	virtual void ReflectZ(CCompGraphObject& transformedObj);
	virtual void ReflectArbitrary(CCompGraphObject& transformedObj, int m, int n);
	virtual void RotateAround2D(CCompGraphObject& transformedObj, CGraphPoint centerOfRotation, double angleOfRotation);
	virtual void RotateAroundOrigin(CCompGraphObject& transformedObj, double angle);
	int GetPointCount() {return m_points.GetCount();};
	void AddNewPoint(double x=0, double y=0, double z = 0, double h= 1);
	virtual void DrawGraphObject(CDC &dc, bool closed = true);
	virtual void CopyData(CCompGraphObject& replica);
	virtual void Translate3D(CCompGraphObject& transformedObj, int delX, int delY, int delZ);
	void Scale3D(CCompGraphObject& transformedObj, double scaleFactor);
	void ShearZ(CCompGraphObject& newObj, double shearScale);
	void Rotate3Dx(CCompGraphObject& transformedObj, double angleOfRotation);
	void Rotate3Dy(CCompGraphObject& transformedObj, double angleOfRotation);
	void Rotate3Dz(CCompGraphObject& transformedObj, double angleOfRotation);
private:
	void CalculateTransformMatrix(double T[4][4], double n1, double n2, double n3, double theta);
};


class CTriCube :
	public CCompGraphObject
{
public:
	CTriCube(void);
	~CTriCube(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void DefaultTriCube();
};


class CPrism :
	public CCompGraphObject
{
public:
	CPrism(void);
	~CPrism(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void DefaultPrism();
};

//class CCircularObj ://circle, ellipse
//	public CCompGraphObject
//{
//public:
//	CCircularObj(void);
//	~CCircularObj(void);
//	void DrawGraphObject(CDC &dc);
//};

class CHyperbolaObj :
	public CCompGraphObject
{
	CList<CGraphPoint, CGraphPoint> m_points2;
public:
	CHyperbolaObj(void);
	~CHyperbolaObj(void);
	void DrawGraphObject(CDC &dc);
};

class CParabolaObj :
	public CCompGraphObject
{
public:
	CParabolaObj(void);
	~CParabolaObj(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
};