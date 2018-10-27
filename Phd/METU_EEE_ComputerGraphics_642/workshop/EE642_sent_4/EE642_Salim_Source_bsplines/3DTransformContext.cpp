#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"
#include "math.h"

#define PI 3.1415926535
C3DTransformContext* C3DTransformContext::m_context = 0;

C3DTransformContext::C3DTransformContext()
{
	radio4Enum = 0;
	m_contextName = "Object Transformation";
	m_contextInfo = "Object Transformation -- In this menu, you can translate, rotate, shear, reflect etc. the current object. Select the type of transformation you want, from the buttons on the upper left part of the window.";
	m_menuCount = 7;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Translates the object by input parameters -- Unit of translation is pixels. Press enter on your keyboard or apply button on the screen to see the effect of translation.";
	m_menuItems[0].menuText = "Translation";
	m_menuItems[1].menuInfo = "Scales the object by input parameters -- Select the type of scaling [down or upscale] and the scale parameter.  Press enter on your keyboard or apply button on the screen to see the effect of scaling. ";
	m_menuItems[1].menuText = "Scaling";
	m_menuItems[2].menuInfo = "Reflects the object by user intervention -- Select the type of reflection from the radio buttons and input the parameters if necessary.  Press enter on your keyboard or apply button on the screen to see the effect of reflection.";
	m_menuItems[2].menuText = "Reflection";
	m_menuItems[3].menuInfo = "Rotates the object by user intervention -- Select the type of rotation from the radio buttons and input  the parameters if necessary. Press enter on your keyboard or apply button on the screen to see the effect of rotation. (Note that the angle of rotation is given in degrees)";
	m_menuItems[3].menuText = "Rotation";
//	m_menuItems[4].menuInfo = "Rotates about an arbitrary point -- Select the point with left clicking your mouse on the display area and input the rotation angle in degrees";
//	m_menuItems[4].menuText = "Rotation wrt Arbitrary Line";
	m_menuItems[4].menuInfo = "Shears the object by input parameters -- Select the type of shearing [X-axis, Y-axis]. Do not input large shear factors in order to see the effect within the display (values between 0-2 are OK). Press enter on your keyboard or apply button on the screen to see the effect of shearing.";
	m_menuItems[4].menuText = "Shearing";
	m_menuItems[5].menuInfo = "You can see the object from a selected perspective point. The perspective object is projected onto z=0 plane";
	m_menuItems[5].menuText = "Perspective Projection";
	m_menuItems[6].menuInfo = "Goes back to the main menu";
	m_menuItems[6].menuText = "Main Menu";
}

C3DTransformContext::~C3DTransformContext()
{
}

CUserContext* C3DTransformContext::GetInstance()
{
	if (C3DTransformContext::m_context == 0)
	{
		C3DTransformContext::m_context = new C3DTransformContext();
	}
	return C3DTransformContext::m_context;
}

void C3DTransformContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	EnableTranslationParams();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::TranslateObject;
}

void C3DTransformContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	radio4Enum = 0;
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	ScaleParamsEnable();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Scale;
}

void C3DTransformContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	EnableReflection3DParams();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Reflect3D;
	radio4Enum = 1;
	m_manager->SetRadioSel(0);
}

void C3DTransformContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	EnableRotate3DxParams();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Rotate3D;
	radio4Enum = 2;
	m_manager->SetRadioSel(0);
}

void C3DTransformContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	radio4Enum = 0;
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	ShearParamsEnable();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::ShearObject;
}

void C3DTransformContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	EnablePerspectiveProjectionParams();
	m_manager->SetHandleMouse(false);
	C3DTransformContext::ApplyTransformation = C3DTransformContext::ProjectPerspective;
}

void C3DTransformContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->SetHandleMouse(false);
	m_manager->ChangeContext(CMainContext2::GetInstance());
}
void C3DTransformContext::Menu8Selected()
{
}
void C3DTransformContext::Menu9Selected()
{
}

void C3DTransformContext::ApplyBtnPressed(void)
{
	(this->*ApplyTransformation)();
}

void C3DTransformContext::OnRadio4()
{
	switch(radio4Enum)
	{
	case 0:
		break;
	case 1:
		m_manager->LineParametersShow(SW_SHOW);
		break;
	case 2:
		m_manager->ClearInputArea();
		EnableRotationAboutALineParams();
		m_manager->SetHandleMouse(false);
		C3DTransformContext::ApplyTransformation = C3DTransformContext::RotateAboutAnyLine;
		break;
	}
}

void C3DTransformContext::OnRadio1()
{
	switch(radio4Enum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		m_manager->ClearInputArea();
		EnableRotate3DxParams();
		m_manager->SetHandleMouse(false);
		C3DTransformContext::ApplyTransformation = C3DTransformContext::Rotate3D;
		break;
	}
}

void C3DTransformContext::OnRadio2()
{
	switch(radio4Enum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		m_manager->ClearInputArea();
		EnableRotate3DxParams();
		m_manager->SetHandleMouse(false);
		C3DTransformContext::ApplyTransformation = C3DTransformContext::Rotate3D;
		break;
	}
}

void C3DTransformContext::OnRadio3()
{
	switch(radio4Enum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		m_manager->ClearInputArea();
		EnableRotate3DxParams();
		m_manager->SetHandleMouse(false);
		C3DTransformContext::ApplyTransformation = C3DTransformContext::Rotate3D;
		break;
	}
}

void C3DTransformContext::OnRadio5()
{
	switch(radio4Enum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		m_manager->ClearInputArea();
		EnableRotate3DxParams();
		m_manager->SetHandleMouse(true);
		C3DTransformContext::ApplyTransformation = C3DTransformContext::RotateObjAroundPoint;
		break;
	}
}

void C3DTransformContext::RotateObjAroundPoint()
{
	double angle = m_manager->GetInput1();
	angle = angle*PI / 180.0;

	CGraphPoint p(m_manager->GetMouseLoc().x, m_manager->GetMouseLoc().y);

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		CCompGraphObject* newObj = obj->GetNewInstance();
		obj->RotateAround2D(*newObj,p, angle);
		m_manager->SetCurrentGraphObject(newObj);
	}
//	m_manager->SetHandleMouse(false);
}

void C3DTransformContext::EnableTranslationParams(void)
{
	m_manager->SetInput1Name("X:(pxls)");
	m_manager->SetInput2Name("Y:(pxls)");
	m_manager->SetInput3Name("Z:(pxls)");
}

void C3DTransformContext::TranslateObject(void)
{
	int delX = (int)ceil(m_manager->GetInput1());
	int delY = (int)ceil(m_manager->GetInput2());
	int delZ = (int)ceil(m_manager->GetInput3());
	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		newObj = obj->GetNewInstance();
		obj->Translate3D(*newObj, delX, delY, delZ);
		m_manager->SetCurrentGraphObject(newObj);
	}
}

void C3DTransformContext::ScaleParamsEnable(void)
{
	m_manager->ClearInputArea();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->SetRadio1("Upscale");
	m_manager->SetRadio2("Downscale");
	m_manager->SetInput1Name("Scale Factor");
}

void C3DTransformContext::Scale(void)
{
	int sel = m_manager->GetRadioSel();
	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();
	if (obj != 0)
	{
		newObj = obj->GetNewInstance();
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

void C3DTransformContext::ShearParamsEnable(void)
{
	m_manager->ClearInputArea();
	m_manager->LineParametersShow(SW_HIDE);
	m_manager->SetRadio1("Shear in X axis");
	m_manager->SetRadio2("Shear in Y axis");
//	m_manager->SetRadio3("Shear in Z axiz");
	m_manager->SetInput1Name("Shearing Factor");
}

void C3DTransformContext::ShearObject(void)
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		newObj = obj->GetNewInstance();

		switch (sel)
		{
		case 0:
			obj->ShearX(*newObj, m_manager->GetInput1());
			break;
		case 1:
			obj->ShearY(*newObj, m_manager->GetInput1());
			break;
		case 2:
			//obj->ShearZ(*newObj, m_manager->GetInput1());
			break;
		}
		m_manager->SetCurrentGraphObject(newObj);
	}
}

void C3DTransformContext::EnableRotate3DxParams(void)
{
	int sel = m_manager->GetRadioSel();
	m_manager->SetRadio1("About X Axis");
	m_manager->SetRadio2("About Y Axis");
	m_manager->SetRadio3("About Z Axis");
	m_manager->SetRadio4("About Arbitrary Line");
	m_manager->SetRadio5("About Arbitrary Point");
	m_manager->SetInput1Name("Theta");
	m_manager->SetRadioSel(sel);
}

void C3DTransformContext::EnableReflection3DParams()
{
	m_manager->ClearRadio();
	m_manager->SetRadio1("About XY Plane");
	m_manager->SetRadio2("About XZ Plane");
	m_manager->SetRadio3("About YZ Plane");
	m_manager->SetRadio4("About Arbitrary Line");
}

void C3DTransformContext::EnableRotationAboutALineParams()
{
	m_manager->SetInput1Name("q1");
	m_manager->SetInput2Name("q2");
	m_manager->SetInput3Name("q3");
	m_manager->SetInput4Name("Theta");
}

void C3DTransformContext::Rotate3D(void)
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		newObj = obj->GetNewInstance();

		switch (sel)
		{
		case 0:
			obj->Rotate3Dx(*newObj, m_manager->GetInput1()*PI/180);
			break;
		case 1:
			obj->Rotate3Dy(*newObj, m_manager->GetInput1()*PI/180);
			break;
		case 2:
			obj->Rotate3Dz(*newObj, m_manager->GetInput1()*PI/180);
			break;
		case 3:
			break;
		case 4:
			break;
		}
		m_manager->SetCurrentGraphObject(newObj);
	}
}


void C3DTransformContext::Reflect3D()
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		bool bLine = false;
		CPoint p1, p2;
		newObj = obj->GetNewInstance();

		switch (sel)
		{
		case 0:
			obj->ReflectZ(*newObj);
			break;
		case 1:
			obj->ReflectY(*newObj);
			break;
		case 2:
			obj->ReflectX(*newObj);
			break;
		case 3:
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

void C3DTransformContext::RotateAboutAnyLine()
{
	double q1, q2, q3, theta;

	q1 = m_manager->GetInput1();
	q2 = m_manager->GetInput2();
	q3 = m_manager->GetInput3();
	theta = m_manager->GetInput4()*PI/180;

	double n1, n2, n3, Q;
	
	Q = sqrt( q1*q1 + q2*q2 + q3*q3 );
	if (Q == 0)
	{
		return;
	}

	n1 = q1 / Q;
	n2 = q2 / Q;
	n3 = q3 / Q;

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		newObj = obj->GetNewInstance();

		obj->Rotate3DAboutAnyLine(*newObj, n1, n2, n3, theta);
		m_manager->SetCurrentGraphObject(newObj);
	}

}


void C3DTransformContext::EnablePerspectiveProjectionParams()
{
	m_manager->SetInput1Name("Xp");
	m_manager->SetInput2Name("Yp");
	m_manager->SetInput3Name("Zp");
}

void C3DTransformContext::ProjectPerspective()
{
	double xp, yp, zp;

	xp = m_manager->GetInput1();
	yp = m_manager->GetInput2();
	zp = m_manager->GetInput3();

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (obj != 0)
	{
		newObj = obj->GetNewInstance();
		m_manager->SetCurrentGraphObject(obj, true);
		obj->ProjectPerspective(*newObj, xp, yp, zp);
		CDC* pDC = m_manager->GetRenderAreaDC();
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, 0xff);
		pDC->SelectObject(pen);
		newObj->DrawGraphObject(*pDC);
		pDC->SelectStockObject(BLACK_PEN);
		m_manager->ReleaseRenderAreaDC(pDC);
		delete newObj;
		newObj = 0;
	}
}
