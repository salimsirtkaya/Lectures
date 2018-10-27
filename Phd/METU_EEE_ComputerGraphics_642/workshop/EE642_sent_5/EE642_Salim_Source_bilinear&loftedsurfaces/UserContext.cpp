#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"

CUserContext::CUserContext(void)
{
}

CUserContext::~CUserContext(void)
{
	delete[] m_menuItems;
	m_menuItems = 0;
}


void CUserContext::Menu1Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[0].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[0].menuText);
	}
	catch(...)
	{
	}
}

void CUserContext::Menu2Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[1].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[1].menuText);
	}
	catch(...)
	{
	}
}

void CUserContext::Menu3Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[2].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[2].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu4Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[3].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[3].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu5Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[4].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[4].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu6Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[5].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[5].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu7Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[6].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[6].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu8Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[7].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[7].menuText);
	}
	catch(...)
	{
	}
}
void CUserContext::Menu9Selected()
{
	try
	{
		m_manager->SetInfoAreaText(m_menuItems[8].menuInfo);
		m_manager->SetMenuTitle(m_menuItems[8].menuText);
	}
	catch(...)
	{
	}
}
