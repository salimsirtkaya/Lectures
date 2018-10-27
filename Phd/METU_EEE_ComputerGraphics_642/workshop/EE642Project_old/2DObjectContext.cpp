#include "stdafx.h"
#include "usercontext.h"

C2DObjectContext* C2DObjectContext::m_context = 0;

C2DObjectContext::C2DObjectContext()
{
	m_contextName = "2D Object Selection";
}

void C2DObjectContext::SetMenuArea()
{
}

void C2DObjectContext::SetInputArea()
{
}

C2DObjectContext::~C2DObjectContext()
{
	CUserContext::~CUserContext();
	delete C2DObjectContext::m_context;
}

CUserContext* C2DObjectContext::GetInstance()
{
	if (C2DObjectContext::m_context == 0)
	{
		C2DObjectContext::m_context = new C2DObjectContext();
	}
	return C2DObjectContext::m_context;
}