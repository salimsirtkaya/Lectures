#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"
#include "math.h"

#define PI 3.1415926535
C3DTransformContext* C3DTransformContext::m_context = 0;

C3DTransformContext::C3DTransformContext()
{
	m_contextName = "3D Object Transformation";
	m_menuCount = 8;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Scales by input parameters -- Select the type of scaling [down or upscale] and the scale parameter";
	m_menuItems[0].menuText = "Translation";
	m_menuItems[1].menuInfo = "Sheares by input parameters -- Select the axis of shear and input the shearing factor";
	m_menuItems[1].menuText = "Scaling";
	m_menuItems[2].menuInfo = "Rotates by input parameters about the origin -- Input the angle of rotation in degrees";
	m_menuItems[2].menuText = "Reflection wrt Main Planes";
	m_menuItems[3].menuInfo = "Translates by input parameters -- Input the X and Y axes translations in pixels";
	m_menuItems[3].menuText = "Rotation wrt Main Axes";
	m_menuItems[4].menuInfo = "Rotates about an arbitrary point -- Select the point with left clicking your mouse on the display area and input the rotation angle in degrees";
	m_menuItems[4].menuText = "Rotation wrt Arbitrary Line";
	m_menuItems[5].menuInfo = "Reflects the object -- Select the type of reflection [X-axis, Y-axis or wrt an arbitrary line]. Input the line equation for the arbitrary line";
	m_menuItems[5].menuText = "Shearing";
	m_menuItems[6].menuInfo = "Goes back to the main menu";
	m_menuItems[6].menuText = "Perspective Projection";
	m_menuItems[7].menuInfo = "Goes back to the main menu";
	m_menuItems[7].menuText = "Main Menu";
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
	EnableTranslationParams();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::TranslateObject;
}

void C3DTransformContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	m_manager->ClearInputArea();
	ScaleParamsEnable();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Scale;
}

void C3DTransformContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearInputArea();
	EnableReflection3DParams();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Reflect3D;
}

void C3DTransformContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	EnableRotate3DxParams();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::Rotate3D;
}

void C3DTransformContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	EnableRotationAboutALineParams();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::RotateAboutAnyLine;
}

void C3DTransformContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
	m_manager->ClearInputArea();
	ShearParamsEnable();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::ShearObject;
}

void C3DTransformContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	EnablePerspectiveProjectionParams();
	C3DTransformContext::ApplyTransformation = C3DTransformContext::ProjectPerspective;
}
void C3DTransformContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
	m_manager->ClearInputArea();
	m_manager->ClearRadio();
	m_manager->ChangeContext(CMainContext::GetInstance());
}
void C3DTransformContext::Menu9Selected()
{
}

void C3DTransformContext::ApplyBtnPressed(void)
{
	(this->*ApplyTransformation)();
}

void C3DTransformContext::EnableTranslationParams(void)
{
	m_manager->SetInput1Name("X:");
	m_manager->SetInput2Name("Y:");
	m_manager->SetInput3Name("Z:");
}

void C3DTransformContext::TranslateObject(void)
{
	int delX = (int)ceil(m_manager->GetInput1());
	int delY = (int)ceil(m_manager->GetInput2());
	int delZ = (int)ceil(m_manager->GetInput3());
	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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
	m_manager->SetRadio1("About X Axis");
	m_manager->SetRadio2("About Y Axis");
	m_manager->SetRadio3("About Z Axis");
	m_manager->SetInput1Name("Theta");
}

void C3DTransformContext::EnableReflection3DParams()
{
	m_manager->SetRadio1("About XY Plane");
	m_manager->SetRadio2("About XZ Plane");
	m_manager->SetRadio3("About YZ Plane");
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

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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
		}
		m_manager->SetCurrentGraphObject(newObj);
	}
}


void C3DTransformContext::Reflect3D()
{
	int sel = m_manager->GetRadioSel();

	CCompGraphObject* newObj = 0;

	CCompGraphObject* obj = m_manager->GetCurrentGraphObject();

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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
		}
		m_manager->SetCurrentGraphObject(newObj);
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

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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

	if (dynamic_cast<CTriCube*>(obj) != 0)
	{
		newObj = new CTriCube();
	}
	else
	{
		if (dynamic_cast<CPrism*>(obj) != 0)
		{
			newObj = new CPrism();
		}
	}
	if (newObj != 0)
	{
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
