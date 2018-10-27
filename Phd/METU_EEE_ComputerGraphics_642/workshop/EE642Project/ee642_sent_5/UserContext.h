#pragma once
#include "compgraphobject.h"
class C642Manager;

#define MAX_CUBIC_OBJ_COUNT 5

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
	CString	m_contextInfo;
	int m_menuCount;
	SMenuItem* m_menuItems;
	CUserContext(void);
public:
	virtual ~CUserContext(void);
	CString GetContextName() { return m_contextName;};
	CString GetContextInfo() { return m_contextInfo;};
	int GetMenuCount() {return m_menuCount;};
	CString GetMenuItemText(int index) { return m_menuItems[index].menuText;};
	CString GetMenuItemInfo(int index) {return m_menuItems[index].menuInfo;};
	virtual void OnRadio4() {};
	virtual void OnRadio1() {};
	virtual void OnRadio2() {};
	virtual void OnRadio3() {};
	virtual void OnRadio5() {};
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

class CMainContext2
	:public CUserContext
{
private:
	static CMainContext2* m_context;
	CMainContext2();
public:
	~CMainContext2();
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
	int radio4Enum;
public:
	~C3DTransformContext();
	static CUserContext* GetInstance();
	void OnRadio1();
	void OnRadio2();
	void OnRadio3();
	void OnRadio5();
	void OnRadio4();
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
	void RotateObjAroundPoint();
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

class CLoadContext
	:public CUserContext
{
private:
	static CLoadContext* m_context;
	CLoadContext();
	void DefaultLine();
	void DefaultTriangle();
	void DefualtSquare();
	void DefaultPolygon();
	void DefaultTriangularFacet(void);
	void DefaultPrism();
public:
	~CLoadContext();
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

class CDrawContext
	:public CUserContext
{
private:
	void CompleteUserObject();
	static CDrawContext* m_context;
	CDrawContext();
	CCompGraphObject* m_userObj;
	bool bGetUserInput;
public:
	~CDrawContext();
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

class CSpaceCurvesContext
	:public CUserContext
{
private:
	static CSpaceCurvesContext* m_context;
	CSpaceCurvesContext();
	CCompGraphObject* m_userObj;
	void ParabolicBlending();
	void BezierCurve();
	void BSpline();
	int howManyInputs; //0:neutral, 4:parabolicBlend, 6:Bezier, 20:B-Spline
	void DrawPrinciplePoint(CDC* pDC, CPoint pt);
	void DrawPrincipleLines(CDC* pDC);
	CCompGraphObject mPrincipleLine;
	double m_guideXs[20];
	double m_guideYs[20];

public:
	~CSpaceCurvesContext();
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
	void (CSpaceCurvesContext::*ApplyTransformation)();
};


class CCubicSplineContext
	:public CUserContext
{
private:
	static CCubicSplineContext* m_context;
	CCubicSplineContext();
	int m_currentCubicObjCount;
	CCompGraphObject m_cubicObjs[MAX_CUBIC_OBJ_COUNT+1];//first obj is principle-lines
	int nGuidePtsCnt;
//	bool bContinueToAddPts;
	void Inversion();
	void CalcCubicSpline(COLORREF clr);
	void ClampedEndMultiplication();
	void RelaxedEndMultiplication();
	void CyclicEndMultiplication();
	void AntiCyclicEndMultiplication();
	void EnableClampedEndParams();
	double m_guideXs[6];
	double m_guideYs[6];
	double derx[6],dery[6];
public:
	~CCubicSplineContext();
	static CUserContext* GetInstance();
	void PaintRenderArea(CDC &dc);
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
private:
	void DrawPrincipleLines(CDC* pDC);
	void DrawPrinciplePoint(CDC* pDC, CPoint pt);
	void (CCubicSplineContext::*ApplyTransformation)();
	void DrawClampedEnd();
	void VoidFunct(){};
};

class CSurfaceContext
	:public CUserContext
{
private:
	double UW2XYZ(double u, double w, double* points);
	static CSurfaceContext* m_context;
	CSurfaceContext();
	double m_guideXs[20];
	double m_guideYs[20];
	double m_guideZs[20];
	int recentInputPointCount;
	void DrawPrinciplePoint(CDC* pDC, CPoint pt);
	void (CSurfaceContext::*ApplyTransformation)();
	void BilinearSurface();
	void LoftedSurface();
public:
	~CSurfaceContext();
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


class CLoftedSurfaceContext
	:public CUserContext
{
private:
	static CLoftedSurfaceContext* m_context;
	CLoftedSurfaceContext();
	double m_guideXs[20];
	double m_guideYs[20];
	double m_guideZs[20];
	int recentInputPointCount;
	void DrawPrinciplePoint(CDC* pDC, CPoint pt);
	void (CLoftedSurfaceContext::*ApplyTransformation)();
public:
	~CLoftedSurfaceContext();
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
