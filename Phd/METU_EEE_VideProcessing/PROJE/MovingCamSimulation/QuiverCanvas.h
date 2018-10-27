#pragma once


// CQuiverCanvas

class CQuiverCanvas : public CStatic
{
	DECLARE_DYNAMIC(CQuiverCanvas)

public:
	CQuiverCanvas();
	virtual ~CQuiverCanvas();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
private:
	CBrush	m_bgBrush;
	CPoint	m_zoomStartPt;
	CPoint	m_zoomEndPt;
};
