#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"

C2DObjectContext* C2DObjectContext::m_context = 0;

C2DObjectContext::C2DObjectContext()
{
	m_contextName = "2D Object Drawing";
	m_menuCount = 6;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Renders a predefined line";
	m_menuItems[0].menuText = "Draw Line";
	m_menuItems[1].menuInfo = "Renders a predefined triangle";
	m_menuItems[1].menuText = "Draw Triangle";
	m_menuItems[2].menuInfo = "Renders a predefined square";
	m_menuItems[2].menuText = "Draw Square";
	m_menuItems[3].menuInfo = "Renders a predefined polygon";
	m_menuItems[3].menuText = "Draw Polygon";
	m_menuItems[4].menuInfo = "Goes to 2D Transformations Menu";
	m_menuItems[4].menuText = "2D Transformations Menu";
	m_menuItems[5].menuInfo = "Goes back to the main menu";
	m_menuItems[5].menuText = "Main Menu";
}

C2DObjectContext::~C2DObjectContext()
{
}

CUserContext* C2DObjectContext::GetInstance()
{
	if (C2DObjectContext::m_context == 0)
	{
		C2DObjectContext::m_context = new C2DObjectContext();
	}
	return C2DObjectContext::m_context;
}

void C2DObjectContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
}

void C2DObjectContext::DefaultLine()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint();
	obj->AddNewPoint(70, 70);
	m_manager->SetCurrentGraphObject(obj, true);
}

void C2DObjectContext::DefaultTriangle()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint();
	obj->AddNewPoint(50, 100);
	obj->AddNewPoint(100, 50);
	m_manager->SetCurrentGraphObject(obj, true);
}

void C2DObjectContext::DefualtSquare()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint();
	obj->AddNewPoint(0, 70);
	obj->AddNewPoint(70, 70);
	obj->AddNewPoint(70,0);
	m_manager->SetCurrentGraphObject(obj, true);
}

void C2DObjectContext::DefaultPolygon()
{
	CCompGraphObject* obj = new CCompGraphObject();
	obj->AddNewPoint();
	obj->AddNewPoint(0, 40);
	obj->AddNewPoint(30, 70);
	obj->AddNewPoint(100,0);
	m_manager->SetCurrentGraphObject(obj, true);
}

void C2DObjectContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	DefaultLine();
}

void C2DObjectContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	DefaultTriangle();
}

void C2DObjectContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	DefualtSquare();
}

void C2DObjectContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	DefaultPolygon();
}

void C2DObjectContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	m_manager->ChangeContext(C2DTransformContext::GetInstance());
}

void C2DObjectContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	m_manager->ChangeContext(CMainContext::GetInstance());
}

void C2DObjectContext::Menu7Selected()
{
}
void C2DObjectContext::Menu8Selected()
{
}
void C2DObjectContext::Menu9Selected()
{
}

void C2DObjectContext::ApplyBtnPressed()
{
}
