#pragma once

#include "afxtempl.h"

class CCubicSplineContext;

class CGraphPoint
{
	friend class CCompGraphObject;
	friend class CTriCube;
	friend class CPrism;
	friend class CCubicSplineContext;
	friend class CBilinearSurface;
	friend class CSurfaceContext;

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
	friend class CSurfaceContext;
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

	
class CBilinearSurface :
	public CCompGraphObject
{
private:
	double UW2XYZ(double u, double w, double* points);
public:
	CBilinearSurface(void);
	~CBilinearSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
};

class CLoftedSurface :
	public CCompGraphObject
{
private:
	void ClampedEnd(CDC &dc);
	void RelaxedEnd(CDC &dc);
	void Cyclic(CDC &dc);
	void AntiCyclic(CDC &dc);
	int m_loftMode; //0: Clamped, 1:Relaxed, 2:Cyclic, 3:Annticyclic
public:
	CLoftedSurface(void);
	~CLoftedSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void SetLoftMode(int mode) {m_loftMode = mode;};
	int GetLoftMode() {return m_loftMode;};
};

class CBicubicCoonsSurface :
	public CCompGraphObject
{
private:
	double Mm[4][4][3];
public:
	CBicubicCoonsSurface(void);
	~CBicubicCoonsSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void SetMParam(double param, int i, int j, int k) 
	{
		Mm[i][j][k] = param;
	};
	double GetMParam(int i, int j, int k)
	{
		return Mm[i][j][k];
	};
};


class CLinearCoonsSurface :
	public CCompGraphObject
{
private:
	double Mm[4][4][3];
public:
	CLinearCoonsSurface(void);
	~CLinearCoonsSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void SetMParam(double param, int i, int j, int k) 
	{
		Mm[i][j][k] = param;
	};
	double GetMParam(int i, int j, int k)
	{
		return Mm[i][j][k];
	};

};

class CBezierSurface :
	public CCompGraphObject
{
private:
	int num_u, num_w;
	float fact(int n); // calculates n!
public:
	CBezierSurface(void);
	~CBezierSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void SetNumU(int u) {num_u = u;};
	int GetNumU(){ return num_u;};
	void SetNumW(int w) {num_w = w;};
	int GetNumW(){ return num_w;};

};

class CBSplineSurface :
	public CCompGraphObject
{
private:
	int num_n, num_m;
	int ku, kw;
	float fact(int n); // calculates n!
	double calculateN(int i,double t,int k);
public:
	CBSplineSurface(void);
	~CBSplineSurface(void);
	void DrawGraphObject(CDC &dc, bool closed = true);
	void SetNumN(int u) {num_n = u;};
	int GetNumN(){ return num_n;};
	void SetNumM(int w) {num_m = w;};
	int GetNumM(){ return num_m;};
	void SetNumKu(int w) {ku = w;};
	int GetNumKu(){ return ku;};
	void SetNumKw(int w) {kw = w;};
	int GetNumKw(){ return kw;};

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