// QuiverCanvas.cpp : implementation file
//

#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "QuiverCanvas.h"
#include ".\quivercanvas.h"


// CQuiverCanvas

IMPLEMENT_DYNAMIC(CQuiverCanvas, CStatic)
CQuiverCanvas::CQuiverCanvas()
{
	m_bgBrush.CreateSolidBrush(0xffffff);
}

CQuiverCanvas::~CQuiverCanvas()
{
}


BEGIN_MESSAGE_MAP(CQuiverCanvas, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CQuiverCanvas message handlers


HBRUSH CQuiverCanvas::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	return m_bgBrush;	
}
