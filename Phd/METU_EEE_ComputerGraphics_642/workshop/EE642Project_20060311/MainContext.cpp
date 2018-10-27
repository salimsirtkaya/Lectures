#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CMainContext* CMainContext::m_context = 0;

CMainContext::CMainContext()
{
	m_contextName = "Main Menu";
	m_menuCount = 5;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Draw a 2D object to render";
	m_menuItems[0].menuText = "Draw 2D Object";
	m_menuItems[1].menuInfo = "Select a transformation on the current graphics object";
	m_menuItems[1].menuText = "2D Transformations";
	m_menuItems[2].menuInfo = "Draw a 3D object to render";
	m_menuItems[2].menuText = "Draw 3D Object";
	m_menuItems[3].menuInfo = "Select a transformation on the current 3D graphics object";
	m_menuItems[3].menuText = "3D Transformations";
	m_menuItems[4].menuInfo = "Draw a plane curve to render";
	m_menuItems[4].menuText = "Plane Curves";
}

CMainContext::~CMainContext()
{
}

CUserContext* CMainContext::GetInstance()
{
	if (CMainContext::m_context == 0)
	{
		CMainContext::m_context = new CMainContext();
	}
	return CMainContext::m_context;
}

void CMainContext::SwitchTo2DObjects()
{
	m_manager->ChangeContext(C2DObjectContext::GetInstance());
}
void CMainContext::SwitchTo2DTransformations()
{
	m_manager->ChangeContext(C2DTransformContext::GetInstance());
}
void CMainContext::SwitchTo3DTransformations()
{
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}
void CMainContext::SwitchTo3DObjects()
{
	m_manager->ChangeContext(C3DObjectContext::GetInstance());
}
void CMainContext::SwitchToPlaneCurves()
{
	m_manager->ChangeContext(CPlaneCurvesContext::GetInstance());
}

void CMainContext::Menu1Selected()
{
	SwitchTo2DObjects();
	m_manager->SetInfoAreaText("Draw A 2D object to render");
}

void CMainContext::Menu2Selected()
{
	SwitchTo2DTransformations();
}

void CMainContext::Menu3Selected()
{
	SwitchTo3DObjects();
}

void CMainContext::Menu4Selected()
{
	SwitchTo3DTransformations();
}

void CMainContext::Menu5Selected()
{
	SwitchToPlaneCurves();
}

void CMainContext::Menu6Selected()
{
}

void CMainContext::Menu7Selected()
{
}

void CMainContext::Menu8Selected()
{
}

void CMainContext::Menu9Selected()
{
}

void CMainContext::ApplyBtnPressed()
{
}
