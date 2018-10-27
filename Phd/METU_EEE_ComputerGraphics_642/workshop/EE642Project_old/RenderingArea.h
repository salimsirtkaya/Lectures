#if !defined(AFX_RENDERINGAREA_H__C16A15BB_1E32_4E50_8A49_6FA78FF2244E__INCLUDED_)
#define AFX_RENDERINGAREA_H__C16A15BB_1E32_4E50_8A49_6FA78FF2244E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenderingArea.h : header file
//
#include "642Managed.h"
/////////////////////////////////////////////////////////////////////////////
// CRenderingArea window

class CRenderingArea : public CStatic, public C642Managed
{
// Construction
public:
	CRenderingArea();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenderingArea)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRenderingArea();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRenderingArea)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void Grid(CDC &dc, int xSpace, int ySpace, bool gridOn);
	void FillArea(CDC &dc, COLORREF clr);
	CBrush m_bkGndBrush;
	CPen	m_gridPen;
	CPen	m_principalGridPen;
	CPen	m_currentObjectPen;
	CPen	m_previousObjectPen;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERINGAREA_H__C16A15BB_1E32_4E50_8A49_6FA78FF2244E__INCLUDED_)
