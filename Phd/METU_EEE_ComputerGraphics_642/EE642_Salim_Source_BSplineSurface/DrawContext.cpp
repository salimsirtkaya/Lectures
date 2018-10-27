#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"

CDrawContext* CDrawContext::m_context = 0;

CDrawContext::CDrawContext()
{
	m_contextName = "Draw Objects by User Input";
	m_contextInfo = "Draw Objects by User Input -- You can draw arbitrary 2D objects or plane curves in this menu. Select the type from the buttons on the upper left part of the window.";
	m_menuCount = 6;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "You can draw an arbitrary 2D object in this menu. All you have to do is to left click the arbitrary object's feature points on the screen and then pressing enter or apply button. ";
	m_menuItems[0].menuText = "User Defined 2D Objects";
	m_menuItems[1].menuInfo = "Renders user editable plane curves such as circle, 3-point circle, ellipse etc. User can select the type of the plane curve and the input boxes will appear automatically. You should press enter or apply button in order to display the object";
	m_menuItems[1].menuText = "Plane Curves";	
	m_menuItems[2].menuInfo = "Draws Space Curves";
	m_menuItems[2].menuText = "Space Curves";
	m_menuItems[3].menuInfo = "Draws Space Curves";
	m_menuItems[3].menuText = "Surfaces";

	m_menuItems[4].menuInfo = "Goes back to the edit menu";
	m_menuItems[4].menuText = "Edit Menu";
	m_menuItems[5].menuInfo = "Goes back to the main menu";
	m_menuItems[5].menuText = "Main Menu";
	
	m_userObj = 0;
	bGetUserInput = false;
}

CDrawContext::~CDrawContext()
{
	delete m_userObj;
	m_userObj = 0;
}

CUserContext* CDrawContext::GetInstance()
{
	if (CDrawContext::m_context == 0)
	{
		CDrawContext::m_context = new CDrawContext();
	}
	return CDrawContext::m_context;
}

void CDrawContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
	if (bGetUserInput) //User is inputting the points of 2D objects
	{
		CPoint pt = m_manager->GetMouseLoc();

		CDC* pDC = m_manager->GetRenderAreaDC();
		pDC->MoveTo(pt);
		CBrush br;
		br.CreateSolidBrush(0xff);
		CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
		pDC->FillRect(r, &br);
		
		m_manager->ReleaseRenderAreaDC(pDC);

		m_userObj->AddNewPoint(pt.x, pt.y);
	}
}

void CDrawContext::CompleteUserObject()
{
	m_manager->SetCurrentGraphObject(m_userObj, true);
	m_userObj = new CCompGraphObject();
}

void CDrawContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	m_manager->ShowApplyBtn(SW_SHOW);

	if (m_userObj == 0)
	{
		m_userObj = new CCompGraphObject();
	}
	m_userObj->RemoveAllPoints();
	bGetUserInput = true;

}

void CDrawContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(CPlaneCurvesContext::GetInstance());
	bGetUserInput = false;
}

void CDrawContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(CSpaceCurvesContext::GetInstance());
	bGetUserInput = false;
}

void CDrawContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ChangeContext(CSurfaceContext::GetInstance());
}

void CDrawContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
	bGetUserInput = false;
}

void CDrawContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	m_manager->ShowApplyBtn(SW_HIDE);
	m_manager->ChangeContext(CMainContext2::GetInstance());
	bGetUserInput = false;
}

void CDrawContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
}
void CDrawContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
}
void CDrawContext::Menu9Selected()
{
}

void CDrawContext::ApplyBtnPressed()
{
	CompleteUserObject();
}
