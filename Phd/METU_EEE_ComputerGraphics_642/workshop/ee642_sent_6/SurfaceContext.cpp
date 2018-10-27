#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CSurfaceContext* CSurfaceContext::m_context = 0;

CSurfaceContext::CSurfaceContext()
{
	recentInputPointCount = 0;

	m_contextName = "Surface Menu";
	m_contextInfo = "Surface Menu -- You can draw 3D surfaces in this menu. Select the type of the surface from the buttons";
	m_menuCount = 4;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Draw a bilinear surface";
	m_menuItems[0].menuText = "Bilinear Surface";
	m_menuItems[1].menuInfo = "Draw lofted surface. Select the type of the edges from the radio buttons. The end conditions for the clamped spline is fixed to 100 , -100, -100 for x,y and z axes respectively for both ends and both splines.";
	m_menuItems[1].menuText = "Lofted Surface";
	m_menuItems[2].menuInfo = "Select a transformation on the current 3D graphics object";
	m_menuItems[2].menuText = "Edit";
	m_menuItems[3].menuInfo = "Go to main menu";
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
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");

	m_manager->SetRadio1("Clamped End");
	m_manager->SetRadio2("Relaxed End");
	m_manager->SetRadio3("Cyclic");
	m_manager->SetRadio4("Anti-Cyclic");

}

void CSurfaceContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();

	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CSurfaceContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();

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

void CSurfaceContext::LoftedSurface()
{
	CCompGraphObject *newObj = new CLoftedSurface();

	((CLoftedSurface*)newObj)->SetLoftMode(m_manager->GetRadioSel());
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;

}

void CSurfaceContext::BilinearSurface()
{
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

	CCompGraphObject* newObj = new CBilinearSurface();

	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
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
