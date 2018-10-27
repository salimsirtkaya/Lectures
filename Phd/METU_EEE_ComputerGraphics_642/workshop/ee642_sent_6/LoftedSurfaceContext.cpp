#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CLoftedSurfaceContext* CLoftedSurfaceContext::m_context = 0;

CLoftedSurfaceContext::CLoftedSurfaceContext()
{
	recentInputPointCount = 0;

	m_contextName = "Lofted Surface Menu";
	m_contextInfo = "Lofted Surface Menu -- You can draw lofted surfaces in this menu. Select the type of the edges from the radio buttons. The end condition for the clamped end spline is predefined.";
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

CLoftedSurfaceContext::~CLoftedSurfaceContext()
{
}

CUserContext* CLoftedSurfaceContext::GetInstance()
{
	if (CLoftedSurfaceContext::m_context == 0)
	{
		CLoftedSurfaceContext::m_context = new CLoftedSurfaceContext();
	}
	return CLoftedSurfaceContext::m_context;
}

void CLoftedSurfaceContext::Menu1Selected()
{
	CUserContext::Menu1Selected();

	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");
}

void CLoftedSurfaceContext::Menu2Selected()
{
	CUserContext::Menu2Selected();

	m_manager->ClearInputArea();

	m_manager->SetRadio1("");

}

void CLoftedSurfaceContext::Menu3Selected()
{
	CUserContext::Menu3Selected();

	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CLoftedSurfaceContext::Menu4Selected()
{
	CUserContext::Menu4Selected();

	m_manager->ChangeContext(CMainContext2::GetInstance());
}

void CLoftedSurfaceContext::Menu5Selected()
{
}

void CLoftedSurfaceContext::Menu6Selected()
{
}

void CLoftedSurfaceContext::Menu7Selected()
{
}

void CLoftedSurfaceContext::Menu8Selected()
{
}

void CLoftedSurfaceContext::Menu9Selected()
{
}

void CLoftedSurfaceContext::ApplyBtnPressed()
{
	(this->*ApplyTransformation)();
}

void CLoftedSurfaceContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt = m_manager->GetMouseLoc();
	
	m_guideXs[recentInputPointCount] = pt.x;
	m_guideYs[recentInputPointCount] = pt.y;

	CDC* pDC = m_manager->GetRenderAreaDC();

	DrawPrinciplePoint(pDC, pt);		

	m_manager->ReleaseRenderAreaDC(pDC);

	recentInputPointCount++;
}

void CLoftedSurfaceContext::DrawPrinciplePoint(CDC* pDC, CPoint pt)
{
	pDC->MoveTo(pt);
	CBrush br;
	br.CreateSolidBrush(0xff00);
	CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
	pDC->FillRect(r, &br);
	br.DeleteObject();
}
