// MenuArea.cpp : implementation file
//

#include "stdafx.h"
#include "EE642Project.h"
#include "MenuArea.h"


// CMenuArea

IMPLEMENT_DYNAMIC(CMenuArea, CWnd)
CMenuArea::CMenuArea()
{
}

CMenuArea::~CMenuArea()
{
}

BEGIN_MESSAGE_MAP(CMenuArea, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMenuArea message handlers


void CMenuArea::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,10, "Main Menu");
	
}
