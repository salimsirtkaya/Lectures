#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"

CCubicSplineContext* CCubicSplineContext::m_context = 0;

CCubicSplineContext::CCubicSplineContext()
{
	m_contextName = "Cubic Splines Menu";
	m_contextInfo = "Cubic Splines Menu -- You can draw cubic spline curves in this menu. Select the type of the end condition from the buttons on the upeer right part of the window.";
	m_menuCount = 6;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "You can draw clamped-end Cubic Splines in this menu. Select 6 points on the display area. Then enter the end tangent vectors and press apply button or enter on the keyboard. To select a new point-set press -Create New Point Set- button.";
	m_menuItems[0].menuText = "Clamped End";
	m_menuItems[1].menuInfo = "You can draw relaxed-end Cubic Splines in this menu. Select 6 points on the display area and press -Relaxed End- button. To select a new point-set press -Create New Point Set- button.";
	m_menuItems[1].menuText = "Relaxed End";	
	m_menuItems[2].menuInfo = "You can draw cyclic-end Cubic Splines in this menu. Select 6 points on the display area and press -Cyclic End- button. To select a new point-set press -Create New Point Set- button.";
	m_menuItems[2].menuText = "Cyclic End";	
	m_menuItems[3].menuInfo = "You can draw anticyclic-end Cubic Splines in this menu. Select 6 points on the display area and press -Anti-cyclic End- button. To select a new point-set press -Create New Point Set- button.";
	m_menuItems[3].menuText = "Anti-Cyclic End";	

	m_menuItems[4].menuInfo = "Goes back to the edit menu";
	m_menuItems[4].menuText = "Edit Menu";
	m_menuItems[5].menuInfo = "Goes back to the main menu";
	m_menuItems[5].menuText = "Main Menu";
	
	m_currentCubicObjCount = 1;
//	bContinueToAddPts = true;
	nGuidePtsCnt = 0;
}

CCubicSplineContext::~CCubicSplineContext()
{
}

void CCubicSplineContext::Inversion()
{
	double r2[2][2] = {0.2667, -0.0667, 
		-0.0667, 0.2667};
	double r3[3][3] = {0.2679, -0.0714,    0.0179,
		-0.0714, 0.2857, -0.0714,
		0.0179, -0.0714, 0.2679} ;
	double r4[4][4] = {     0.2679, -0.0718, 0.0191, -0.0048,
   -0.0718, 0.2871,  -0.0766, 0.0191,
    0.0191, -0.0766, 0.2871, -0.0718,
	-0.0048, 0.0191, -0.0718, 0.2679};
	double r5[5][5]= { 0.2679, -0.0718, 0.0192, -0.0051, 0.0013,
   -0.0718, 0.2872   -0.0769,    0.0205,   -0.0051,
    0.0192, -0.0769,    0.2885,   -0.0769,    0.0192,
   -0.0051,    0.0205,   -0.0769,    0.2872,   -0.0718,
   0.0013,   -0.0051,    0.0192,   -0.0718,    0.2679};
	double r6[6][6] = {    0.2679,   -0.0718,    0.0192,   -0.0052,    0.0014,   -0.0003,
   -0.0718,    0.2872,   -0.0769,    0.0206,   -0.0055,    0.0014,
    0.0192,   -0.0769,    0.2886,   -0.0773,    0.0206,   -0.0052,
   -0.0052,    0.0206,   -0.0773,    0.2886,   -0.0769,    0.0192,
    0.0014,   -0.0055,    0.0206,   -0.0769,    0.2872,   -0.0718,
	-0.0003,    0.0014,   -0.0052,    0.0192,   -0.0718,    0.2679};
	double r7[7][7] = {   0.2679,   -0.0718,    0.0192,   -0.0052,    0.0014,   -0.0004,    0.0001,
   -0.0718,    0.2872,   -0.0770,    0.0206,   -0.0055,    0.0015,   -0.0004,
    0.0192,   -0.0770,    0.2886,   -0.0773,    0.0207,   -0.0055,    0.0014,
   -0.0052,    0.0206,   -0.0773,    0.2887,   -0.0773,    0.0206,   -0.0052,
    0.0014,   -0.0055,    0.0207,   -0.0773,    0.2886,   -0.0770,    0.0192,
   -0.0004,    0.0015,   -0.0055,    0.0206,   -0.0770,    0.2872,   -0.0718,
   0.0001,   -0.0004,    0.0014,   -0.0052,    0.0192,   -0.0718,    0.2679};
	double r8[8][8];
	double r9[9][9];



}

CUserContext* CCubicSplineContext::GetInstance()
{
	if (CCubicSplineContext::m_context == 0)
	{
		CCubicSplineContext::m_context = new CCubicSplineContext();
	}
	return CCubicSplineContext::m_context;
}

void CCubicSplineContext::DrawPrinciplePoint(CDC* pDC, CPoint pt)
{
	pDC->MoveTo(pt);
	CBrush br;
	br.CreateSolidBrush(0x80ffff);
	CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
	pDC->FillRect(r, &br);
	br.DeleteObject();
}

void CCubicSplineContext::DrawPrincipleLines(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_DOT, 1, 0x80ffff);
	CPen* oldPen = pDC->SelectObject(&pen);
	m_cubicObjs[0].DrawGraphObject(*pDC, false);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}
void CCubicSplineContext::PaintRenderArea(CDC &dc)
{
	if (m_cubicObjs[0].GetPointCount() != 0)
	{
		CPen pen;
		pen.CreatePen(PS_DOT, 1, 0x80ffff);
		CPen* oldPen = dc.SelectObject(&pen);
		m_cubicObjs[0].DrawGraphObject(dc, false);
		dc.SelectObject(oldPen);
		pen.DeleteObject();
	}
}

void CCubicSplineContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
//	if (bContinueToAddPts)
	if (nGuidePtsCnt < 6)
	{
		CPoint pt = m_manager->GetMouseLoc();

		CDC* pDC = m_manager->GetRenderAreaDC();

		DrawPrinciplePoint(pDC, pt);		

		m_cubicObjs[0].AddNewPoint(pt.x, pt.y);
		m_guideXs[nGuidePtsCnt] = pt.x;
		m_guideYs[nGuidePtsCnt] = pt.y;

		DrawPrincipleLines(pDC);
		m_manager->ReleaseRenderAreaDC(pDC);
		nGuidePtsCnt++;
	}
	else
	{
		//bContinueToAddPts = true;
		//m_cubicObjs[0].RemoveAllPoints();
	}
}

void CCubicSplineContext::EnableClampedEndParams()
{
	m_manager->SetInput1Name("1. DelX");
	m_manager->SetInput2Name("1. DelY");
	m_manager->SetInput4Name("6. DelX");
	m_manager->SetInput5Name("6. DelY");
	m_manager->ShowApplyBtn(SW_SHOW);
}

void CCubicSplineContext::RelaxedEndMultiplication()
{
	derx[0]= (1.1547*3/2*(m_guideXs[1]-m_guideXs[0]))-(0.1547*3*(m_guideXs[2]-m_guideXs[0]))+(0.0415*3*(m_guideXs[3]-m_guideXs[1]))-(0.0112*3*(m_guideXs[4]-m_guideXs[2]))+(0.0032*3*(m_guideXs[5]-m_guideXs[3]))-(0.0008*6*(m_guideXs[5]-m_guideXs[4]));
	dery[0]= (1.1547*3/2*(m_guideYs[1]-m_guideYs[0]))-(0.1547*3*(m_guideYs[2]-m_guideYs[0]))+(0.0415*3*(m_guideYs[3]-m_guideYs[1]))-(0.0112*3*(m_guideYs[4]-m_guideYs[2]))+(0.0032*3*(m_guideYs[5]-m_guideYs[3]))-(0.0008*6*(m_guideYs[5]-m_guideYs[4]));

	derx[1]= (-0.3094*3/2*(m_guideXs[1]-m_guideXs[0]))+(0.3094*3*(m_guideXs[2]-m_guideXs[0]))-(0.0829*3*(m_guideXs[3]-m_guideXs[1]))+(0.0223*3*(m_guideXs[4]-m_guideXs[2]))-(0.0064*3*(m_guideXs[5]-m_guideXs[3]))+(0.0016*6*(m_guideXs[5]-m_guideXs[4]));
	dery[1]= (-0.3094*3/2*(m_guideYs[1]-m_guideYs[0]))+(0.3094*3*(m_guideYs[2]-m_guideYs[0]))-(0.0829*3*(m_guideYs[3]-m_guideYs[1]))+(0.0223*3*(m_guideYs[4]-m_guideYs[2]))-(0.0064*3*(m_guideYs[5]-m_guideYs[3]))+(0.0016*6*(m_guideYs[5]-m_guideYs[4]));
			
	derx[2]= (0.0829*3/2*(m_guideXs[1]-m_guideXs[0]))-(0.0829*3*(m_guideXs[2]-m_guideXs[0]))+(0.2903*3*(m_guideXs[3]-m_guideXs[1]))-(0.0781*3*(m_guideXs[4]-m_guideXs[2]))+(0.0223*3*(m_guideXs[5]-m_guideXs[3]))-(0.0056*6*(m_guideXs[5]-m_guideXs[4]));
	dery[2]= (0.0829*3/2*(m_guideYs[1]-m_guideYs[0]))-(0.0829*3*(m_guideYs[2]-m_guideYs[0]))+(0.2903*3*(m_guideYs[3]-m_guideYs[1]))-(0.0781*3*(m_guideYs[4]-m_guideYs[2]))+(0.0223*3*(m_guideYs[5]-m_guideYs[3]))-(0.0056*6*(m_guideYs[5]-m_guideYs[4]));
	
	derx[3]= (-0.0223*3/2*(m_guideXs[1]-m_guideXs[0]))+(0.0223*3*(m_guideXs[2]-m_guideXs[0]))-(0.0781*3*(m_guideXs[3]-m_guideXs[1]))+(0.2903*3*(m_guideXs[4]-m_guideXs[2]))-(0.0829*3*(m_guideXs[5]-m_guideXs[3]))+(0.0207*6*(m_guideXs[5]-m_guideXs[4]));
	dery[3]= (-0.0223*3/2*(m_guideYs[1]-m_guideYs[0]))+(0.0223*3*(m_guideYs[2]-m_guideYs[0]))-(0.0781*3*(m_guideYs[3]-m_guideYs[1]))+(0.2903*3*(m_guideYs[4]-m_guideYs[2]))-(0.0829*3*(m_guideYs[5]-m_guideYs[3]))+(0.0207*6*(m_guideYs[5]-m_guideYs[4]));

	derx[4]= (0.0064*3/2*(m_guideXs[1]-m_guideXs[0]))-(0.0064*3*(m_guideXs[2]-m_guideXs[0]))+(0.0223*3*(m_guideXs[3]-m_guideXs[1]))-(0.0829*3*(m_guideXs[4]-m_guideXs[2]))+(0.3094*3*(m_guideXs[5]-m_guideXs[3]))-(0.0774*6*(m_guideXs[5]-m_guideXs[4]));
	dery[4]= (0.0064*3/2*(m_guideYs[1]-m_guideYs[0]))-(0.0064*3*(m_guideYs[2]-m_guideYs[0]))+(0.0223*3*(m_guideYs[3]-m_guideYs[1]))-(0.0829*3*(m_guideYs[4]-m_guideYs[2]))+(0.3094*3*(m_guideYs[5]-m_guideYs[3]))-(0.0774*6*(m_guideYs[5]-m_guideYs[4]));

	derx[5]= (-0.0032*3/2*(m_guideXs[1]-m_guideXs[0]))+(0.0032*3*(m_guideXs[2]-m_guideXs[0]))-(0.0112*3*(m_guideXs[3]-m_guideXs[1]))+(0.0415*3*(m_guideXs[4]-m_guideXs[2]))-(0.1547*3*(m_guideXs[5]-m_guideXs[3]))+(0.2887*6*(m_guideXs[5]-m_guideXs[4]));
	dery[5]= (-0.0032*3/2*(m_guideYs[1]-m_guideYs[0]))+(0.0032*3*(m_guideYs[2]-m_guideYs[0]))-(0.0112*3*(m_guideYs[3]-m_guideYs[1]))+(0.0415*3*(m_guideYs[4]-m_guideYs[2]))-(0.1547*3*(m_guideYs[5]-m_guideYs[3]))+(0.2887*6*(m_guideYs[5]-m_guideYs[4]));		
}

void CCubicSplineContext::ClampedEndMultiplication()
{
	derx[0] = m_manager->GetInput1();
	dery[0] = m_manager->GetInput1();

	derx[5] = m_manager->GetInput4();
	dery[5] = m_manager->GetInput5();
		
	derx[1]= (-0.2679*derx[0])+(0.2679*3*(m_guideXs[2]-m_guideXs[0]))-(0.0718*3*(m_guideXs[3]-m_guideXs[1]))+(0.0191*3*(m_guideXs[4]-m_guideXs[2]))-(0.0048*3*(m_guideXs[5]-m_guideXs[3]))+(0.0048*derx[5]);
	dery[1]= (-0.2679*dery[0])+(0.2679*3*(m_guideYs[2]-m_guideYs[0]))-(0.0718*3*(m_guideYs[3]-m_guideYs[1]))+(0.0191*3*(m_guideYs[4]-m_guideYs[2]))-(0.0048*3*(m_guideYs[5]-m_guideYs[3]))+(0.0048*dery[5]);

	derx[2]= (0.0718*derx[0])-(0.0718*3*(m_guideXs[2]-m_guideXs[0]))+(0.2871*3*(m_guideXs[3]-m_guideXs[1]))-(0.0766*3*(m_guideXs[4]-m_guideXs[2]))+(0.0191*3*(m_guideXs[5]-m_guideXs[3]))-(0.0191*derx[5]);
	dery[2]= (0.0718*dery[0])-(0.0718*3*(m_guideYs[2]-m_guideYs[0]))+(0.2871*3*(m_guideYs[3]-m_guideYs[1]))-(0.0766*3*(m_guideYs[4]-m_guideYs[2]))+(0.0191*3*(m_guideYs[5]-m_guideYs[3]))-(0.0191*dery[5]);
	
	derx[3]= (-0.0191*derx[0])+(0.0191*3*(m_guideXs[2]-m_guideXs[0]))-(0.0766*3*(m_guideXs[3]-m_guideXs[1]))+(0.2871*3*(m_guideXs[4]-m_guideXs[2]))-(0.0718*3*(m_guideXs[5]-m_guideXs[3]))+(0.0718*derx[5]);
	dery[3]= (-0.0191*dery[0])+(0.0191*3*(m_guideYs[2]-m_guideYs[0]))-(0.0766*3*(m_guideYs[3]-m_guideYs[1]))+(0.2871*3*(m_guideYs[4]-m_guideYs[2]))-(0.0718*3*(m_guideYs[5]-m_guideYs[3]))+(0.0718*dery[5]);
	
	derx[4]= (0.0048*derx[0])-(0.2679*3*(m_guideXs[2]-m_guideXs[0]))+(0.0191*3*(m_guideXs[3]-m_guideXs[1]))-(0.0718*3*(m_guideXs[4]-m_guideXs[2]))+(0.2679*3*(m_guideXs[5]-m_guideXs[3]))-(0.2679*derx[5]);
	dery[4]= (0.0048*dery[0])-(0.2679*3*(m_guideYs[2]-m_guideYs[0]))+(0.0191*3*(m_guideYs[3]-m_guideYs[1]))-(0.0718*3*(m_guideYs[4]-m_guideYs[2]))+(0.2679*3*(m_guideYs[5]-m_guideYs[3]))-(0.2679*dery[5]);
}

void CCubicSplineContext::AntiCyclicEndMultiplication()
{
	derx[0]= (0.2895*3*(m_guideXs[1]-m_guideXs[0]+m_guideXs[4]-m_guideXs[5]))-(0.0789*3*(m_guideXs[2]-m_guideXs[0]))+(0.0263*3*(m_guideXs[3]-m_guideXs[1]))-(0.0263*3*(m_guideXs[4]-m_guideXs[2]))+(0.0789*3*(m_guideXs[5]-m_guideXs[3]));
	dery[0]= (0.2895*3*(m_guideYs[1]-m_guideYs[0]+m_guideYs[4]-m_guideYs[5]))-(0.0789*3*(m_guideYs[2]-m_guideYs[0]))+(0.0263*3*(m_guideYs[3]-m_guideYs[1]))-(0.0263*3*(m_guideYs[4]-m_guideYs[2]))+(0.0789*3*(m_guideYs[5]-m_guideYs[3]));
	
	derx[1]= (-0.0789*3*(m_guideXs[1]-m_guideXs[0]+m_guideXs[4]-m_guideXs[5]))+(0.2895*3*(m_guideXs[2]-m_guideXs[0]))-(0.0789*3*(m_guideXs[3]-m_guideXs[1]))+(0.0263*3*(m_guideXs[4]-m_guideXs[2]))-(0.0263*3*(m_guideXs[5]-m_guideXs[3]));
	dery[1]= (-0.0789*3*(m_guideYs[1]-m_guideYs[0]+m_guideYs[4]-m_guideYs[5]))+(0.2895*3*(m_guideYs[2]-m_guideYs[0]))-(0.0789*3*(m_guideYs[3]-m_guideYs[1]))+(0.0263*3*(m_guideYs[4]-m_guideYs[2]))-(0.0263*3*(m_guideYs[5]-m_guideYs[3]));
			
	derx[2]= (0.0263*3*(m_guideXs[1]-m_guideXs[0]+m_guideXs[4]-m_guideXs[5]))-(0.0789*3*(m_guideXs[2]-m_guideXs[0]))+(0.2895*3*(m_guideXs[3]-m_guideXs[1]))-(0.0789*3*(m_guideXs[4]-m_guideXs[2]))+(0.0263*3*(m_guideXs[5]-m_guideXs[3]));
	dery[2]= (0.0263*3*(m_guideYs[1]-m_guideYs[0]+m_guideYs[4]-m_guideYs[5]))-(0.0789*3*(m_guideYs[2]-m_guideYs[0]))+(0.2895*3*(m_guideYs[3]-m_guideYs[1]))-(0.0789*3*(m_guideYs[4]-m_guideYs[2]))+(0.0263*3*(m_guideYs[5]-m_guideYs[3]));
	
	derx[3]= (-0.0263*3*(m_guideXs[1]-m_guideXs[0]+m_guideXs[4]-m_guideXs[5]))+(0.0263*3*(m_guideXs[2]-m_guideXs[0]))-(0.0789*3*(m_guideXs[3]-m_guideXs[1]))+(0.2895*3*(m_guideXs[4]-m_guideXs[2]))-(0.0789*3*(m_guideXs[5]-m_guideXs[3]));
	dery[3]= (-0.0263*3*(m_guideYs[1]-m_guideYs[0]+m_guideYs[4]-m_guideYs[5]))+(0.0263*3*(m_guideYs[2]-m_guideYs[0]))-(0.0789*3*(m_guideYs[3]-m_guideYs[1]))+(0.2895*3*(m_guideYs[4]-m_guideYs[2]))-(0.0789*3*(m_guideYs[5]-m_guideYs[3]));

	derx[4]= (0.0789*3*(m_guideXs[1]-m_guideXs[0]+m_guideXs[4]-m_guideXs[5]))-(0.0263*3*(m_guideXs[2]-m_guideXs[0]))+(0.0263*3*(m_guideXs[3]-m_guideXs[1]))-(0.0789*3*(m_guideXs[4]-m_guideXs[2]))+(0.2895*3*(m_guideXs[5]-m_guideXs[3]));
	dery[4]= (0.0789*3*(m_guideYs[1]-m_guideYs[0]+m_guideYs[4]-m_guideYs[5]))-(0.0263*3*(m_guideYs[2]-m_guideYs[0]))+(0.0263*3*(m_guideYs[3]-m_guideYs[1]))-(0.0789*3*(m_guideYs[4]-m_guideYs[2]))+(0.2895*3*(m_guideYs[5]-m_guideYs[3]));
			
	derx[5]= -derx[0];
	dery[5]= -dery[0];
}

void CCubicSplineContext::CyclicEndMultiplication()
{
	derx[0]= (0.2879*3*(m_guideXs[1]-m_guideXs[0]-m_guideXs[4]+m_guideXs[5]))-(0.0758*3*(m_guideXs[2]-m_guideXs[0]))+(0.0152*3*(m_guideXs[3]-m_guideXs[1]))+(0.0152*3*(m_guideXs[4]-m_guideXs[2]))-(0.0758*3*(m_guideXs[5]-m_guideXs[3]));
	dery[0]= (0.2879*3*(m_guideYs[1]-m_guideYs[0]-m_guideYs[4]+m_guideYs[5]))-(0.0758*3*(m_guideYs[2]-m_guideYs[0]))+(0.0152*3*(m_guideYs[3]-m_guideYs[1]))+(0.0152*3*(m_guideYs[4]-m_guideYs[2]))-(0.0758*3*(m_guideYs[5]-m_guideYs[3]));
	
	derx[1]= (-0.0758*3*(m_guideXs[1]-m_guideXs[0]-m_guideXs[4]+m_guideXs[5]))+(0.2879*3*(m_guideXs[2]-m_guideXs[0]))-(0.0758*3*(m_guideXs[3]-m_guideXs[1]))+(0.0152*3*(m_guideXs[4]-m_guideXs[2]))+(0.0152*3*(m_guideXs[5]-m_guideXs[3]));
	dery[1]= (-0.0758*3*(m_guideYs[1]-m_guideYs[0]-m_guideYs[4]+m_guideYs[5]))+(0.2879*3*(m_guideYs[2]-m_guideYs[0]))-(0.0758*3*(m_guideYs[3]-m_guideYs[1]))+(0.0152*3*(m_guideYs[4]-m_guideYs[2]))+(0.0152*3*(m_guideYs[5]-m_guideYs[3]));
			
	derx[2]= (0.0152*3*(m_guideXs[1]-m_guideXs[0]-m_guideXs[4]+m_guideXs[5]))-(0.0758*3*(m_guideXs[2]-m_guideXs[0]))+(0.2879*3*(m_guideXs[3]-m_guideXs[1]))-(0.0758*3*(m_guideXs[4]-m_guideXs[2]))+(0.0152*3*(m_guideXs[5]-m_guideXs[3]));
	dery[2]= (0.0152*3*(m_guideYs[1]-m_guideYs[0]-m_guideYs[4]+m_guideYs[5]))-(0.0758*3*(m_guideYs[2]-m_guideYs[0]))+(0.2879*3*(m_guideYs[3]-m_guideYs[1]))-(0.0758*3*(m_guideYs[4]-m_guideYs[2]))+(0.0152*3*(m_guideYs[5]-m_guideYs[3]));
	
	derx[3]= (0.0152*3*(m_guideXs[1]-m_guideXs[0]-m_guideXs[4]+m_guideXs[5]))+(0.0152*3*(m_guideXs[2]-m_guideXs[0]))-(0.0758*3*(m_guideXs[3]-m_guideXs[1]))+(0.2879*3*(m_guideXs[4]-m_guideXs[2]))-(0.0758*3*(m_guideXs[5]-m_guideXs[3]));
	dery[3]= (0.0152*3*(m_guideYs[1]-m_guideYs[0]-m_guideYs[4]+m_guideYs[5]))+(0.0152*3*(m_guideYs[2]-m_guideYs[0]))-(0.0758*3*(m_guideYs[3]-m_guideYs[1]))+(0.2879*3*(m_guideYs[4]-m_guideYs[2]))-(0.0758*3*(m_guideYs[5]-m_guideYs[3]));

	derx[4]= (-0.0758*3*(m_guideXs[1]-m_guideXs[0]-m_guideXs[4]+m_guideXs[5]))+(0.0152*3*(m_guideXs[2]-m_guideXs[0]))+(0.0152*3*(m_guideXs[3]-m_guideXs[1]))-(0.0758*3*(m_guideXs[4]-m_guideXs[2]))+(0.2879*3*(m_guideXs[5]-m_guideXs[3]));
	dery[4]= (-0.0758*3*(m_guideYs[1]-m_guideYs[0]-m_guideYs[4]+m_guideYs[5]))+(0.0152*3*(m_guideYs[2]-m_guideYs[0]))+(0.0152*3*(m_guideYs[3]-m_guideYs[1]))-(0.0758*3*(m_guideYs[4]-m_guideYs[2]))+(0.2879*3*(m_guideYs[5]-m_guideYs[3]));
			
	derx[5]= derx[0];
	dery[5]= dery[0];
}

void CCubicSplineContext::CalcCubicSpline(COLORREF clr)
{
	double B1x[5],B1y[5],B2x[5],B2y[5],B3x[5],B3y[5],B4x[5],B4y[5];
	int i, j;
	for (i=0;i<5;i++)
	{
		B1x[i]=(m_guideXs[i]);
		B1y[i]=(m_guideYs[i]);
		B2x[i]=derx[i];
		B2y[i]=dery[i];
		B3x[i]=3*(m_guideXs[i+1]-m_guideXs[i])-2*derx[i]-derx[i+1];
		B3y[i]=3*(m_guideYs[i+1]-m_guideYs[i])-2*dery[i]-dery[i+1];
		B4x[i]=2*(m_guideXs[i]-m_guideXs[i+1])+derx[i]+derx[i+1];
		B4y[i]=2*(m_guideYs[i]-m_guideYs[i+1])+dery[i]+dery[i+1];
	}

	CCompGraphObject* newObj = new CCompGraphObject(false);
//		CDC* pDC = m_manager->GetRenderAreaDC();

	for (i=0;i<5;i++)
	{
		for (j=0;j<2000;j+=20)
		{
			newObj->AddNewPoint(B1x[i]+B2x[i]*j/2000+B3x[i]*j*j/2000/2000+B4x[i]*j*j*j/2000/2000/2000,
				(B1y[i]+B2y[i]*j/2000+B3y[i]*j*j/2000/2000+B4y[i]*j*j*j/2000/2000/2000));
		} // for j
	}

//		m_manager->ReleaseRenderAreaDC(pDC);
	m_manager->SetCurrentGraphObject(newObj, true);
}

void CCubicSplineContext::DrawClampedEnd()
{
	ClampedEndMultiplication();
	CalcCubicSpline(0xff);
}

void CCubicSplineContext::Menu1Selected()
{
	CUserContext::Menu1Selected();

	EnableClampedEndParams();
	CCubicSplineContext::ApplyTransformation =	CCubicSplineContext::DrawClampedEnd;
}

void CCubicSplineContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	m_manager->ClearInputArea();
	CCubicSplineContext::ApplyTransformation =	CCubicSplineContext::VoidFunct;
	RelaxedEndMultiplication();
	CalcCubicSpline(0xffff);
}

void CCubicSplineContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearInputArea();
	CCubicSplineContext::ApplyTransformation =	CCubicSplineContext::VoidFunct;
	CyclicEndMultiplication();
	CalcCubicSpline(0xff00ff);
}

void CCubicSplineContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearInputArea();
	CCubicSplineContext::ApplyTransformation =	CCubicSplineContext::VoidFunct;
	AntiCyclicEndMultiplication();
	CalcCubicSpline(0xffff00);
}

void CCubicSplineContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
//	Menu9Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CCubicSplineContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
//	Menu9Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(CMainContext2::GetInstance());
}

void CCubicSplineContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
}
void CCubicSplineContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
}
void CCubicSplineContext::Menu9Selected()
{
	nGuidePtsCnt = 0;
	m_cubicObjs[0].RemoveAllPoints();
	m_manager->SetCurrentGraphObject(0, true);
}

void CCubicSplineContext::ApplyBtnPressed()
{
//	bContinueToAddPts = false;
	(this->*ApplyTransformation)();
}
