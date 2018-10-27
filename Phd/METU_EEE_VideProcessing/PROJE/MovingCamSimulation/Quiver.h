#pragma once
#include "imge.h"
class CFigureWindow;
class CQuiver
{
	friend CFigureWindow;
private:
	//Following points represent a single arrow to be drawn
	CPoint	m_startPt;
	CPoint	m_endPt;
	CPoint	m_upperArrEndPt;
	CPoint	m_lowerArrEndPt;
    int		m_xResolution;
	int		m_yResolution;
	double	m_xMagnify;
	double	m_yMagnify;
	CRect	m_zoomIntoRect;

	void	DrawSingle(CDC* pDC, int i, int j, double u, double v);
	void	RotatePoint(CPoint &p, double cosUV, double sinUV);
	void	LengthenArrow(double mag);
	void	TranslateArrow(CPoint trans);
	void	ResetArrowCoords();
	void	RotateArrow(double u, double v);
public:
	CQuiver(void);
	~CQuiver(void);
	BOOL DisplayQuiver(CWnd* wnd, const CImge & U, const CImge & V);
	void SetZoom(CRect zoomR);
	void ResetZoom();
	CRect GetZoom()
	{
		return m_zoomIntoRect;
	}
};
