// KBasicStructures.cpp: implementation of the KBasicStructures class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KBasicStructures.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

KBasicStructures::dPoint2D::dPoint2D(double dx , double dy )
{
	x = dx;
	y = dy;
}

KBasicStructures::dPoint3D::dPoint3D(double dx , double dy, double dz )
{
	x = dx;
	y = dy;
	z = dz;
}


KBasicStructures::correspondencePair::correspondencePair()
{
}

KBasicStructures::correspondenceTriplet::correspondenceTriplet()
{
}


KBasicStructures::node::node()
{
}
