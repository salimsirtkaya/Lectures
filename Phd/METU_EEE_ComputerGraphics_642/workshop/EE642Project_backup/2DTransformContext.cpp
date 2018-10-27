#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"
#include "math.h"

#define PI 3.1415926535
C2DTransformContext* C2DTransformContext::m_context = 0;

C2DTransformContext::C2DTransformContext()
{
	m_contextName = "2D Object Transformation";
	m_menuCount = 7;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Scales by input parameters -- Select the type of scaling [down or upscale] and the scale parameter";
	m_menuItems[0].menuText = "Scaling";
	m_menuItems[1].menuInfo = "Sheares by input parameters -- Select the axis of shear and input the shearing factor";
	m_menuItems[1].menuText = "Shearing";
	m_menuItems[2].menuInfo = "Rotates by input parameters about the origin -- Input the angle of rotation in degrees";
	m_menuItems[2].menuText = "Rotation about Origin";
	m_menuItems[3].menuInfo = "Translates by input parameters -- Input the X and Y axes translations in pixels";
	m_menuItems[3].menuText = "Translate";
	m_menuItems[4].menuInfo = "Rotates about an arbitrary point -- Select the point with left clicking your mouse on the display area and input the rotation angle in degrees";
	m_menuItems[4].menuText = "Rotation About Any Point";
	m_menuItems[5].menuInfo = "Reflects the object -- Select the type of reflection [X-axis, Y-axis or wrt an arbitrary line]. Input the line equation for the arbitrary line";
	m_menuItems[5].menuText = "Reflection";
	m_menuItems[6].menuInfo = "Goes back to the main menu";
	m_menuItems[6].menuText = "Main Menu";
}

C2DTransformContext::~C2DTransformContext()
{
	CUserContext::~CUserContext();
	delete C2DTransformContext::m_context;
	delete[] m_menuItems;
}

CUserContext* C2DTransformContext::GetInstance()
{
	if (C2DTransformContext::m_context == 0)
	{
		C2DTransformContext::m_context = new C2DTransformContext();
	}
	return C2DTransformContext::m_context;
}

void C2DTransformContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	m_manager->ClearInputArea();
	m_manager->SetHandleMouse(false);
	ScaleParamsEnable();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::Scale;
}

void C2DTransformContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	m_manager->ClearInputArea();
	m_manager->SetHandleMouse(false);
	ShearParamsEnable();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::ShearObject;
}

void C2DTransformContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearInputArea();
	m_manager->SetHandleMouse(false);
	m_manager->ClearRadio();
	RotationParametersEnable();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::RotateObject;
}

void C2DTransformContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->SetHandleMouse(false);
	TranslationParametersEnable();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::TranslateObject;
}

void C2DTransformContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	RotationParametersEnable();
	RotateAboutArbitraryPoint();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::RotateObjAroundPoint;
}

void C2DTransformContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	m_manager->ClearInputArea();
	m_manager->SetHandleMouse(false);
	ReflectionParametersEnable();
	C2DTransformContext::ApplyTransformation = C2DTransformContext::Reflect;
}

void C2DTransformContext::ScaleParamsEnable()
{
	m_manager->ClearInputArea();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->SetRadio1("Upscale");
	m_manager->SetRadio2("Downscale");
	m_manager->SetInput1Name("Scale Factor");
}

void C2DTransformContext::ShearParamsEnable()
{
	m_manager->ClearInputArea();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->SetRadio1("Shear in X axis");
	m_manager->SetRadio2("Shear in Y axis");
	m_manager->SetInput1Name("Shearing Factor");
}


void C2DTransformContext::RotateAboutAPointParamsEnable()
{
	m_manager->SetInput1Name("Rotation Angle (degree):");
	m_manager->LineParametersShow(SW_HIDE);
}

void C2DTransformContext::ReflectionParametersEnable()
{
	m_manager->LineParametersShow(SW_SHOW);
	m_manager->SetRadio1("Reflect about X axis");
	m_manager->SetRadio2("Reflect about Y axis");
	m_manager->SetRadio3("Reflect about a line");
}

void C2DTransformContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->ChangeContext(CMainContext::GetInstance());
	m_manager->SetHandleMouse(false);
}
void C2DTransformContext::Menu8Selected()
{
}
void C2DTransformContext::Menu9Selected()
{
}
void C2DTransformContext::TranslationParametersEnable(void)
{
	m_manager->SetInput1Name("Horizontal Translation (pxls):");
	m_manager->SetInput2Name("Vertical Translation (pxls):");
	m_manager->LineParametersShow(SW_HIDE);
}


void C2DTransformContext::ShearObject()
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = new CCompGraphObject();
		switch (sel)
		{
		case 0:
			obj->ShearX(*newObj, m_manager->GetInput1());
			break;
		case 1:
			obj->ShearY(*newObj, m_manager->GetInput1());
			break;
		case 2:
			break;
		}
		m_manager->SetCurrentGraphObject(newObj);
	}
}

void C2DTransformContext::Scale()
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = new CCompGraphObject();
		switch (sel)
		{
		case 0:
			obj->Scale(*newObj, m_manager->GetInput1());
			break;
		case 1:
			obj->Scale(*newObj, 1/(m_manager->GetInput1()));
			break;
		case 2:
			break;
		}
		m_manager->SetCurrentGraphObject(newObj);
	}
}

void C2DTransformContext::RotateAboutArbitraryPoint()
{
	m_manager->SetHandleMouse(true);
}

void C2DTransformContext::Reflect()
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		bool bLine = false;
		CPoint p1, p2;
		CCompGraphObject* newObj = new CCompGraphObject();
		switch (sel)
		{
		case 0:
			obj->ReflectX(*newObj);
			break;
		case 1:
			obj->ReflectY(*newObj);
			break;
		case 2:
			bLine = true;
			obj->ReflectArbitrary(*newObj,(int) m_manager->GetLineParamA(), (int) m_manager->GetLineParamB());
			p1.x = 100;
			p1.y = m_manager->GetLineParamA()*p1.x + m_manager->GetLineParamB();
			p2.x = -100;
			p2.y = m_manager->GetLineParamA()*p2.x + m_manager->GetLineParamB();
			break;
		}
		m_manager->SetCurrentGraphObject(newObj);
		if (bLine)
		{
			m_manager->DrawLine(p1, p2);
		}
	}

}

void C2DTransformContext::ApplyBtnPressed(void)
{
	(this->*ApplyTransformation)();
}

void C2DTransformContext::TranslateObject()
{
	int delX = (int)ceil(m_manager->GetInput1());
	int delY = (int)ceil(m_manager->GetInput2());

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = new CCompGraphObject();
		obj->Translate2D(*newObj, delX, delY);
		m_manager->SetCurrentGraphObject(newObj);
	}

}

void C2DTransformContext::RotationParametersEnable(void)
{
	m_manager->SetInput1Name("Rotation Angle (degree):");
	m_manager->LineParametersShow(SW_HIDE);
}

void C2DTransformContext::RotateObject(void)
{
	double angle = m_manager->GetInput1();
	angle = angle*PI / 180.0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = new CCompGraphObject();
		obj->RotateAroundOrigin(*newObj, angle);
		m_manager->SetCurrentGraphObject(newObj);
	}
}


void C2DTransformContext::RotateObjAroundPoint()
{
	double angle = m_manager->GetInput1();
	angle = angle*PI / 180.0;

	CGraphPoint p(m_manager->GetMouseLoc().x, m_manager->GetMouseLoc().y);

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = new CCompGraphObject();
		obj->RotateAround2D(*newObj,p, angle);
		m_manager->SetCurrentGraphObject(newObj);
	}

}
