#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CMainContext2* CMainContext2::m_context = 0;

CMainContext2::CMainContext2()
{
	m_contextName = "Main Menu";
	m_contextInfo = "Main Menu -- You can select an action from the upper right buttons. You can load a predefined object from the 'LOAD' menu. You can draw an arbitrary 2D Object or many type of plane curves from the 'DRAW' menu. You can apply transformation on objects from the 'EDIT' menu. You can close this program by clicking 'EXIT' button.";
	m_menuCount = 4;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Draw a 2D object to render";
	m_menuItems[0].menuText = "LOAD";
	m_menuItems[1].menuInfo = "Select a transformation on the current graphics object";
	m_menuItems[1].menuText = "DRAW";
	m_menuItems[2].menuInfo = "Draw a 3D object to render";
	m_menuItems[2].menuText = "EDIT";
	m_menuItems[3].menuInfo = "Select a transformation on the current 3D graphics object";
	m_menuItems[3].menuText = "EXIT";
}

CMainContext2::~CMainContext2()
{
}

CUserContext* CMainContext2::GetInstance()
{
	if (CMainContext2::m_context == 0)
	{
		CMainContext2::m_context = new CMainContext2();
	}
	return CMainContext2::m_context;
}

void CMainContext2::Menu1Selected()
{
	CUserContext::Menu1Selected();
	m_manager->ChangeContext(CLoadContext::GetInstance());
}

void CMainContext2::Menu2Selected()
{
	CUserContext::Menu2Selected();
	m_manager->ChangeContext(CDrawContext::GetInstance());
}

void CMainContext2::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CMainContext2::Menu4Selected()
{
	m_manager->Exit();
}

void CMainContext2::Menu5Selected()
{
}

void CMainContext2::Menu6Selected()
{
}

void CMainContext2::Menu7Selected()
{
}

void CMainContext2::Menu8Selected()
{
}

void CMainContext2::Menu9Selected()
{
}

void CMainContext2::ApplyBtnPressed()
{
}
