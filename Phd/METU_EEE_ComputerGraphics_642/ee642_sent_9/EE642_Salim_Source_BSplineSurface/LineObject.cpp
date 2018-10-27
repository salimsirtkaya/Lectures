#include "stdafx.h"
#include "compgraphobject.h"
#include <math.h>
CTriCube::CTriCube(void)
{
}

CTriCube::~CTriCube(void)
{
}

void CTriCube::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pts[10];
	pts[0] = m_points.GetNext(pos);
	dc.MoveTo(pts[0].x, -pts[0].y);
	int i;
	for(i = 1; i < 5; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[0].x, -pts[0].y);

	pts[i] = m_points.GetNext(pos);
	dc.LineTo(pts[i].x, -pts[i].y);

	for(i = 6; i < 9; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[5].x, -pts[5].y);

	pts[i] = m_points.GetNext(pos);
	
	dc.MoveTo(pts[7].x, -pts[7].y);
	dc.LineTo(pts[9].x, -pts[9].y);
	dc.LineTo(pts[3].x, -pts[3].y);
	dc.MoveTo(pts[9].x, -pts[9].y);
	dc.LineTo(pts[2].x, -pts[2].y);
	dc.MoveTo(pts[6].x, -pts[6].y);
	dc.LineTo(pts[1].x, -pts[1].y);
	dc.MoveTo(pts[8].x, -pts[8].y);
	dc.LineTo(pts[4].x, -pts[4].y);
}

void CTriCube::DefaultTriCube()
{
	this->AddNewPoint(0, 0, 100, 1);
	this->AddNewPoint(100, 0, 100, 1);
	this->AddNewPoint(100, 50, 100, 1);
	this->AddNewPoint(50, 100, 100, 1);
	this->AddNewPoint(0, 100, 100, 1);
	this->AddNewPoint(0, 0, 0, 1);
	this->AddNewPoint(100, 0, 0, 1);
	this->AddNewPoint(100, 100, 0, 1);
	this->AddNewPoint(0, 100, 0, 1);
	this->AddNewPoint(100, 100, 50, 1);
}


/***************************************************/
CPrism::CPrism(void)
{
}

CPrism::~CPrism(void)
{
}

void CPrism::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	CGraphPoint pts[10];
	pts[0] = m_points.GetNext(pos);
	dc.MoveTo(pts[0].x, -pts[0].y);
	int i;
	for(i = 1; i < 8; i++)
	{
		pts[i] = m_points.GetNext(pos);
		dc.LineTo(pts[i].x, -pts[i].y);
	}
	dc.LineTo(pts[0].x, -pts[0].y);
	dc.MoveTo(pts[7].x, -pts[7].y);
	dc.LineTo(pts[4].x, -pts[4].y);
	dc.MoveTo(pts[2].x, -pts[2].y);
	dc.LineTo(pts[5].x, -pts[5].y);
	dc.MoveTo(pts[1].x, -pts[1].y);
	dc.LineTo(pts[6].x, -pts[6].y);
	dc.MoveTo(pts[0].x, -pts[0].y);
	dc.LineTo(pts[3].x, -pts[3].y);
}

void CPrism::DefaultPrism()
{
	int a = 50;
	this->AddNewPoint(0, 0, 0, 1);
	this->AddNewPoint(0, a, 0, 1);
	this->AddNewPoint(2*a, a, 0, 1);
	this->AddNewPoint(2*a, 0, 0, 1);
	this->AddNewPoint(2*a, 0, a/2, 1);
	this->AddNewPoint(2*a, a, a/2, 1);
	this->AddNewPoint(0, a, a/2, 1);
	this->AddNewPoint(0, 0, a/2, 1);
}

/***********************************************************/
/***************************************************/
CBilinearSurface::CBilinearSurface(void)
{
}

CBilinearSurface::~CBilinearSurface(void)
{
}

void CBilinearSurface::DrawGraphObject(CDC &dc, bool closed)
{
	POSITION pos = m_points.GetHeadPosition();
	double m_guideXs[4], m_guideYs[4], m_guideZs[4];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	m_guideXs[0] = pt.GetX();
	m_guideYs[0] = pt.GetY();
	m_guideZs[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		m_guideXs[i] = pt.GetX();
		m_guideYs[i] = pt.GetY();
		m_guideZs[i] = pt.GetZ();
	}

/*	CPen pen, *pOldPen ;
	pen.CreatePen(PS_SOLID, 1, 0xffff);
	pOldPen = dc.SelectObject(&pen);
*/	double u=0,w=0;
	double qx,qy,qz;
	double nsegs1 = 20, nsegs2 = 20;
	double du=1/nsegs1;
	double dw=1/nsegs2;

  int k;
  for( k=0,u=0;k<=nsegs1;k++,u+=du)
  {
	   qx = UW2XYZ(u, w, m_guideXs);
	   qy = UW2XYZ(u, w, m_guideYs);
	   qz = UW2XYZ(u, w, m_guideZs);
	   dc.MoveTo(qx, -qy);
	   for( i=0,w=0;i<=nsegs2;i++,w+=dw)
		{
		   qx = UW2XYZ(u, w, m_guideXs);
		   qy = UW2XYZ(u, w, m_guideYs);
		   qz = UW2XYZ(u, w, m_guideZs);
		   dc.LineTo(qx, -qy);
  		}
		w=w-dw;
   }
//****
w=0;
u=0;
for( k=0,w=0;k<=nsegs1;k++,w+=dw)
  {
   qx = UW2XYZ(u, w, m_guideXs);
   qy = UW2XYZ(u, w, m_guideYs);
   qz = UW2XYZ(u, w, m_guideZs);

   dc.MoveTo(qx, -qy);
   for( i=0,u=0;i<=nsegs2;i++,u+=du)
   {
   qx = UW2XYZ(u, w, m_guideXs);
   qy = UW2XYZ(u, w, m_guideYs);
   qz = UW2XYZ(u, w, m_guideZs);
   dc.LineTo(qx, -qy);
   }
   u=u-du;
   }
}

double CBilinearSurface::UW2XYZ(double u, double w, double* points)
{
//	return (1-u)*(1-w)*points[0]+(1-u)*w*points[1]+(1-w)*u*points[2]+u*w*points[3];
	return ((points[0]*(1-u)*(1-w))+(points[3]*(1-u)*w)+(points[1]*u*(1-w))+(points[2]*u*w));
}

/***************************************************/
CLoftedSurface::CLoftedSurface(void)
{
	m_loftMode = 0;
}

CLoftedSurface::~CLoftedSurface(void)
{
}

void CLoftedSurface::DrawGraphObject(CDC &dc, bool closed)
{
	switch (m_loftMode)
	{
	case 0:
		ClampedEnd(dc);
		break;
	case 1:
		RelaxedEnd(dc);
		break;
	case 2:
		Cyclic(dc);
		break;
	case 3:
		AntiCyclic(dc);
		break;
	default:
		ClampedEnd(dc);
		break;
	}
}

void CLoftedSurface::ClampedEnd(CDC &dc)
{
	POSITION pos = m_points.GetHeadPosition();
	double surfX[4], surfY[4], surfZ[4];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	surfX[0] = pt.GetX();
	surfY[0] = pt.GetY();
	surfZ[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		surfX[i] = pt.GetX();
		surfY[i] = pt.GetY();
		surfZ[i] = pt.GetZ();
	}
	
	int iu,iw,X,Y,B;
	float u,w,derx,dery,derz;
	float B11x,B12x,B13x,B14x,B21x,B22x,B23x,B24x;
	float B11y,B12y,B13y,B14y,B21y,B22y,B23y,B24y;
	float B11z,B12z,B13z,B14z,B21z,B22z,B23z,B24z;
	float P0x,P0y,P1x,P1y,Qx[30][30],Qy[30][30];
	float P0z,P1z,Qz[30][30];

	derx=100;dery=-100, derz=-100;
	B11x=surfX[0];
	B11y=surfY[0];
	B11z = surfZ[0];
	B12x=derx;
	B12y=dery;
	B12z = derz;

	B13x=3*(surfX[1]-surfX[0])-(2*derx)-derx;
	B13y=3*(surfY[1]-surfY[0])-(2*dery)-dery;
	B13z=3*(surfZ[1]-surfZ[0])-(2*derz)-derz;

	B14x=2*(surfX[0]-surfX[1])+derx+derx;
	B14y=2*(surfY[0]-surfY[1])+dery+dery;
	B14z=2*(surfZ[0]-surfZ[1])+derz+derz;

	B21x=surfX[2];B21y=surfY[2];B21z=surfZ[2];
	B22x=derx;B22y=dery; B22z = derz;
	
	B23x=3*(surfX[3]-surfX[2])-(2*derx)-derx;
	B23y=3*(surfY[3]-surfY[2])-(2*dery)-dery;
	B23z=3*(surfZ[3]-surfZ[2])-(2*derz)-derz;

	B24x=2*(surfX[2]-surfX[3])+derx+derx;
	B24y=2*(surfY[2]-surfY[3])+dery+dery;
	B24z=2*(surfZ[2]-surfZ[3])+derz+derz;

	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		P0x=B11x+B12x*u+B13x*u*u+B14x*u*u*u;
		P0y=B11y+B12y*u+B13y*u*u+B14y*u*u*u;
		P0z=B11z+B12z*u+B13z*u*u+B14z*u*u*u;
		P1x=B21x+B22x*u+B23x*u*u+B24x*u*u*u;
		P1y=B21y+B22y*u+B23y*u*u+B24y*u*u*u;
		P1z=B21z+B22z*u+B23z*u*u+B24z*u*u*u;

		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			Qx[iu][iw] =P0x*(1-w)+P1x*w;
			Qy[iu][iw] =P0y*(1-w)+P1y*w;
			Qz[iu][iw] =P0z*(1-w)+P1z*w;
		}
	} // for iw

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Qx[iu][iw-1],-Qy[iu][iw-1]);
			dc.LineTo(Qx[iu][iw],-Qy[iu][iw]);
		}
		if (iu>0)
		{
			dc.MoveTo(Qx[iu-1][iw],-Qy[iu-1][iw]);
			dc.LineTo(Qx[iu][iw], -Qy[iu][iw]);
		}
		} //for iw
	} // for iu
}

void CLoftedSurface::RelaxedEnd(CDC &dc)
{
	POSITION pos = m_points.GetHeadPosition();
	double surfX[4], surfY[4], surfZ[4];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	surfX[0] = pt.GetX();
	surfY[0] = pt.GetY();
	surfZ[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		surfX[i] = pt.GetX();
		surfY[i] = pt.GetY();
		surfZ[i] = pt.GetZ();
	}
	
	int iu,iw,X,Y,B;
	float u,w,der11x,der11y,der11z,der12x,der12y,der12z;
	float der21x,der21y,der21z,der22x,der22y,der22z;
	float B11x,B12x,B13x,B14x,B21x,B22x,B23x,B24x;
	float B11y,B12y,B13y,B14y,B21y,B22y,B23y,B24y;
	float B11z,B12z,B13z,B14z,B21z,B22z,B23z,B24z;
	float P0x,P0y,P1x,P1y,Qx[30][30],Qy[30][30];
	float P0z,P1z,Qz[30][30];

	//calculate the end point derivatives

	der11x = (surfX[1]-surfX[0]);
	der11y = (surfY[1]-surfY[0]);
	der11z = (surfZ[1]-surfZ[0]);

	der21x = surfX[3]-surfX[2];
	der21y = surfY[3]-surfY[2];
	der21z = surfZ[3]-surfZ[2];

	der12x = 0;
	der12y = 0;
	der12z = 0;

	der22x = 0;
	der22y = 0;
	der22z = 0;
	//draw the first cubic spline
	B11x=surfX[0];
	B11y=surfY[0];
	B11z = surfZ[0];
	
	B12x=der11x;
	B12y=der11y;
	B12z = der11z;

	B13x=3*(surfX[1]-surfX[0])-(2*der11x)-der12x;
	B13y=3*(surfY[1]-surfY[0])-(2*der11y)-der12y;
	B13z=3*(surfZ[1]-surfZ[0])-(2*der11z)-der12z;

	B14x=2*(surfX[0]-surfX[1])+der11x+der12x;
	B14y=2*(surfY[0]-surfY[1])+der11y+der12y;
	B14z=2*(surfZ[0]-surfZ[1])+der11z+der12z;

	//draw the second cubic spline
	B21x=surfX[2];B21y=surfY[2];B21z=surfZ[2];
	B22x=der21x;B22y=der21y; B22z = der21z;
	
	B23x=3*(surfX[3]-surfX[2])-(2*der21x)-der22x;
	B23y=3*(surfY[3]-surfY[2])-(2*der21y)-der22y;
	B23z=3*(surfZ[3]-surfZ[2])-(2*der21z)-der22z;

	B24x=2*(surfX[2]-surfX[3])+der21x+der22x;
	B24y=2*(surfY[2]-surfY[3])+der21y+der22y;
	B24z=2*(surfZ[2]-surfZ[3])+der21z+der22z;

	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		P0x=B11x+B12x*u+B13x*u*u+B14x*u*u*u;
		P0y=B11y+B12y*u+B13y*u*u+B14y*u*u*u;
		P0z=B11z+B12z*u+B13z*u*u+B14z*u*u*u;
		P1x=B21x+B22x*u+B23x*u*u+B24x*u*u*u;
		P1y=B21y+B22y*u+B23y*u*u+B24y*u*u*u;
		P1z=B21z+B22z*u+B23z*u*u+B24z*u*u*u;

		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			Qx[iu][iw] =P0x*(1-w)+P1x*w;
			Qy[iu][iw] =P0y*(1-w)+P1y*w;
			Qz[iu][iw] =P0z*(1-w)+P1z*w;
		}
	} // for iw

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Qx[iu][iw-1],-Qy[iu][iw-1]);
			dc.LineTo(Qx[iu][iw],-Qy[iu][iw]);
		}
		if (iu>0)
		{
			dc.MoveTo(Qx[iu-1][iw],-Qy[iu-1][iw]);
			dc.LineTo(Qx[iu][iw], -Qy[iu][iw]);
		}
		} //for iw
	} // for iu
}

void CLoftedSurface::Cyclic(CDC &dc)
{
	POSITION pos = m_points.GetHeadPosition();
	double surfX[4], surfY[4], surfZ[4];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	surfX[0] = pt.GetX();
	surfY[0] = pt.GetY();
	surfZ[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		surfX[i] = pt.GetX();
		surfY[i] = pt.GetY();
		surfZ[i] = pt.GetZ();
	}
	
	int iu,iw,X,Y,B;
	float u,w,der11x,der11y,der11z,der12x,der12y,der12z;
	float der21x,der21y,der21z,der22x,der22y,der22z;
	float B11x,B12x,B13x,B14x,B21x,B22x,B23x,B24x;
	float B11y,B12y,B13y,B14y,B21y,B22y,B23y,B24y;
	float B11z,B12z,B13z,B14z,B21z,B22z,B23z,B24z;
	float P0x,P0y,P1x,P1y,Qx[30][30],Qy[30][30];
	float P0z,P1z,Qz[30][30];

	//calculate the end point derivatives

	der11x = (surfX[1]-surfX[0]);
	der11y = (surfY[1]-surfY[0]);
	der11z = (surfZ[1]-surfZ[0]);

	der21x = (surfX[3]-surfX[2]);
	der21y = (surfY[3]-surfY[2]);
	der21z = (surfZ[3]-surfZ[2]);

	der12x = der11x;
	der12y = der11y;
	der12z = der11z;

	der22x = der21x;
	der22y = der21y;
	der22z = der21z;
	//draw the first cubic spline
	B11x=surfX[0];
	B11y=surfY[0];
	B11z = surfZ[0];
	
	B12x=der11x;
	B12y=der11y;
	B12z = der11z;

	B13x=3*(surfX[1]-surfX[0])-(2*der11x)-der12x;
	B13y=3*(surfY[1]-surfY[0])-(2*der11y)-der12y;
	B13z=3*(surfZ[1]-surfZ[0])-(2*der11z)-der12z;

	B14x=2*(surfX[0]-surfX[1])+der11x+der12x;
	B14y=2*(surfY[0]-surfY[1])+der11y+der12y;
	B14z=2*(surfZ[0]-surfZ[1])+der11z+der12z;

	//draw the second cubic spline
	B21x=surfX[2];B21y=surfY[2];B21z=surfZ[2];
	B22x=der21x;B22y=der21y; B22z = der21z;
	
	B23x=3*(surfX[3]-surfX[2])-(2*der21x)-der22x;
	B23y=3*(surfY[3]-surfY[2])-(2*der21y)-der22y;
	B23z=3*(surfZ[3]-surfZ[2])-(2*der21z)-der22z;

	B24x=2*(surfX[2]-surfX[3])+der21x+der22x;
	B24y=2*(surfY[2]-surfY[3])+der21y+der22y;
	B24z=2*(surfZ[2]-surfZ[3])+der21z+der22z;

	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		P0x=B11x+B12x*u+B13x*u*u+B14x*u*u*u;
		P0y=B11y+B12y*u+B13y*u*u+B14y*u*u*u;
		P0z=B11z+B12z*u+B13z*u*u+B14z*u*u*u;
		P1x=B21x+B22x*u+B23x*u*u+B24x*u*u*u;
		P1y=B21y+B22y*u+B23y*u*u+B24y*u*u*u;
		P1z=B21z+B22z*u+B23z*u*u+B24z*u*u*u;

		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			Qx[iu][iw] =P0x*(1-w)+P1x*w;
			Qy[iu][iw] =P0y*(1-w)+P1y*w;
			Qz[iu][iw] =P0z*(1-w)+P1z*w;
		}
	} // for iw

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Qx[iu][iw-1],-Qy[iu][iw-1]);
			dc.LineTo(Qx[iu][iw],-Qy[iu][iw]);
		}
		if (iu>0)
		{
			dc.MoveTo(Qx[iu-1][iw],-Qy[iu-1][iw]);
			dc.LineTo(Qx[iu][iw], -Qy[iu][iw]);
		}
		} //for iw
	} // for iu

}

void CLoftedSurface::AntiCyclic(CDC &dc)
{
	POSITION pos = m_points.GetHeadPosition();
	double surfX[4], surfY[4], surfZ[4];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	surfX[0] = pt.GetX();
	surfY[0] = pt.GetY();
	surfZ[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		surfX[i] = pt.GetX();
		surfY[i] = pt.GetY();
		surfZ[i] = pt.GetZ();
	}
	
	int iu,iw,X,Y,B;
	float u,w,der11x,der11y,der11z,der12x,der12y,der12z;
	float der21x,der21y,der21z,der22x,der22y,der22z;
	float B11x,B12x,B13x,B14x,B21x,B22x,B23x,B24x;
	float B11y,B12y,B13y,B14y,B21y,B22y,B23y,B24y;
	float B11z,B12z,B13z,B14z,B21z,B22z,B23z,B24z;
	float P0x,P0y,P1x,P1y,Qx[30][30],Qy[30][30];
	float P0z,P1z,Qz[30][30];

	//calculate the end point derivatives

	der11x = 0;
	der11y = 0;
	der11z = 0;

	der21x = 0;
	der21y = 0;
	der21z = 0;

	der12x = -der11x;
	der12y = -der11y;
	der12z = -der11z;

	der22x = -der21x;
	der22y = -der21y;
	der22z = -der21z;
	//draw the first cubic spline
	B11x=surfX[0];
	B11y=surfY[0];
	B11z = surfZ[0];
	
	B12x=der11x;
	B12y=der11y;
	B12z = der11z;

	B13x=3*(surfX[1]-surfX[0])-(2*der11x)-der12x;
	B13y=3*(surfY[1]-surfY[0])-(2*der11y)-der12y;
	B13z=3*(surfZ[1]-surfZ[0])-(2*der11z)-der12z;

	B14x=2*(surfX[0]-surfX[1])+der11x+der12x;
	B14y=2*(surfY[0]-surfY[1])+der11y+der12y;
	B14z=2*(surfZ[0]-surfZ[1])+der11z+der12z;

	//draw the second cubic spline
	B21x=surfX[2];B21y=surfY[2];B21z=surfZ[2];
	B22x=der21x;B22y=der21y; B22z = der21z;
	
	B23x=3*(surfX[3]-surfX[2])-(2*der21x)-der22x;
	B23y=3*(surfY[3]-surfY[2])-(2*der21y)-der22y;
	B23z=3*(surfZ[3]-surfZ[2])-(2*der21z)-der22z;

	B24x=2*(surfX[2]-surfX[3])+der21x+der22x;
	B24y=2*(surfY[2]-surfY[3])+der21y+der22y;
	B24z=2*(surfZ[2]-surfZ[3])+der21z+der22z;

	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		P0x=B11x+B12x*u+B13x*u*u+B14x*u*u*u;
		P0y=B11y+B12y*u+B13y*u*u+B14y*u*u*u;
		P0z=B11z+B12z*u+B13z*u*u+B14z*u*u*u;
		P1x=B21x+B22x*u+B23x*u*u+B24x*u*u*u;
		P1y=B21y+B22y*u+B23y*u*u+B24y*u*u*u;
		P1z=B21z+B22z*u+B23z*u*u+B24z*u*u*u;

		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			Qx[iu][iw] =P0x*(1-w)+P1x*w;
			Qy[iu][iw] =P0y*(1-w)+P1y*w;
			Qz[iu][iw] =P0z*(1-w)+P1z*w;
		}
	} // for iw

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Qx[iu][iw-1],-Qy[iu][iw-1]);
			dc.LineTo(Qx[iu][iw],-Qy[iu][iw]);
		}
		if (iu>0)
		{
			dc.MoveTo(Qx[iu-1][iw],-Qy[iu-1][iw]);
			dc.LineTo(Qx[iu][iw], -Qy[iu][iw]);
		}
		} //for iw
	} // for iu

}

/**************************************************/

CBicubicCoonsSurface::CBicubicCoonsSurface(void)
{
	int i, j, k;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 3; k++)
			{
				Mm[i][j][k] = 0;
			}
		}
	}
}

CBicubicCoonsSurface::~CBicubicCoonsSurface(void)
{
}

void CBicubicCoonsSurface::DrawGraphObject(CDC &dc, bool closed)
{
	double Pm[4][4][3];
	POSITION pos = m_points.GetHeadPosition();
	float R[20][20][3];

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	Mm[0][0][0] = pt.GetX();
	Mm[0][0][1] = pt.GetY();
	Mm[0][0][2] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		Mm[0][i][0] = pt.GetX();
		Mm[0][i][1] = pt.GetY();
		Mm[0][i][2] = pt.GetZ();
	}
	
	float sample;
	float Q_C[30][30][3];
	int j,k,iw,iu;
	float u,w,Fu[4],Fw[4],sum[4],sum2,sum1;

	for (j=0;j<3;j++)
		Pm[0][0][j]=Mm[0][0][j];
	for (j=0;j<3;j++)
		Pm[0][1][j]=Mm[0][1][j];
	for (j=0;j<3;j++)
		Pm[0][2][j]=Mm[1][0][j];
	for (j=0;j<3;j++)
		Pm[0][3][j]=Mm[1][1][j];

	for (j=0;j<3;j++)
		Pm[1][0][j]=Mm[0][2][j];
	for (j=0;j<3;j++)
		Pm[1][1][j]=Mm[0][3][j];
	for (j=0;j<3;j++)
		Pm[1][2][j]=Mm[1][2][j];
	for (j=0;j<3;j++)
		Pm[1][3][j]=Mm[1][3][j];

	for (j=0;j<3;j++)
		Pm[2][0][j]=Mm[2][0][j];
	for (j=0;j<3;j++)
		Pm[2][1][j]=Mm[2][1][j];
	for (j=0;j<3;j++)
		Pm[2][2][j]=Mm[3][0][j];
	for (j=0;j<3;j++)
		Pm[2][3][j]=Mm[3][1][j];

	for (j=0;j<3;j++)
		Pm[3][0][j]=Mm[2][2][j];
	for (j=0;j<3;j++)
		Pm[3][1][j]=Mm[2][3][j];
	for (j=0;j<3;j++)
		Pm[3][2][j]=Mm[3][2][j];
	for (j=0;j<3;j++)
		Pm[3][3][j]=Mm[3][3][j];


	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		Fu[0]=(2*u*u*u)-(3*u*u)+1;
		Fu[1]=-(2*u*u*u)+(3*u*u);
		Fu[2]=(u*u*u)-(2*u*u)+u;
		Fu[3]=(u*u*u)-(u*u);
		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			sum[0]=0;sum[1]=0;sum[2]=0;sum[3]=0;
			Fw[0]=(2*w*w*w)-(3*w*w)+1;
			Fw[1]=-(2*w*w*w)+(3*w*w);
			Fw[2]=(w*w*w)-(2*w*w)+w;
			Fw[3]=(w*w*w)-(w*w);
			for (k=0;k<3;k++)
			{
				sum2=0;
				for (i=0;i<4;i++)
				{
					sum1=0;
					for (j=0;j<4;j++)
						sum1=Fw[j]*Pm[i][j][k]+sum1;
					sum[i]=sum1;
				}
				for (i=0;i<4;i++)
				{
					sum2 =Fu[i]*sum[i]+sum2;
				}
				Q_C[iu][iw][k]=sum2;
			}
		}
	}

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Q_C[iu][iw-1][0],-Q_C[iu][iw-1][1]);
			dc.LineTo(Q_C[iu][iw][0],-Q_C[iu][iw][1]);
		}
		if (iu>0)
		{
			dc.MoveTo(Q_C[iu-1][iw][0],-Q_C[iu-1][iw][1]);
			dc.LineTo(Q_C[iu][iw][0],-Q_C[iu][iw][1]);
		}
		} //for iw
	} // for iu
}


/**************************************************/

CLinearCoonsSurface::CLinearCoonsSurface(void)
{
	int i, j, k;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 3; k++)
			{
				Mm[i][j][k] = 0;
			}
		}
	}
}

CLinearCoonsSurface::~CLinearCoonsSurface(void)
{
}

void CLinearCoonsSurface::DrawGraphObject(CDC &dc, bool closed)
{
	double Pm[4][4][3];
	POSITION pos = m_points.GetHeadPosition();
	float R[20][20][3];
	float B11x,B12x,B13x,B14x,B21x,B22x,B23x,B24x;
	float B11y,B12y,B13y,B14y,B21y,B22y,B23y,B24y;
	float B11z,B12z,B13z,B14z,B21z,B22z,B23z,B24z;

	float B31x,B32x,B33x,B34x,B41x,B42x,B43x,B44x;
	float B31y,B32y,B33y,B34y,B41y,B42y,B43y,B44y;
	float B31z,B32z,B33z,B34z,B41z,B42z,B43z,B44z;

	double surfX[4], surfY[4], surfZ[4];

	float P0x,P0y,P0z,P1x,P1y,P1z,P2x,P2y,P2z,P3x,P3y,P3z;

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	Mm[0][0][0] = pt.GetX();
	Mm[0][0][1] = pt.GetY();
	Mm[0][0][2] = pt.GetZ();
	surfX[0] = pt.GetX();
	surfY[0] = pt.GetY();
	surfZ[0] = pt.GetZ();

	int i;
	for(i = 1; i < 4; i++)
	{
		pt = m_points.GetNext(pos);
		Mm[0][i][0] = pt.GetX();
		Mm[0][i][1] = pt.GetY();
		Mm[0][i][2] = pt.GetZ();
		surfX[i] = pt.GetX();
		surfY[i] = pt.GetY();
		surfZ[i] = pt.GetZ();
	}
	
	float sample;
	float Q_C[30][30][3];
	int j,k,iw,iu;
	float u,w,Fu[4],Fw[4],sum[4],sum2,sum1;

	//estimate B coefficients fur P(u,0) and P(u,1)
	B11x=surfX[0];
	B11y=surfY[0];
	B11z = surfZ[0];
	B12x=Mm[1][0][0];
	B12y=Mm[1][0][1];
	B12z = Mm[1][0][2];

	B13x=3*(surfX[1]-surfX[0])-(2*Mm[1][0][0])-Mm[1][1][0];
	B13y=3*(surfY[1]-surfY[0])-(2*Mm[1][0][1])-Mm[1][1][1];
	B13z=3*(surfZ[1]-surfZ[0])-(2*Mm[1][0][2])-Mm[1][1][2];

	B14x=2*(surfX[0]-surfX[1])+Mm[1][0][0]+Mm[1][1][0];
	B14y=2*(surfY[0]-surfY[1])+Mm[1][0][1]+Mm[1][1][1];
	B14z=2*(surfZ[0]-surfZ[1])+Mm[1][0][2]+Mm[1][1][2];

	//draw the second cubic spline
	B21x=surfX[2];B21y=surfY[2];B21z=surfZ[2];
	B22x=Mm[1][2][0];B22y=Mm[1][2][1]; B22z = Mm[1][2][2];
	
	B23x=3*(surfX[3]-surfX[2])-(2*Mm[1][2][0])-Mm[1][3][0];
	B23y=3*(surfY[3]-surfY[2])-(2*Mm[1][2][1])-Mm[1][3][1];
	B23z=3*(surfZ[3]-surfZ[2])-(2*Mm[1][2][2])-Mm[1][3][2];

	B24x=2*(surfX[2]-surfX[3])+Mm[1][2][0]+Mm[1][3][0];
	B24y=2*(surfY[2]-surfY[3])+Mm[1][2][1]+Mm[1][3][1];
	B24z=2*(surfZ[2]-surfZ[3])+Mm[1][2][2]+Mm[1][3][2];

	//estimate B coefficients fur P(w,0) and P(w,1)
	B31x=surfX[0];
	B31y=surfY[0];
	B31z = surfZ[0];
	B32x=Mm[2][0][0];
	B32y=Mm[2][0][1];
	B32z = Mm[2][0][2];

	B33x=3*(surfX[1]-surfX[0])-(2*Mm[2][0][0])-Mm[2][1][0];
	B33y=3*(surfY[1]-surfY[0])-(2*Mm[2][0][1])-Mm[2][1][1];
	B33z=3*(surfZ[1]-surfZ[0])-(2*Mm[2][0][2])-Mm[2][1][2];

	B34x=2*(surfX[0]-surfX[1])+Mm[2][0][0]+Mm[2][1][0];
	B34y=2*(surfY[0]-surfY[1])+Mm[2][0][1]+Mm[2][1][1];
	B34z=2*(surfZ[0]-surfZ[1])+Mm[2][0][2]+Mm[2][1][2];

	//draw the second cubic spline
	B41x=surfX[2];B41y=surfY[2];B41z=surfZ[2];
	B42x=Mm[2][2][0];B42y=Mm[2][2][1]; B42z = Mm[2][2][2];
	
	B43x=3*(surfX[3]-surfX[2])-(2*Mm[2][2][0])-Mm[2][3][0];
	B43y=3*(surfY[3]-surfY[2])-(2*Mm[2][2][1])-Mm[2][3][1];
	B43z=3*(surfZ[3]-surfZ[2])-(2*Mm[2][2][2])-Mm[2][3][2];

	B44x=2*(surfX[2]-surfX[3])+Mm[2][2][0]+Mm[2][3][0];
	B44y=2*(surfY[2]-surfY[3])+Mm[2][2][1]+Mm[2][3][1];
	B44z=2*(surfZ[2]-surfZ[3])+Mm[2][2][2]+Mm[2][3][2];

	for (iu=0;iu<=15;iu++)
	{
		u=float(iu)/15;
		P0x=B11x+B12x*u+B13x*u*u+B14x*u*u*u;
		P0y=B11y+B12y*u+B13y*u*u+B14y*u*u*u;
		P0z=B11z+B12z*u+B13z*u*u+B14z*u*u*u;
		P1x=B21x+B22x*u+B23x*u*u+B24x*u*u*u;
		P1y=B21y+B22y*u+B23y*u*u+B24y*u*u*u;
		P1z=B21z+B22z*u+B23z*u*u+B24z*u*u*u;

		for (iw=0;iw<=15;iw++)
		{
			w=float(iw)/15;
			
			P2x=B31x+B32x*w+B33x*w*w+B34x*w*w*w;
			P2y=B31y+B32y*w+B33y*w*w+B34y*w*w*w;
			P2z=B31z+B32z*w+B33z*w*w+B34z*w*w*w;
			P3x=B41x+B42x*w+B43x*w*w+B44x*w*w*w;
			P3y=B41y+B42y*w+B43y*w*w+B44y*w*w*w;
			P3z=B41z+B42z*w+B43z*w*w+B44z*w*w*w;

			Q_C[iu][iw][0] = P0x*(1-w)+P1x*w + P2x*(1-u) + P3x*u - surfX[0]*(1-u)*(1-w) - surfX[1]*(1-u)*w - surfX[2]*u*(1-w) - surfX[3]*u*w;
			Q_C[iu][iw][1] = P0y*(1-w)+P1y*w + P2y*(1-u) + P3y*u - surfY[0]*(1-u)*(1-w) - surfY[1]*(1-u)*w - surfY[2]*u*(1-w) - surfY[3]*u*w;
			Q_C[iu][iw][2] = P0z*(1-w)+P1z*w + P2z*(1-u) + P3z*u - surfZ[0]*(1-u)*(1-w) - surfZ[1]*(1-u)*w - surfZ[2]*u*(1-w) - surfZ[3]*u*w;
		}
	}

	for (iu=0;iu<=15;iu++)
	{
		for (iw=0;iw<=15;iw++)
		{
		if (iw>0)
		{
			dc.MoveTo(Q_C[iu][iw-1][0],-Q_C[iu][iw-1][1]);
			dc.LineTo(Q_C[iu][iw][0],-Q_C[iu][iw][1]);
		}
		if (iu>0)
		{
			dc.MoveTo(Q_C[iu-1][iw][0],-Q_C[iu-1][iw][1]);
			dc.LineTo(Q_C[iu][iw][0],-Q_C[iu][iw][1]);
		}
		} //for iw
	} // for iu
}

/***************************************************/
CBezierSurface::CBezierSurface(void)
{
}

CBezierSurface::~CBezierSurface(void)
{
}

float CBezierSurface::fact(int n)
{
	if (n==0) return 1;
	if (n==1) return 1;
	float f=1;
	int i;
	for (i=1;i<=n;i++)
		f=f*i;
	return f;
} // end of fact

void CBezierSurface::DrawGraphObject(CDC &dc, bool closed)
{
	float Bm[10][10][3],Q_C[30][30][3];
	float u,w,Fu[10],Fw[10],sum[10],J[10],K[10],sum2,sum1;
	int iu, iw,k;
	float R[20][20][3];

	POSITION pos = m_points.GetHeadPosition();

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	Bm[0][0][0] = pt.GetX();
	Bm[0][0][1] = pt.GetY();
	Bm[0][0][2] = pt.GetZ();

	int i, j;
	for(i = 0; i < num_u; i++)
	{
		for (j = 0; j < num_w; j++)
		{
			if ((i!=0) || (j!=0))
			{
				pt = m_points.GetNext(pos);
				Bm[i][j][0] = pt.GetX();
				Bm[i][j][1] = pt.GetY();
				Bm[i][j][2] = pt.GetZ();
			}
		}
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, 0xf0f000);
	CPen* pOld = dc.SelectObject(&pen);
	LOGPEN lpen;
	pOld->GetLogPen(&lpen);
	if (lpen.lopnColor == 0x00ff80)
	{
		dc.SelectObject(pOld);
	}
	else
	{
		//	setcolor(LIGHTBLUE);
		for (i=0;i<num_u;i++)
		{
			for(j=1;j<num_w;j++)
			{
				dc.MoveTo(Bm[i][j-1][0], -Bm[i][j-1][1]);
				dc.LineTo(Bm[i][j][0], -Bm[i][j][1]);
			}
		}
		for (i=0;i<num_w;i++)
		{
			for(j=1;j<num_u;j++)
			{
				dc.MoveTo(Bm[j-1][i][0], -Bm[j-1][i][1]);
				dc.LineTo(Bm[j][i][0], -Bm[j][i][1]);
			}
		}
		
		
		
		for(i=0;i<num_u;i++)
			J[i]=fact(num_u-1)/(fact(num_u-1-i)*fact(i));
		for(i=0;i<num_w;i++)
			K[i]=fact(num_w-1)/(fact(num_w-1-i)*fact(i));
		
		for (iu=0;iu<=15;iu++)
		{
			u=float(iu)/15;
			for (iw=0;iw<=15;iw++)
			{
				w=float(iw)/15;
				sum[0]=0;sum[1]=0;sum[2]=0;sum[3]=0;
				for (k=0;k<3;k++)
				{
					sum2=0;
					for (i=0;i<num_u;i++)
					{
						sum1=0;
						for (j=0;j<num_w;j++)
						{
							if (w==0)
							{
								Fw[j]=0;
								Fw[0]=K[j];
							}
							else if (w==1)
							{
								Fw[j]=0;
								Fw[num_w-1]=K[j];
							}
							else
								Fw[j]=K[j]*pow(w,j)*pow((1-w),(num_w-1-j));
							sum1=Fw[j]*Bm[i][j][k]+sum1;
						}
						sum[i]=sum1;
					}
					for (i=0;i<num_u;i++)
					{
						if (u==0)
						{
							Fu[i]=0;
							Fu[0]=J[i];
						}
						else if (u==1)
						{
							Fu[i]=0;
							Fu[num_u-1]=J[i];
						}
						else
							Fu[i]=J[i]*pow(u,i)*pow((1-u),(num_u-1-i));
						sum2 =Fu[i]*sum[i]+sum2;
					}
					Q_C[iu][iw][k]=sum2;
				}
			}
		}
		
		for (k=0;k<2;k++)
		{
			for (j=0;j<=15;j++)
			{
				for (i=0;i<=15;i++)
				{
					R[i][j][k]=Q_C[i][j][k];
				}
			}
		}
		dc.SelectObject(pOld);
		//	setcolor(YELLOW);
		for (iu=0;iu<=15;iu++)
		{
			for (iw=0;iw<=15;iw++)
			{
				if (iw>0)
				{
					dc.MoveTo(Q_C[iu][iw-1][0], -Q_C[iu][iw-1][1]);
					dc.LineTo(Q_C[iu][iw][0], -Q_C[iu][iw][1]);
				}
				if (iu>0)
				{
					dc.MoveTo(Q_C[iu-1][iw][0], -Q_C[iu-1][iw][1]);
					dc.LineTo(Q_C[iu][iw][0], -Q_C[iu][iw][1]);
				}
			} //for iw
		} // for iu
	}
	pen.DeleteObject();

}


/***************************************************/
CBSplineSurface::CBSplineSurface(void)
{
}

CBSplineSurface::~CBSplineSurface(void)
{
}

float CBSplineSurface::fact(int n)
{
	if (n==0) return 1;
	if (n==1) return 1;
	float f=1;
	int i;
	for (i=1;i<=n;i++)
		f=f*i;
	return f;
} // end of fact

void CBSplineSurface::DrawGraphObject(CDC &dc, bool closed)
{
	int i,j,ku,kw,s,tmaxu,tmaxw,n,m,kindex, k;
	float BSSx[30][30],BSSy[30][30],BSSz[30][30],sample;
	float BSx[10][10],BSy[10][10],BSz[10][10];
	int knotu[10],knotw[10],iu,iw;
	float N[7][7][20],M[7][7][20];
	float temp1,temp2,tempx,tempy,tempz;
	char cline[400];
	FILE *read_stream, *in;
	float u,w;


	float lx[16],ly[16];


	POSITION pos = m_points.GetHeadPosition();

	CGraphPoint pt;
	pt = m_points.GetNext(pos);
	BSx[0][0] = pt.GetX();
	BSy[0][0] = pt.GetY();
	BSz[0][0] = pt.GetZ();

//	int i, j;
	for(i = 0; i < num_n; i++)
	{
		for (j = 0; j < num_m; j++)
		{
			if ((i!=0) || (j!=0))
			{
				pt = m_points.GetNext(pos);
				BSx[i][j] = pt.GetX();
				BSy[i][j] = pt.GetY();
				BSz[i][j] = pt.GetZ();
			}
		}
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, 0xf0f000);
	CPen* pOld = dc.SelectObject(&pen);
	LOGPEN lpen;
	pOld->GetLogPen(&lpen);
	if (lpen.lopnColor == 0x00ff80)
	{
		dc.SelectObject(pOld);
	}
	else
	{
		for (i=0; i<num_n; i++)
		{
			for(j=1; j<num_m; j++)
			{
				dc.MoveTo(BSx[i][j-1], -BSy[i][j-1]);
				dc.LineTo(BSx[i][j], -BSy[i][j]);
			}
		}
		for (i=0; i<num_n; i++)
		{
			for(j=1; j<num_m; j++)
			{
				dc.MoveTo( BSx[j-1][i], -BSy[j-1][i]);
				dc.LineTo( BSx[j][i], -BSy[j][i]);
			}
		}
		
		
		n=4;m=4;ku=4;kw=4;
		
		
		tempx=0;tempy=0;tempz=0;
		n=n-1;
		m=m-1;
		tmaxu=n-ku+2;
		tmaxw=m-kw+2;
		for (i=0;i<ku;i++)
			knotu[i]=0;
		for (i=ku;i<tmaxu+ku-1;i++)
			knotu[i]=i-ku+1;
		for (i=0;i<ku;i++)
			knotu[ku+tmaxu-1+i]=tmaxu;
		
		for (i=0;i<kw;i++)
			knotw[i]=0;
		for (i=kw;i<tmaxw+kw-1;i++)
			knotw[i]=i-kw+1;
		for (i=0;i<kw;i++)
			knotw[kw+tmaxw-1+i]=tmaxw;
		
		
		for (iu=0;iu<=tmaxu*5;iu++)
		{
			u=float(iu)/5/float(tmaxu);
			
			for (k=1;k<=ku;k++)
			{
				kindex=k-1;
				for (i=0;i<=n;i++)
				{
					if(k==1)
					{
						if(((u>=knotu[i])&&(u<knotu[i+1]))||(u==knotu[i]))
							N[i][kindex][iu]=1;
						else
							N[i][kindex][iu]=0;
						if(((u>=knotu[n+1])&&(u<knotu[n+1+1]))||(u==knotu[n+1]))
							N[n+1][kindex][iu]=1;
						else
							N[n+1][kindex][iu]=0;
					}
					else
					{
						if ((knotu[i+k-1]-knotu[i])==0)
							temp1=0;
						else
							temp1=((u-knotu[i])*N[i][kindex-1][iu])/(knotu[i+k-1]-knotu[i]);
						if ((knotu[i+k]-knotu[i+1])==0)
							temp2=0;
						else
							temp2=((knotu[i+k]-u)*N[i+1][kindex-1][iu]/(knotu[i+k]-knotu[i+1]));
						
						N[i][kindex][iu]= (temp1+temp2);
					}
				}
			}
		}
		
		for (iu=0;iu<=tmaxu*5;iu++)
		{
			j=0;
			for (i=0;i<n;i++)
			{
				tempx=((BSx[i][j]*N[i][ku-1][iu])+tempx);
				tempy=((BSy[i][j]*N[i][ku-1][iu])+tempy);
				tempz=((BSz[i][j]*N[i][ku-1][iu])+tempz);
			}
			
			lx[iu]=tempx;
			ly[iu]=tempy;
			
			tempx=0;tempy=0;tempz=0;			
		}
		
		for (iw=0;iw<=tmaxw*5;iw++)
		{
			w=float(iw)/5/float(tmaxw);
			
			for (k=1;k<=kw;k++)
			{
				kindex=k-1;
				for (i=0;i<=n;i++)
				{
					if(k==1)
					{
						if(((w>=knotw[i])&&(w<knotw[i+1]))||(w==knotw[i]))
							M[i][kindex][iw]=1;
						else
							M[i][kindex][iw]=0;
						if(((w>=knotw[m+1])&&(w<knotw[m+1+1]))||(w==knotw[m+1]))
							M[m+1][kindex][iw]=1;
						else
							M[m+1][kindex][iw]=0;
					}
					else
					{
						if ((knotw[i+k-1]-knotw[i])==0)
							temp1=0;
						else
							temp1=((w-knotw[i])*M[i][kindex-1][iw]/(knotw[i+k-1]-knotw[i]));
						if ((knotw[i+k]-knotw[i+1])==0)
							temp2=0;
						else
							temp2=((knotw[i+k]-w)*M[i+1][kindex-1][iw]/(knotw[i+k]-knotw[i+1]));
						
						M[i][kindex][iw]=(temp1+temp2);
					}
				}
			}
		}
		
		for (iu=0;iu<=tmaxu*5;iu++)
		{
			for (iw=0;iw<=tmaxw*5;iw++)
			{
				for (i=0;i<n;i++)
				{
					for (j=0;j<m;j++)
					{
						tempx=((BSx[i][j]*N[i][ku-1][iu]*M[j][kw-1][iw])+tempx);
						tempy=((BSy[i][j]*N[i][ku-1][iu]*M[j][kw-1][iw])+tempy);
						tempz=((BSz[i][j]*N[i][ku-1][iu]*M[j][kw-1][iw])+tempz);
					}
				}
				BSSx[iu][iw]=tempx;
				BSSy[iu][iw]=tempy;
				BSSz[iu][iw]=tempz;
				tempx=0;tempy=0;tempz=0;
			}
		}
		
		dc.SelectObject(pOld);
		for (iu=0;iu<=15;iu++)
		{
			for (iw=0;iw<=15;iw++)
			{
				if (iw>0)
				{
					dc.MoveTo(BSSx[iu][iw-1], -BSSy[iu][iw-1]);
					dc.LineTo(BSSx[iu][iw], -BSSy[iu][iw]);
				}
				if (iu>0)
				{
					dc.MoveTo(BSSx[iu-1][iw], -BSSy[iu-1][iw]);
					dc.LineTo(BSSx[iu][iw], -BSSy[iu][iw]);
				}
			} //for iw
		} // for iu
	}

	pen.DeleteObject();
}


double calculateN(int i,double t,int k, int xknot[10])
{
	double w,w1,q,a,res;
	if(k==1)
	{
		if((xknot[i]<=t)&&(t<xknot[i+1])) res=1;
		else res=0;
	}
	else
	{
		w=xknot[i+k-1]-xknot[i];
		w1=xknot[i+k]-xknot[i+1];
		if(w==0) w=99999;
		if(w1==0) w1=99999;
		q=((t-xknot[i])*calculateN(i,t,k-1,xknot))/w;
		a=((xknot[i+k]-t)*calculateN(i+1,t,k-1,xknot))/w1;
		res=(q+a);
	}
	return res;
}
