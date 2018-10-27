#pragma once

#include <vector>

class CGraphPoint
{
private:
	int x, y, z, h;
public:
	CGraphPoint(int x, int y, int z = 0, int h= 1);
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
	std::vector<CCompGraphObject> m_points;
public:
	CCompGraphObject(void);
	virtual ~CCompGraphObject(void);
	virtual CCompGraphObject Translate()=0;
};

