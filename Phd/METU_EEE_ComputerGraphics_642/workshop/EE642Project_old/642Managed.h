// 642Managed.h: interface for the C642Managed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_642MANAGED_H__1111FF7A_C048_4C8C_9F73_7EAA4E0A0AB4__INCLUDED_)
#define AFX_642MANAGED_H__1111FF7A_C048_4C8C_9F73_7EAA4E0A0AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "642Manager.h"

class C642Managed  
{
protected:
	C642Manager* m_manager;
public:
	C642Managed();
	virtual ~C642Managed();
	void SetManager(C642Manager* manager){ m_manager = manager; };
};

#endif // !defined(AFX_642MANAGED_H__1111FF7A_C048_4C8C_9F73_7EAA4E0A0AB4__INCLUDED_)
