#include "stdafx.h"
#include "642manager.h"
#include "UserContext.h"

C642Manager::C642Manager(void)
{
	m_currentStateGraphObject = 0;
	m_previousStateGraphObject = 0;
	handleMouse = false;
}

C642Manager::~C642Manager(void)
{
	delete m_currentStateGraphObject;
	delete m_previousStateGraphObject;
	delete CMainContext::GetInstance();
	delete C2DObjectContext::GetInstance();
	delete C2DTransformContext::GetInstance();
	delete C3DObjectContext::GetInstance();
	delete C3DTransformContext::GetInstance();
	delete CPlaneCurvesContext::GetInstance();
}

void C642Manager::ChangeContext(CUserContext* newContext)
{
	m_userContext = newContext;
	m_userContext->SetManager(this);
}

void C642Manager::RenderAreaLButton(UINT nFlags, CPoint point)
{
	m_userContext->RenderAreaLButtonDown(nFlags, point);
}

void C642Manager::SetCurrentGraphObject(CCompGraphObject* obj, bool clearPrevious)
{
	delete m_previousStateGraphObject;
	m_previousStateGraphObject = 0;
	if (!clearPrevious)
	{
		if (m_previousStateGraphObject == obj)
		{
			m_previousStateGraphObject = 0;
		}
		else
		{
			m_previousStateGraphObject = m_currentStateGraphObject;
		}
	}
	m_currentStateGraphObject = obj;
}

void C642Manager::DrawCurrentGraphObject(CDC &dc)
{
	if (m_currentStateGraphObject != 0)
	{
		m_currentStateGraphObject->DrawGraphObject(dc);
	}
}

void C642Manager::DrawPreviousGraphObject(CDC &dc)
{
	if (m_previousStateGraphObject != 0)
	{
		m_previousStateGraphObject->DrawGraphObject(dc);
	}
}