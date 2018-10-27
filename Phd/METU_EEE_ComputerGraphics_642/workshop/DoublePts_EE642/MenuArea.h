#pragma once
// CMenuArea

class CMenuArea : public CWnd
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
	void SetMenuTitle(CString menuTitle);
private:
	CString m_menuTitle;
};


