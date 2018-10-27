// AuxiliaryClasses.h: interface for the AuxiliaryClasses class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_)
#define AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C3DMotion  
{
public:
	double	m_Vx;
	double	m_Vy;
	double	m_Vz;
	double	m_RateX;
	double	m_RateY;
	double	m_RateZ;
public:
	CString ParametersString();
	C3DMotion();
	virtual ~C3DMotion();

};

class C2DMotion
{
public:
	double	m_u;
	double	m_v;
};

class C3DMotionOf2DPlane
{
public:
	double	m_a;
	double	m_b;
	double	m_c;
	double	m_d;
	double	m_e;
	double	m_f;
	double	m_g;
	double	m_h;
};

class C2DPlane
{
public:
	double	m_A;
	double	m_B;
	double	m_C;
public:
	double	Alpha(){return 1/m_C;};
	double	Beta(){return -m_A/m_C;};
	double	Gamma() {return -m_B/m_C;};
	C3DMotionOf2DPlane	Motion(C3DMotion motionParams);
};

#endif // !defined(AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_)
