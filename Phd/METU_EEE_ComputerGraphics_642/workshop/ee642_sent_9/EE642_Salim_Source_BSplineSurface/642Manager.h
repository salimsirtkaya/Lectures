#pragma once

#include "CompGraphObject.h"

class CUserContext;
class C642Manager
{
protected:
	CUserContext* m_userContext;
	CUserContext* m_previousContext;
	CCompGraphObject* m_currentStateGraphObject;
	CCompGraphObject* m_previousStateGraphObject;
	bool handleMouse;
	CPoint m_mouseLoc;

public:
	C642Manager(void);
	void GoBackContext();
	virtual ~C642Manager(void);
	virtual CDC* GetRenderAreaDC()=0;
	virtual void ReleaseRenderAreaDC(CDC* pDC)=0;
	virtual void ShowApplyBtn(int nCmd)=0;
	virtual void ShowMenu9(CString menuName, bool show = true)=0;
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
	virtual void SetInput3Name(CString name)=0;
	virtual double GetInput3()=0;
	virtual void SetInput4Name(CString name)=0;
	virtual double GetInput4()=0;
	virtual void SetInput5Name(CString name)=0;
	virtual double GetInput5()=0;
	virtual void SetInput6Name(CString name)=0;
	virtual double GetInput6()=0;
	virtual void SetRadio1(CString str)=0;
	virtual void SetRadio2(CString str)=0;
	virtual void SetRadio3(CString str)=0;
	virtual void SetRadio4(CString str)=0;
	virtual void SetRadio5(CString str)=0;
	virtual void ClearRadio()=0;
	virtual void LineParametersShow(int cmd)=0;
	virtual int GetRadioSel()=0;
	virtual void SetRadioSel(int sel)=0;
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
	void RenderAreaLButton(UINT nFlags, CPoint point);
	virtual void WriteMouseLocInfo(int x, int y)=0;
	virtual void Exit()=0;
	void PaintRenderArea(CDC &dc);
};
