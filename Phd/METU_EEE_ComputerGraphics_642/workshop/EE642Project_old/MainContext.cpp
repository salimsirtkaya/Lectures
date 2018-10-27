#include "stdafx.h"
#include "usercontext.h"

CMainContext* CMainContext::m_context = 0;

CMainContext::CMainContext()
{
	m_contextName = "Main Menu";
}

CMainContext::~CMainContext()
{
	CUserContext::~CUserContext();
	delete CMainContext::m_context;
}

void CMainContext::SetMenuArea()
{
}

void CMainContext::SetInputArea()
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
