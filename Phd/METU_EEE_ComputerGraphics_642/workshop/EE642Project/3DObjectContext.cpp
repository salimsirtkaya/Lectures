
#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"
#include "CompGraphObject.h"

C3DObjectContext* C3DObjectContext::m_context = 0;

C3DObjectContext::C3DObjectContext()
{
	m_contextName = "3D Object Selection";
	m_menuCount = 4;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Renders a predefined line";
	m_menuItems[0].menuText = "Cube w. Triangular Facet";
	m_menuItems[1].menuInfo = "Renders a predefined triangle";
	m_menuItems[1].menuText = "Prism";
	m_menuItems[2].menuInfo = "Goes to 3D Transformations Menu";
	m_menuItems[2].menuText = "3D Transformations Menu";
	m_menuItems[3].menuInfo = "Goes back to the main menu";
	m_menuItems[3].menuText = "Main Menu";
}

C3DObjectContext::~C3DObjectContext()
{
	CUserContext::~CUserContext();
	delete C3DObjectContext::m_context;
	delete[] m_menuItems;
}

CUserContext* C3DObjectContext::GetInstance()
{
	if (C3DObjectContext::m_context == 0)
	{
		C3DObjectContext::m_context = new C3DObjectContext();
	}
	return C3DObjectContext::m_context;
}

void C3DObjectContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	DefaultTriangularFacet();
}

void C3DObjectContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	DefaultPrism();
}

void C3DObjectContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void C3DObjectContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ChangeContext(CMainContext::GetInstance());
}

void C3DObjectContext::Menu5Selected()
{
}

void C3DObjectContext::Menu6Selected()
{
}

void C3DObjectContext::Menu7Selected()
{
}
void C3DObjectContext::Menu8Selected()
{
}
void C3DObjectContext::Menu9Selected()
{
}

void C3DObjectContext::ApplyBtnPressed()
{
}

void C3DObjectContext::DefaultTriangularFacet(void)
{
	CCompGraphObject* obj = new CTriCube();
	((CTriCube*)obj)->DefaultTriCube();
	m_manager->SetCurrentGraphObject(obj, true);
}
void C3DObjectContext::DefaultPrism(void)
{
	CCompGraphObject* obj = new CPrism();
	((CPrism*)obj)->DefaultPrism();
	m_manager->SetCurrentGraphObject(obj, true);
}
