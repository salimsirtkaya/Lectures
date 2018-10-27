#pragma once
#include "642Managed.h"
// CMenuArea

class CMenuArea : public CWnd, public C642Managed
{
	DECLARE_DYNAMIC(CMenuArea)
private:
public:
	CMenuArea();
	virtual ~CMenuArea();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


