#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"
#include "math.h"

#define PI 3.1415926535

CPlaneCurvesContext* CPlaneCurvesContext::m_context = 0;

CPlaneCurvesContext::CPlaneCurvesContext()
{
	currentMenu = 0;
	iMouseLoc = 0;
	m_contextName = "Plane Curves Menu";
	m_contextInfo = "Plane Curves Menu -- You can draw plane curves in this menu. Selectthe type of the plane curve from the buttons on the upeer right part of the window.";
	m_menuCount = 6;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Renders a circle";
	m_menuItems[0].menuText = "Circle";
	m_menuItems[1].menuInfo = "Renders a 3 point circle";
	m_menuItems[1].menuText = "3 Point Circle";
	m_menuItems[2].menuInfo = "Renders an ellipse.";
	m_menuItems[2].menuText = "Ellipse";
	m_menuItems[3].menuInfo = "Renders a parabola. The parabola expression is y^2 = 4ax. Consider input 'a' accordingly.";
	m_menuItems[3].menuText = "Parabola";
	m_menuItems[4].menuInfo = "Renders a hyperbola. The hyperbola expression is x^2/a^2 - y^2/b^2 = 1. Consider inputs 'a' and 'b' accordingly.";
	m_menuItems[4].menuText = "Hyperbola";
	m_menuItems[5].menuInfo = "Goes back to main menu";
	m_menuItems[5].menuText = "Main Menu";
}

CPlaneCurvesContext::~CPlaneCurvesContext()
{
}

CUserContext* CPlaneCurvesContext::GetInstance()
{
	if (CPlaneCurvesContext::m_context == 0)
	{
		CPlaneCurvesContext::m_context = new CPlaneCurvesContext();
	}
	return CPlaneCurvesContext::m_context;
}

void CPlaneCurvesContext::DrawCircle()
{
	m_manager->SetCurrentGraphObject(0, true);
	CDC* pDC = m_manager->GetRenderAreaDC();

	int x, y, r;
	x = (int)m_manager->GetInput1();
	y = (int)m_manager->GetInput2();
	r = (int)m_manager->GetInput3();

	int i;
	double teta_inc,xcircle,ycircle;

	teta_inc=2*PI/3600;
	r=abs(r);
	for(i=0;i<3600;i++)
	{
		xcircle = r*cos(teta_inc*i);
		ycircle = r*sin(teta_inc*i);
//		if (((x+xcircle<630) && (x+xcircle>130)) && ((y-ycircle<440) && (y-ycircle>40)))
		pDC->SetPixelV(xcircle+x,-y+ycircle, 0xff);
	}
	m_manager->ReleaseRenderAreaDC(pDC);
}

void CPlaneCurvesContext::EnableCircleParams()
{
	m_manager->SetInput1Name("X Center:");
	m_manager->SetInput2Name("Y Center:");
	m_manager->SetInput3Name("Radius:");
}
void CPlaneCurvesContext::EnableEllipseParams()
{
	m_manager->SetInput1Name("X Center:");
	m_manager->SetInput4Name("Y Center:");
	m_manager->SetInput2Name("X Radius:");
	m_manager->SetInput5Name("Y Radius:");
	m_manager->SetInput3Name("Orientation:");
}

void CPlaneCurvesContext::EnableParabolaParams()
{
	m_manager->SetInput1Name("a:");
}

void CPlaneCurvesContext::EnableHyperbolaParams()
{
	m_manager->SetInput1Name("a:");
	m_manager->SetInput2Name("b:");
}

void CPlaneCurvesContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	currentMenu = 0;
	ResetIMouseLoc();
	m_manager->ClearInputArea();	
	EnableCircleParams();
	CPlaneCurvesContext::ApplyTransformation =	CPlaneCurvesContext::DrawCircle;
}

void CPlaneCurvesContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	currentMenu = 1;
	ResetIMouseLoc();
	m_manager->ClearInputArea();
}

void CPlaneCurvesContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	currentMenu = 2;
	ResetIMouseLoc();
	m_manager->ClearInputArea();
	EnableEllipseParams();
	CPlaneCurvesContext::ApplyTransformation =	CPlaneCurvesContext::DrawEllipse;
}

void CPlaneCurvesContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	currentMenu = 3;
	ResetIMouseLoc();
	m_manager->ClearInputArea();	
	EnableParabolaParams();
	CPlaneCurvesContext::ApplyTransformation =	CPlaneCurvesContext::DrawParabola;
}

void CPlaneCurvesContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	currentMenu = 4;
	ResetIMouseLoc();
	m_manager->ClearInputArea();	
	EnableHyperbolaParams();
	CPlaneCurvesContext::ApplyTransformation =	CPlaneCurvesContext::DrawHyperbola;
}

void CPlaneCurvesContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	currentMenu = 0;
	ResetIMouseLoc();
	CUserContext::Menu6Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->ChangeContext(CMainContext2::GetInstance());
	m_manager->SetHandleMouse(false);
	if (m_manager->GetCurrentGraphObject() == 0)
	{
		m_manager->SetCurrentGraphObject(0);
	}
}

void CPlaneCurvesContext::Menu7Selected()
{
}

void CPlaneCurvesContext::Menu8Selected()
{
}

void CPlaneCurvesContext::Menu9Selected()
{
}

void CPlaneCurvesContext::ApplyBtnPressed()
{
	(this->*ApplyTransformation)();
}

void CPlaneCurvesContext::DrawEllipse()
{
	m_manager->SetCurrentGraphObject(0, true);
	CDC* pDC = m_manager->GetRenderAreaDC();

	int x, y, rx, ry, orientation;
	x = (int)m_manager->GetInput1();
	y = (int)m_manager->GetInput4();
	rx = (int)m_manager->GetInput2();
	ry = (int)m_manager->GetInput5();
	orientation = (int)m_manager->GetInput3();

	int i;
	double teta_inc,xellipse,yellipse,xellipse_r,yellipse_r;

	teta_inc=2*PI/3600;
	rx=abs(rx);
	ry=abs(ry);
	for(i=0;i<3600;i++)
	{
		xellipse = rx*cos(teta_inc*i);
		yellipse = ry*sin(teta_inc*i);
		xellipse_r = (xellipse*cos(PI/180*orientation))-(yellipse*sin(PI/180*orientation));
		yellipse_r = (xellipse*sin(PI/180*orientation))+(yellipse*cos(PI/180*orientation));
		pDC->SetPixelV(xellipse_r+x, -y+yellipse_r, 0xff);
	}

	m_manager->ReleaseRenderAreaDC(pDC);
}

void CPlaneCurvesContext::DrawParabola()
{
	m_manager->SetCurrentGraphObject(0, true);
	CDC* pDC = m_manager->GetRenderAreaDC();
	int a;
	a = (int)m_manager->GetInput1();
	if (a==0)
	{
		return;
	}

	double teta_inc=0.0005;
	double xparab=0,yparab=0;

	do
	{
		pDC->SetPixelV(xparab,yparab,0xff);
		pDC->SetPixelV(xparab,-yparab,0xff);
		xparab = xparab + yparab*teta_inc + a*(teta_inc*teta_inc);
		yparab = yparab + 2*a*teta_inc;
	}  while(((xparab<300) && (xparab>-300)) && ((yparab<300) && (yparab>-300)));

	m_manager->ReleaseRenderAreaDC(pDC);
}

void CPlaneCurvesContext::DrawHyperbola()
{
	m_manager->SetCurrentGraphObject(0, true);
	CDC* pDC = m_manager->GetRenderAreaDC();

	int a, b;
	a = (int)m_manager->GetInput1();
	b = (int)m_manager->GetInput2();

	const double cosh_teta_inc=cosh(0.003);
	const double sinh_teta_inc=sinh(0.003);
	double xhypb=a,yhypb=0;
	double xhypb_1,yhypb_1;

	do
	{
		pDC->SetPixelV(xhypb,-yhypb,0xff);
		pDC->SetPixelV(xhypb,yhypb,0xff);
		pDC->SetPixelV(-xhypb,-yhypb,0xff);
		pDC->SetPixelV(-xhypb,yhypb,0xff);
		xhypb_1 = (xhypb*cosh_teta_inc) + (double(a)/double(b)*yhypb*sinh_teta_inc);
		yhypb_1 = (double(b)/double(a)*xhypb*sinh_teta_inc) + (yhypb*cosh_teta_inc);
		xhypb = xhypb_1;
		yhypb = yhypb_1;
	}  while(((xhypb<300) && (xhypb>-300)) && ((yhypb<300) && (yhypb>-300)));

	m_manager->ReleaseRenderAreaDC(pDC);
}

void CPlaneCurvesContext::Draw3PtCircle()
{
	int i=0;
	float px[3],py[3];
	float h,k,r,hp,kp;

	px[0] = (float) mouseLocs[0][0];	
	px[1] = mouseLocs[1][0] - mouseLocs[0][0];
	px[2] = mouseLocs[2][0] - mouseLocs[0][0];

	py[0] = mouseLocs[0][1];	
	py[1] = mouseLocs[1][1] - mouseLocs[0][1];
	py[2] = mouseLocs[2][1] - mouseLocs[0][1];

	hp=(((px[2]*px[2]+py[2]*py[2])*py[1])-((px[1]*px[1]+py[1]*py[1])*py[2]))/(2*px[2]*py[1]-2*px[1]*py[2]);
	kp=((px[1]*px[1]+py[1]*py[1])-2*px[1]*hp)/(2*py[1]);
	h=hp+px[0];
	k=kp+py[0];
	r=sqrt(hp*hp+kp*kp);

	m_manager->SetCurrentGraphObject(0, true);
	CDC* pDC = m_manager->GetRenderAreaDC();

	double teta_inc,xcircle,ycircle;

	teta_inc=2*PI/3600;
	r=abs(r);
	for(i=0;i<3600;i++)
	{
		xcircle = r*cos(teta_inc*i);
		ycircle = r*sin(teta_inc*i);
//		if (((x+xcircle<630) && (x+xcircle>130)) && ((y-ycircle<440) && (y-ycircle>40)))
		pDC->SetPixelV(xcircle+h,-k+ycircle, 0xff);

	}

	m_manager->ReleaseRenderAreaDC(pDC);

}

void CPlaneCurvesContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
	if (currentMenu == 1) //3pt circle
	{
		CPoint pt = m_manager->GetMouseLoc();
		mouseLocs[iMouseLoc][0] = pt.x;
		mouseLocs[iMouseLoc][1] = pt.y;

		CDC* pDC = m_manager->GetRenderAreaDC();
		pDC->MoveTo(pt);
		CBrush br;
		br.CreateSolidBrush(0xff);
		CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
		pDC->FillRect(r, &br);
		
		m_manager->ReleaseRenderAreaDC(pDC);
		iMouseLoc ++;
		if(iMouseLoc == 3)
		{
			Draw3PtCircle();
			iMouseLoc = 0;
		}
	}
}