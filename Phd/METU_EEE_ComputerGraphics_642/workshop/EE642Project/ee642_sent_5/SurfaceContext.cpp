#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CSurfaceContext* CSurfaceContext::m_context = 0;

CSurfaceContext::CSurfaceContext()
{
	recentInputPointCount = 0;

	m_contextName = "Main Menu";
	m_contextInfo = "Main Menu -- You can select an action from the upper right buttons. You can load a predefined object from the 'LOAD' menu. You can draw an arbitrary 2D Object or many type of plane curves from the 'DRAW' menu. You can apply transformation on objects from the 'EDIT' menu. You can close this program by clicking 'EXIT' button.";
	m_menuCount = 4;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Draw a 2D object to render";
	m_menuItems[0].menuText = "Bilinear Surface";
	m_menuItems[1].menuInfo = "Select a transformation on the current graphics object";
	m_menuItems[1].menuText = "Lofted Surface";
	m_menuItems[2].menuInfo = "Draw a 3D object to render";
	m_menuItems[2].menuText = "Edit";
	m_menuItems[3].menuInfo = "Select a transformation on the current 3D graphics object";
	m_menuItems[3].menuText = "Main";
}

CSurfaceContext::~CSurfaceContext()
{
}

CUserContext* CSurfaceContext::GetInstance()
{
	if (CSurfaceContext::m_context == 0)
	{
		CSurfaceContext::m_context = new CSurfaceContext();
	}
	return CSurfaceContext::m_context;
}

void CSurfaceContext::Menu1Selected()
{
	CUserContext::Menu1Selected();

	ApplyTransformation = this->BilinearSurface;
	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");
}

void CSurfaceContext::Menu2Selected()
{
	CUserContext::Menu2Selected();

	ApplyTransformation = this->LoftedSurface;
	m_manager->ClearInputArea();

	m_manager->SetRadio1("");

}

void CSurfaceContext::Menu3Selected()
{
	CUserContext::Menu3Selected();

	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CSurfaceContext::Menu4Selected()
{
	CUserContext::Menu4Selected();

	m_manager->ChangeContext(CMainContext2::GetInstance());
}

void CSurfaceContext::Menu5Selected()
{
}

void CSurfaceContext::Menu6Selected()
{
}

void CSurfaceContext::Menu7Selected()
{
}

void CSurfaceContext::Menu8Selected()
{
}

void CSurfaceContext::Menu9Selected()
{
}

void CSurfaceContext::ApplyBtnPressed()
{
	(this->*ApplyTransformation)();
}

double CSurfaceContext::UW2XYZ(double u, double w, double* points)
{
//	return (1-u)*(1-w)*points[0]+(1-u)*w*points[1]+(1-w)*u*points[2]+u*w*points[3];
	return ((points[0]*(1-u)*(1-w))+(points[3]*(1-u)*w)+(points[1]*u*(1-w))+(points[2]*u*w));
}

void CSurfaceContext::LoftedSurface()
{

}

void CSurfaceContext::BilinearSurface()
{
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

	CDC* pDC = m_manager->GetRenderAreaDC();

	CPen pen, *pOldPen ;
	pen.CreatePen(PS_SOLID, 1, 0xffff);
	pOldPen = pDC->SelectObject(&pen);
	double u=0,w=0;
	double qx,qy,qz;
	double nsegs1 = 20, nsegs2 = 20;
	double du=1/nsegs1;
	double dw=1/nsegs2;

  int i,k;
  for( k=0,u=0;k<=nsegs1;k++,u+=du)
  {
	   qx = UW2XYZ(u, w, m_guideXs);
	   qy = UW2XYZ(u, w, m_guideYs);
	   qz = UW2XYZ(u, w, m_guideZs);
	   pDC->MoveTo(qx, -qy);
 //  Form1->PaintBox1->Canvas->MoveTo(qx,qy);
	   for( i=0,w=0;i<=nsegs2;i++,w+=dw)
		{
		   qx = UW2XYZ(u, w, m_guideXs);
		   qy = UW2XYZ(u, w, m_guideYs);
		   qz = UW2XYZ(u, w, m_guideZs);
		   pDC->LineTo(qx, -qy);
  // Form1->PaintBox1->Canvas->LineTo(qx,qy);
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
//   Form1->PaintBox1->Canvas->MoveTo(qx,qy);
   pDC->MoveTo(qx, -qy);
   for( i=0,u=0;i<=nsegs2;i++,u+=du)
   {
   qx = UW2XYZ(u, w, m_guideXs);
   qy = UW2XYZ(u, w, m_guideYs);
   qz = UW2XYZ(u, w, m_guideZs);
   pDC->LineTo(qx, -qy);
   //Form1->PaintBox1->Canvas->LineTo(qx,qy);
   }
   u=u-du;
   }

pDC->SelectObject(pOldPen);
pen.DeleteObject();
m_manager->ReleaseRenderAreaDC(pDC);


recentInputPointCount = 0;
}

void CSurfaceContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt = m_manager->GetMouseLoc();
	
	m_guideXs[recentInputPointCount] = pt.x;
	m_guideYs[recentInputPointCount] = pt.y;

	CDC* pDC = m_manager->GetRenderAreaDC();

	DrawPrinciplePoint(pDC, pt);		

	m_manager->ReleaseRenderAreaDC(pDC);

	recentInputPointCount++;
}

void CSurfaceContext::DrawPrinciplePoint(CDC* pDC, CPoint pt)
{
	pDC->MoveTo(pt);
	CBrush br;
	br.CreateSolidBrush(0xff00);
	CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
	pDC->FillRect(r, &br);
	br.DeleteObject();
}
