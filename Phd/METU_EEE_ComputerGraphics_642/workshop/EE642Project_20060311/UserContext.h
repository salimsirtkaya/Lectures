#pragma once

class C642Manager;

struct SMenuItem
{
public:
	CString menuText;
	CString menuInfo;
};

class CUserContext
{
protected:
	C642Manager* m_manager;
	CString m_contextName;
	int m_menuCount;
	SMenuItem* m_menuItems;
	CUserContext(void);
public:
	virtual ~CUserContext(void);
	CString GetContextName() { return m_contextName;};
	int GetMenuCount() {return m_menuCount;};
	CString GetMenuItemText(int index) { return m_menuItems[index].menuText;};
	CString GetMenuItemInfo(int index) {return m_menuItems[index].menuInfo;};
	virtual void PaintRenderArea(CDC &dc) = 0;
	virtual void RenderAreaLButtonDown(UINT nFlags, CPoint point)=0;
	virtual void Menu1Selected();
	virtual void Menu2Selected();
	virtual void Menu3Selected();
	virtual void Menu4Selected();
	virtual void Menu5Selected();
	virtual void Menu6Selected();
	virtual void Menu7Selected();
	virtual void Menu8Selected();
	virtual void Menu9Selected();
	virtual void ApplyBtnPressed()=0;
	virtual CString GetInput1Name(){ return "";}
	virtual CString GetInput2Name(){ return "";}
	C642Manager*  GetManager()
	{
		return m_manager;
	}
	void SetManager(C642Manager* manager)
	{
		m_manager = manager;
	}
};

class CMainContext
	:public CUserContext
{
private:
	static CMainContext* m_context;
	CMainContext();
	void SwitchTo2DObjects();
	void SwitchTo2DTransformations();
	void SwitchToPlaneCurves();
	void SwitchTo3DObjects();
	void SwitchTo3DTransformations();
public:
	~CMainContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point){};
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
};

class C2DObjectContext
	:public CUserContext
{
private:
	static C2DObjectContext* m_context;
	C2DObjectContext();
	void DefaultLine();
	void DefaultTriangle();
	void DefualtSquare();
	void DefaultPolygon();
public:
	~C2DObjectContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point);
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
};

class C2DTransformContext
	:public CUserContext
{
private:
	static C2DTransformContext* m_context;
	C2DTransformContext();
	void TranslationParametersEnable(void);
	void TranslateObject();	
	void Reflect();
public:
	~C2DTransformContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point){};
	void (C2DTransformContext::*ApplyTransformation)();
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
private:
	void RotateObjAroundPoint();
	void RotateAboutAPointParamsEnable();
	void RotateAboutArbitraryPoint();
	void ShearObject();
	void ShearParamsEnable();
	void Scale();
	void ScaleParamsEnable();
	void ReflectionParametersEnable();
	void RotationParametersEnable(void);
	void RotateObject(void);
};

class C3DObjectContext
	:public CUserContext
{
private:
	static C3DObjectContext* m_context;
	C3DObjectContext();
public:
	~C3DObjectContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point){};
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
private:
	void DefaultTriangularFacet(void);
	void DefaultPrism();
};

class CPlaneCurvesContext
	:public CUserContext
{
private:
	int currentMenu; //0:Circle, 1:3-pt Circle, 2: Ellipse, 3:Parabola, 4:Hyerbola
	int iMouseLoc;
	void ResetIMouseLoc(){iMouseLoc = 0;}
	int mouseLocs[3][2];
	static CPlaneCurvesContext* m_context;
	CPlaneCurvesContext();
	void DrawCircle();
	void DrawParabola();
	void DrawHyperbola();
	void EnableCircleParams();
	void EnableEllipseParams();
	void EnableParabolaParams();
	void EnableHyperbolaParams();
	void Draw3PtCircle();
	void DrawEllipse();
public:
	~CPlaneCurvesContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point);
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
	void (CPlaneCurvesContext::*ApplyTransformation)();
};


class C3DTransformContext
	:public CUserContext
{
private:
	static C3DTransformContext* m_context;
	C3DTransformContext();
public:
	~C3DTransformContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc){};
	void RenderAreaLButtonDown(UINT nFlags, CPoint point){};
	void Menu1Selected();
	void Menu2Selected();
	void Menu3Selected();
	void Menu4Selected();
	void Menu5Selected();
	void Menu6Selected();
	void Menu7Selected();
	void Menu8Selected();
	void Menu9Selected();
	void ApplyBtnPressed();
	void (C3DTransformContext::*ApplyTransformation)();
private:
	void ProjectPerspective();
	void EnablePerspectiveProjectionParams();
	void Reflect3D();
	void EnableReflection3DParams();
	void RotateAboutAnyLine();
	void EnableRotationAboutALineParams();
	void EnableTranslationParams(void);
	void TranslateObject(void);
	void ScaleParamsEnable(void);
	void Scale(void);
	void ShearParamsEnable(void);
	void ShearObject(void);
	void EnableRotate3DxParams(void);
	void Rotate3D(void);
};
