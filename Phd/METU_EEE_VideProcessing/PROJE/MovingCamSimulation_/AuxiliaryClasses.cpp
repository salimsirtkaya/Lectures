// AuxiliaryClasses.cpp: implementation of the AuxiliaryClasses class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "AuxiliaryClasses.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DMotion::C3DMotion()
{

}

C3DMotion::~C3DMotion()
{

}

C3DMotionOf2DPlane C2DPlane::Motion(C3DMotion	motionParams)
{
	C3DMotionOf2DPlane	result;

	result.m_a = -Alpha()*motionParams.m_Vx - motionParams.m_RateY;
	result.m_b = Alpha()*motionParams.m_Vz - Beta()*motionParams.m_Vx;
	result.m_c = -motionParams.m_RateZ - Gamma()*motionParams.m_Vx;
	result.m_d = -Alpha()*motionParams.m_Vy + motionParams.m_RateX;
	result.m_e = -motionParams.m_RateZ - Beta()*motionParams.m_Vy;
	result.m_f = Alpha()*motionParams.m_Vz - Gamma()*motionParams.m_Vy;
	result.m_g = -motionParams.m_RateY + Beta()*motionParams.m_Vz;
	result.m_h = motionParams.m_RateX - Gamma()*motionParams.m_Vz;

	return result;
}

CString C3DMotion::ParametersString()
{
	CString	str;
	str.Format("%f; %f; %f; %f; %f; %f", m_Vx, m_Vy, m_Vz, m_RateX, m_RateY, m_RateZ);
	return str;
}
