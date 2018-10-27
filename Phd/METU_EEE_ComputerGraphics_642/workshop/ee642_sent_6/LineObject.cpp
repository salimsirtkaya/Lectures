#include "stdafx.h"
#include "compgraphobject.h"

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

	der11x = surfX[1]-surfX[0];
	der11y = surfY[1]-surfY[0];
	der11z = surfZ[1]-surfZ[0];

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

	der11x = surfX[1]-surfX[0];
	der11y = surfY[1]-surfY[0];
	der11z = surfZ[1]-surfZ[0];

	der21x = surfX[3]-surfX[2];
	der21y = surfY[3]-surfY[2];
	der21z = surfZ[3]-surfZ[2];

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