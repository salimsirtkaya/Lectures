#include "stdafx.h"
#include "642Manager.h"
#include "userContext.h"

CSurfaceContext* CSurfaceContext::m_context = 0;

CSurfaceContext::CSurfaceContext()
{
	recentInputPointCount = 0;
	this->surfaceMethod = 3; 

	m_contextName = "Surface Menu";
	m_contextInfo = "Surface Menu -- You can draw 3D surfaces in this menu. Select the type of the surface from the buttons and mark four corner points on the display area. Do not forget to input the z-axis value for each point (default is set to 0).";
	m_menuCount = 8;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "Draw a blinear surface";
	m_menuItems[0].menuText = "Bilinear Surface";
	m_menuItems[1].menuInfo = "Draw lofted surface. Select the type of the edges from the radio buttons. The end conditions for the clamped spline is fixed to 100 , -100, -100 for x,y and z axes respectively for both ends and both splines.";
	m_menuItems[1].menuText = "Lofted Surface";

	m_menuItems[2].menuInfo = "Draw Linear Coons Surface. Edge curves are cubic splines. Select the edge points by clicking the display area. Edge conditions can be loaded by pressing the -Load End Conditions- button and selecting a proper .txt file. BiLinearCoonsEndConds.txt is suitable for this example.";
	m_menuItems[2].menuText = "Linear Coons Surface";

	m_menuItems[3].menuInfo = "Draw Bicubic Coons Surface. Select the edge points by clicking the display area. Edge conditions can be loaded by pressing the -Load End Conditions- button and selecting a proper .txt file. BicubicCoonsEndConds.txt is suitable for this example.";
	m_menuItems[3].menuText = "Bicubic Coons Surface";
	
	m_menuItems[4].menuInfo = "Draw Bezier Surface. Load the defining mesh of the bezier surface by pressing the -Load Defining Mesh- button and selecting a proper .txt file. BezierDefiningMesh_1.txt is suitable for this example.";
	m_menuItems[4].menuText = "Bezier Surface";

	m_menuItems[5].menuInfo = "Draw Bezier Surface. Load the defining mesh of the bezier surface by pressing the -Load Defining Mesh- button and selecting a proper .txt file. BezierDefiningMesh_1.txt is suitable for this example.";
	m_menuItems[5].menuText = "B-Spline Surface";

	m_menuItems[6].menuInfo = "Select a transformation on the current 3D graphics object";
	m_menuItems[6].menuText = "Edit";
	m_menuItems[7].menuInfo = "Go to main menu";
	m_menuItems[7].menuText = "Main";
}

CSurfaceContext::~CSurfaceContext()
{
}

CUserContext* CSurfaceContext::GetInstance()
{
	if (CSurfaceContext::m_context == 0)
	{
		CSurfaceContext::m_context = new CSurfaceContext();
	}
	return CSurfaceContext::m_context;
}

void CSurfaceContext::Menu1Selected()
{
	CUserContext::Menu1Selected();

	CSurfaceContext::ApplyTransformation = CSurfaceContext::BilinearSurface;
	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");
	m_manager->ShowMenu9("", false);
}

void CSurfaceContext::Menu2Selected()
{
	CUserContext::Menu2Selected();

	ApplyTransformation = CSurfaceContext::LoftedSurface;
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");

	m_manager->SetRadio1("Clamped End");
	m_manager->SetRadio2("Relaxed End");
	m_manager->SetRadio3("Cyclic");
	m_manager->SetRadio4("Anti-Cyclic");

	m_manager->ShowMenu9("", false);
}

void CSurfaceContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");
	m_manager->ShowMenu9("Load End Conditions");

	ApplyTransformation = LinearCoons;
	surfaceMethod = 3;
}

void CSurfaceContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->SetInput1Name("1.Z");
	m_manager->SetInput4Name("2.Z");
	m_manager->SetInput2Name("3.Z");
	m_manager->SetInput5Name("4.Z");
	m_manager->ShowMenu9("Load End Conditions");

	ApplyTransformation = BicubicCoons;
	surfaceMethod = 4;
}

void CSurfaceContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->ShowMenu9("Load Defining Mesh");
	m_manager->ShowApplyBtn(SW_HIDE);

	surfaceMethod = 5;
}

void CSurfaceContext::Menu6Selected()
{
	CUserContext::Menu6Selected();

	m_manager->ClearRadio();
	m_manager->ClearInputArea();
	m_manager->ShowMenu9("Load Defining Mesh");
	m_manager->ShowApplyBtn(SW_HIDE);

	surfaceMethod = 6;
}

void CSurfaceContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();

	m_manager->ShowMenu9("", false);
	m_manager->ChangeContext(C3DTransformContext::GetInstance());
}

void CSurfaceContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
	m_manager->ClearRadio();
	m_manager->ClearInputArea();

	m_manager->ShowMenu9("", false);
	m_manager->ChangeContext(CMainContext2::GetInstance());
}


void CSurfaceContext::ReadLinearCoonsFile(CString file)
{
		FILE *read_stream;
	char cline[400], text[15];
	float sample;
	read_stream  = fopen( file, "r" );
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );

	for (int k=0;k<4;k++)
	{
		fscanf (read_stream, "%s\t", &text);
		fscanf (read_stream, "%s\t", &text);
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				fscanf (read_stream, "%g\t", &sample);
				tempMm[i+1][k][j] = sample;
			}
		}
	}
	fclose(read_stream);
}

void CSurfaceContext::ReadBicubicCoonsFile(CString file)
{
	FILE *read_stream;
	char cline[400], text[15];
	float sample;
	read_stream  = fopen( file, "r" );
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );

	for (int k=0;k<4;k++)
	{
		fscanf (read_stream, "%s\t", &text);
		fscanf (read_stream, "%s\t", &text);
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				fscanf (read_stream, "%g\t", &sample);
				tempMm[i+1][k][j] = sample;
			}
		}
	}
	fclose(read_stream);
}

void CSurfaceContext::ReadBezierFile(CString file)
{
	FILE *read_stream;
	char cline[400], text[15];
	float s1, s2, s3;
	read_stream  = fopen( file, "r" );
	int i,j,k,iw,iu;
	int tempNum_u, tempNum_w;

	fscanf(read_stream,"%d\t",&tempNum_u);
	fscanf(read_stream,"%d\t",&tempNum_w);
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );


	bezierSurface.RemoveAllPoints();
	bezierSurface.SetNumU(tempNum_u);
	bezierSurface.SetNumW(tempNum_w);

	for (i=0;i<tempNum_u;i++)
	{
		for (j=0;j<tempNum_w;j++)
		{
			fscanf (read_stream, "%g\t", &s1);
			fscanf (read_stream, "%g\t", &s2);
			fscanf (read_stream, "%g\t", &s3);
			bezierSurface.AddNewPoint(s1, s2, s3);
		}
	}
	fclose(read_stream);
}

void CSurfaceContext::ReadBSplineFile(CString file)
{
	FILE *read_stream;
	char cline[400], text[15];
	float s1, s2, s3;
	read_stream  = fopen( file, "r" );
	int i,j,k,iw,iu;
	int tempNum_u, tempNum_w;

	bSplineSurface.RemoveAllPoints();

	fscanf(read_stream,"%d\t",&tempNum_u);
	fscanf(read_stream,"%d\t",&tempNum_w);
	bSplineSurface.SetNumN(tempNum_u);
	bSplineSurface.SetNumKu(tempNum_w);

	fscanf(read_stream,"%d\t",&tempNum_u);
	fscanf(read_stream,"%d\t",&tempNum_w);
	bSplineSurface.SetNumM(tempNum_u);
	bSplineSurface.SetNumKw(tempNum_w);
	fgets(cline, 400, read_stream );
	fgets(cline, 400, read_stream );



	for (i=0;i<bSplineSurface.GetNumN();i++)
	{
		for (j=0;j<bSplineSurface.GetNumM();j++)
		{
			fscanf (read_stream, "%g\t", &s1);
			fscanf (read_stream, "%g\t", &s2);
			fscanf (read_stream, "%g\t", &s3);
			bSplineSurface.AddNewPoint(s1, s2, s3);
		}
	}
	fclose(read_stream);
}

void CSurfaceContext::Menu9Selected()
{
	char szTitle[]="Select the END CONDITIONS file";
	TCHAR FileNameList[16384]= {0};
	TCHAR szFilters[]=_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||)");
	CFileDialog fileDlg(TRUE,_T("txt"),_T("*.txt"),OFN_HIDEREADONLY|OFN_EXPLORER ,szFilters);
	fileDlg.m_ofn.lpstrTitle=szTitle;
	fileDlg.m_ofn.lpstrFile=FileNameList;
	fileDlg.m_ofn.nMaxFile=16384;
	CString file;
	POSITION filePosition;

	if (fileDlg.DoModal()==IDOK)
	{
		filePosition = fileDlg.GetStartPosition();
		
		if(filePosition!=NULL)
		{
			file = fileDlg.GetNextPathName(filePosition);
			if(surfaceMethod == 3)//linearCoons
			{
				ReadLinearCoonsFile(file);
			}
			else if (surfaceMethod == 4) //bicubic Coons
			{
				ReadBicubicCoonsFile(file);
			}
			else if (surfaceMethod == 5)
			{
				ReadBezierFile(file);
				BezierSurface();
			}
			else if (surfaceMethod == 6)
			{
				ReadBSplineFile(file);
 				BSplineSurface();
			}
		}
	}
}

void CSurfaceContext::ApplyBtnPressed()
{
	(this->*ApplyTransformation)();
}

void CSurfaceContext::LoftedSurface()
{
	CCompGraphObject *newObj = new CLoftedSurface();

	((CLoftedSurface*)newObj)->SetLoftMode(m_manager->GetRadioSel());
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;

}

void CSurfaceContext::BilinearSurface()
{
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

	CCompGraphObject* newObj = new CBilinearSurface();

	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;
}

void CSurfaceContext::BicubicCoons()
{
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

/*	CCompGraphObject* newObj = m_manager->GetCurrentGraphObject();
	if (dynamic_cast<CBicubicCoonsSurface*>(this) == 0)
	{
		newObj = new CBicubicCoonsSurface();
	}
	*/
	CBicubicCoonsSurface* newObj = new CBicubicCoonsSurface();
	
	for (int k=0;k<4;k++)
	{
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				newObj->SetMParam(tempMm[i+1][k][j], i+1, k, j);
			}
		}
	}
	
	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}
	
	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;

}

void CSurfaceContext::BSplineSurface()
{
	CCompGraphObject* newObj = bSplineSurface.GetNewInstance();
	
	POSITION pos = bSplineSurface.m_points.GetHeadPosition();

	CGraphPoint pt;
	
	while(pos!=0)
	{
		pt = bSplineSurface.m_points.GetNext(pos);
		newObj->AddNewPoint(pt.x, pt.y, pt.z);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;
}

void CSurfaceContext::BezierSurface()
{
	CCompGraphObject* newObj = bezierSurface.GetNewInstance();
	
	POSITION pos = bezierSurface.m_points.GetHeadPosition();

	CGraphPoint pt;
	
	while(pos!=0)
	{
		pt = bezierSurface.m_points.GetNext(pos);
		newObj->AddNewPoint(pt.x, pt.y, pt.z);
	}

	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;
}

void CSurfaceContext::LinearCoons()
{
	m_guideZs[0] = m_manager->GetInput1();
	m_guideZs[1] = m_manager->GetInput4();
	m_guideZs[2] = m_manager->GetInput2();
	m_guideZs[3] = m_manager->GetInput5();

/*	CCompGraphObject* newObj = m_manager->GetCurrentGraphObject();
	if (dynamic_cast<CBicubicCoonsSurface*>(this) == 0)
	{
		newObj = new CBicubicCoonsSurface();
	}
	*/
	CLinearCoonsSurface* newObj = new CLinearCoonsSurface();
	
	for (int k=0;k<4;k++)
	{
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				newObj->SetMParam(tempMm[i+1][k][j], i+1, k, j);
			}
		}
	}
	
	for(int i = 0; i < 4; i++)
	{
		newObj->AddNewPoint(m_guideXs[i], m_guideYs[i], m_guideZs[i]);
	}
	
	m_manager->SetCurrentGraphObject(newObj, true);
	
	recentInputPointCount = 0;

}

void CSurfaceContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt = m_manager->GetMouseLoc();
	
	m_guideXs[recentInputPointCount] = pt.x;
	m_guideYs[recentInputPointCount] = pt.y;

	CDC* pDC = m_manager->GetRenderAreaDC();

	DrawPrinciplePoint(pDC, pt);		

	m_manager->ReleaseRenderAreaDC(pDC);

	recentInputPointCount++;
}

void CSurfaceContext::DrawPrinciplePoint(CDC* pDC, CPoint pt)
{
	pDC->MoveTo(pt);
	CBrush br;
	br.CreateSolidBrush(0xff00);
	CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
	pDC->FillRect(r, &br);
	br.DeleteObject();
}
