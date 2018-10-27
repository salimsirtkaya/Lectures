#pragma once

#include "CompGraphObject.h"
#include "UserContext.h"

class C642Manager
{
protected:
	CUserContext* m_userContext;
	CCompGraphObject* m_currentStateGraphObject;
	CCompGraphObject* m_previousStateGraphObject;

public:
	C642Manager(void);
	virtual ~C642Manager(void);
	virtual void AddMenu()=0;
};
