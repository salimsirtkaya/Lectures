// AuxiliaryClasses.h: interface for the AuxiliaryClasses class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_)
#define AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_
#if _MSC_VER > 1000
#endif // _MSC_VER > 1000

#pragma warning( disable : 4786 ) 
#include <map>


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

	C3DMotion(CString s);
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

	C2DMotion UVofPlane(int locationX, int locationY, int resolutionX, int resolutionY)
	{
		C2DMotion	uv;
		double		normalX = locationX/resolutionX - 0.5;
		double		normalY = locationY/resolutionY - 0.5;
		uv.m_u = m_a + m_b*normalY + m_c*normalX + m_g*normalY*normalY + m_h*normalX*normalY;
		uv.m_v = m_d + m_e*normalY + m_f*normalX + m_g*normalX*normalY + m_h*normalX*normalX; 
		return uv;
	}
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

class CPlanarPictureSegment
{
public:
	BYTE	m_maskByte;
	BOOL	m_isIMO;
	
	union PlaneOrMotion
	{
		C2DPlane	m_plane;
		C2DMotion	m_motion;
	}m_planeOrMotion;

	C3DMotionOf2DPlane	m_motionOfPlane;
};

typedef std::map<BYTE, CPlanarPictureSegment> TRegionMap;

#endif // !defined(AFX_AUXILIARYCLASSES_H__4F3256E9_F867_49C1_BBBF_228BA4AD0E11__INCLUDED_)
