#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"

CLoadContext* CLoadContext::m_context = 0;

CLoadContext::CLoadContext()
{
	m_contextName = "Load Predefined Objects";
	m_contextInfo = "Load predefined objects -- You can load predefined objects such as line, square, triangle, cube etc. from this menu. Select the object you want to load from buttons on the upper right part of the window.";
	m_menuCount = 8;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Renders a predefined line";
	m_menuItems[0].menuText = "2D Line";
	m_menuItems[1].menuInfo = "Renders a predefined triangle";
	m_menuItems[1].menuText = "2D Triangle";
	m_menuItems[2].menuInfo = "Renders a predefined square";
	m_menuItems[2].menuText = "2D Square";
	m_menuItems[3].menuInfo = "Renders a predefined polygon";
	m_menuItems[3].menuText = "2D Polygon";
	m_menuItems[4].menuInfo = "Renders a predefined cube with triangular facet - Note that this object is a 3D object. Go to EDIT menu and rotate this object to see the 3D characteristic.";
	m_menuItems[4].menuText = "Cube w. Triang. Facet(3D)";	
	m_menuItems[5].menuInfo = "Renders a predefined prism - Note that this object is a 3D object. Go to EDIT menu and rotate this object to see the 3D characteristic.";
	m_menuItems[5].menuText = "Prism (3D)";	
	
	m_menuItems[6].menuInfo = "Goes to Edit Menu";
	m_menuItems[6].menuText = "Edit Menu";
	m_menuItems[7].menuInfo = "Goes back to the main menu";
	m_menuItems[7].menuText = "Main Menu";
}

CLoadContext::~CLoadContext()
{
}

CUserContext* CLoadContext::GetInstance()
{
	if (CLoadContext::m_context == 0)
	{
		CLoadContext::m_context = new CLoadContext();
	}
	return CLoadContext::m_context;
}

void CLoadContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
}

void CLoadContext::DefaultLine()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint(0);
	obj->AddNewPoint(70, 70);
	m_manager->SetCurrentGraphObject(obj, true);
}

void CLoadContext::DefaultTriangle()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint(0);
	obj->AddNewPoint(50, 100);
	obj->AddNewPoint(100, 50);
	m_manager->SetCurrentGraphObject(obj, true);
}

void CLoadContext::DefualtSquare()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint(0);
	obj->AddNewPoint(0, 70);
	obj->AddNewPoint(70, 70);
	obj->AddNewPoint(70,0);
	m_manager->SetCurrentGraphObject(obj, true);
}

void CLoadContext::DefaultPolygon()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint(0);
	obj->AddNewPoint(0, 40);
	obj->AddNewPoint(30, 70);
	obj->AddNewPoint(100,0);
	m_manager->SetCurrentGraphObject(obj, true);
}

void CLoadContext::DefaultTriangularFacet(void)
{
	CCompGraphObject* obj = new CTriCube();
	((CTriCube*)obj)->DefaultTriCube();
	m_manager->SetCurrentGraphObject(obj, true);
}
void CLoadContext::DefaultPrism(void)
{
	CCompGraphObject* obj = new CPrism();
	((CPrism*)obj)->DefaultPrism();
	m_manager->SetCurrentGraphObject(obj, true);
}

void CLoadContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	DefaultLine();
}

void CLoadContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	DefaultTriangle();
}

void CLoadContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	DefualtSquare();
}

void CLoadContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	DefaultPolygon();
}

void CLoadContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	DefaultTriangularFacet();
}

void CLoadContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	DefaultPrism();
}

void CLoadContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}
void CLoadContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
	m_manager->ChangeContext(CMainContext2::GetInstance());
}
void CLoadContext::Menu9Selected()
{
}

void CLoadContext::ApplyBtnPressed()
{
}
