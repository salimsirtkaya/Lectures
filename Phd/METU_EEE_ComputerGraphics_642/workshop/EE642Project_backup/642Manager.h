#pragma once

#include "CompGraphObject.h"

class CUserContext;
class C642Manager
{
protected:
	CUserContext* m_userContext;
	CCompGraphObject* m_currentStateGraphObject;
	CCompGraphObject* m_previousStateGraphObject;
	bool handleMouse;
	CPoint m_mouseLoc;

public:
	C642Manager(void);
	virtual ~C642Manager(void);
	virtual void ChangeContext(CUserContext* newContext);
	virtual void SetCurrentGraphObject(CCompGraphObject* obj, bool clearPrev = false);
	CCompGraphObject* GetCurrentGraphObject() {return m_currentStateGraphObject;}
	void DrawCurrentGraphObject(CDC &dc);
	void DrawPreviousGraphObject(CDC &dc);
	virtual void ClearInputArea()=0;
	virtual void SetInput1Name(CString name)=0;
	virtual void SetInput2Name(CString name)=0;
	virtual double GetInput1()=0;
	virtual double GetInput2()=0;
	virtual void SetRadio1(CString str)=0;
	virtual void SetRadio2(CString str)=0;
	virtual void SetRadio3(CString str)=0;
	virtual void ClearRadio()=0;
	virtual void LineParametersShow(int cmd)=0;
	virtual int GetRadioSel()=0;
	virtual double GetLineParamA()=0;
	virtual double GetLineParamB()=0;
	virtual void SetMenuTitle(CString str)=0;
	void SetHandleMouse(bool x)
	{
		handleMouse = x;
	}
	bool GetHandleMouse()
	{
		return handleMouse;
	}
	void SetMouseLoc(CPoint x)
	{
		m_mouseLoc = x;
	}
	CPoint GetMouseLoc()
	{
		return m_mouseLoc;
	}
	virtual void SetInfoAreaText(CString str)=0;
	virtual void DrawLine(CPoint p1, CPoint p2)=0;
};