#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CMainContext* CMainContext::m_context = 0;

CMainContext::CMainContext()
{
	m_contextName = "Main Menu";
	m_menuCount = 2;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Select a 2D object to render";
	m_menuItems[0].menuText = "Select 2d Object";
	m_menuItems[1].menuInfo = "Select a transformation on the current graphics object";
	m_menuItems[1].menuText = "2D Transformations";
}

CMainContext::~CMainContext()
{
	CUserContext::~CUserContext();
	delete CMainContext::m_context;
	delete[] m_menuItems;
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
void CMainContext::Menu1Selected()
{
	SwitchTo2DObjects();
	m_manager->SetInfoAreaText("Select A 2D object to render");
}

void CMainContext::Menu2Selected()
{
	SwitchTo2DTransformations();
}

void CMainContext::Menu3Selected()
{
}

void CMainContext::Menu4Selected()
{
}

void CMainContext::Menu5Selected()
{
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
