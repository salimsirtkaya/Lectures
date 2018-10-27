#include "stdafx.h"
#include "usercontext.h"
#include "642Manager.h"
#include "math.h"

CSpaceCurvesContext* CSpaceCurvesContext::m_context = 0;

CSpaceCurvesContext::CSpaceCurvesContext()
{
	m_contextName = "Draw Space Curves";
	m_contextInfo = "Draw Space Curves by User Input -- You can draw Space Curves in this menu. Select the type from the buttons on the upper left part of the window.";
	m_menuCount = 5;
	m_menuItems = new SMenuItem[m_menuCount];
	m_menuItems[0].menuInfo = "You can draw different end-conditioned Cubic Splines in this menu. Please note thati the user intervention  logic is different for clamped-end cubic spline. In clamped-end you enter 6 points then enter derivative values and press applly or enter. In other splines you enter 6 points and then enter the corresponding splines button.";
	m_menuItems[0].menuText = "Cubic Splines";
	m_menuItems[1].menuInfo = "You can draw space curves using paraboling blending in this menu. Select 4 points on the display area. The curve will be displayed automatically.";
	m_menuItems[1].menuText = "Parabolic Blending";	
	m_menuItems[2].menuInfo = "You can draw  Bezier curves in this menu. Select 6 points on the display area. The curve will be displayed automatically.";
	m_menuItems[2].menuText = "Bezier Curves";
	m_menuItems[3].menuInfo = "You can draw B-spline curves in this menu. Input the degree of the B-spline, select the points(variable) on the screen and press apply or enter.";
	m_menuItems[3].menuText = "B-Spline";

	m_menuItems[4].menuInfo = "Goes back to the main menu";
	m_menuItems[4].menuText = "Main Menu";
	
	m_userObj = 0;
	howManyInputs = 0;
	mPrincipleLine.RemoveAllPoints();
}

CSpaceCurvesContext::~CSpaceCurvesContext()
{
	delete m_userObj;
	m_userObj = 0;
}

CUserContext* CSpaceCurvesContext::GetInstance()
{
	if (CSpaceCurvesContext::m_context == 0)
	{
		CSpaceCurvesContext::m_context = new CSpaceCurvesContext();
	}
	return CSpaceCurvesContext::m_context;
}

void CSpaceCurvesContext::DrawPrinciplePoint(CDC* pDC, CPoint pt)
{
	pDC->MoveTo(pt);
	CBrush br;
	br.CreateSolidBrush(0xff00);
	CRect r(pt.x-2, -(pt.y-2), pt.x+2, -(pt.y+2));
	pDC->FillRect(r, &br);
	br.DeleteObject();
}

void CSpaceCurvesContext::DrawPrincipleLines(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_DOT, 1, 0xff00);
	CPen* oldPen = pDC->SelectObject(&pen);
	mPrincipleLine.DrawGraphObject(*pDC, false);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void CSpaceCurvesContext::RenderAreaLButtonDown(UINT nFlags, CPoint point)
{

	if (mPrincipleLine.GetPointCount() < howManyInputs)
	{
		CPoint pt = m_manager->GetMouseLoc();

		CDC* pDC = m_manager->GetRenderAreaDC();

		DrawPrinciplePoint(pDC, pt);		

		mPrincipleLine.AddNewPoint(pt.x, pt.y);
		m_guideXs[mPrincipleLine.GetPointCount()-1] = pt.x;
		m_guideYs[mPrincipleLine.GetPointCount()-1] = pt.y;

		DrawPrincipleLines(pDC);
		m_manager->ReleaseRenderAreaDC(pDC);
	}

	if (mPrincipleLine.GetPointCount() == howManyInputs)
	{
		if ( howManyInputs == 4 ) //parabolic blending
		{
			ParabolicBlending();
			mPrincipleLine.RemoveAllPoints();
		}
		else if ( howManyInputs == 6 ) //bezier
		{
			BezierCurve();
			mPrincipleLine.RemoveAllPoints();
		}
	}
}

void CSpaceCurvesContext::BezierCurve()
{
	int i,j;
	float bsx=0,bsy=0,fj;

	CDC* pDC = m_manager->GetRenderAreaDC();
	for (j=0;j<2000;j++)
	{
		fj=float(j);
		bsx=((1*m_guideXs[0]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000)))
			+(5*m_guideXs[1]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(fj/2000))
			+(10*m_guideXs[2]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(fj/2000)*(fj/2000))
			+(10*m_guideXs[3]*(1-(fj/2000))*(1-(fj/2000))*(fj/2000)*(fj/2000)*(fj/2000))
			+(5*m_guideXs[4]*(1-(fj/2000))*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000))
			+(1*m_guideXs[5]*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000)));

		bsy=((1*m_guideYs[0]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000)))
			+(5*m_guideYs[1]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(fj/2000))
			+(10*m_guideYs[2]*(1-(fj/2000))*(1-(fj/2000))*(1-(fj/2000))*(fj/2000)*(fj/2000))
			+(10*m_guideYs[3]*(1-(fj/2000))*(1-(fj/2000))*(fj/2000)*(fj/2000)*(fj/2000))
			+(5*m_guideYs[4]*(1-(fj/2000))*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000))
			+(1*m_guideYs[5]*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000)*(fj/2000)));

		pDC->SetPixelV(bsx,-bsy,0xff);
	} // for j

	m_manager->ReleaseRenderAreaDC(pDC);
}

void CSpaceCurvesContext::ParabolicBlending()
{
	int i,j,X,Y,B,color;
	float pbx[4],pby[4];
	int num;
	char text[8];
	float gama1,d,alfa,to,cos_teta1,gama2,e,beta,t,cos_teta2,fj,rt,st;
	float Pofr_x,Pofr_y,Qofs_x,Qofs_y,Coft_x,Coft_y;
	
	gama1=(((m_guideXs[1]-m_guideXs[0])*(m_guideXs[2]-m_guideXs[0]))+((m_guideYs[1]-m_guideYs[0])*(m_guideYs[2]-m_guideYs[0])))/(((m_guideXs[2]-m_guideXs[0])*(m_guideXs[2]-m_guideXs[0]))+((m_guideYs[2]-m_guideYs[0])*(m_guideYs[2]-m_guideYs[0])));
	d=sqrt(((m_guideXs[2]-m_guideXs[0])*(m_guideXs[2]-m_guideXs[0]))+((m_guideYs[2]-m_guideYs[0])*(m_guideYs[2]-m_guideYs[0])));
	alfa=1/(d*d*gama1*(1-gama1));
	to=sqrt(((m_guideXs[2]-m_guideXs[1])*(m_guideXs[2]-m_guideXs[1]))+((m_guideYs[2]-m_guideYs[1])*(m_guideYs[2]-m_guideYs[1])));
	cos_teta1=(((m_guideXs[2]-m_guideXs[1])*(m_guideXs[2]-m_guideXs[0]))+((m_guideYs[2]-m_guideYs[1])*(m_guideYs[2]-m_guideYs[0])))/(to*d);
	
	gama2=(((m_guideXs[2]-m_guideXs[1])*(m_guideXs[3]-m_guideXs[1]))+((m_guideYs[2]-m_guideYs[1])*(m_guideYs[3]-m_guideYs[1])))/(((m_guideXs[3]-m_guideXs[1])*(m_guideXs[3]-m_guideXs[1]))+((m_guideYs[3]-m_guideYs[1])*(m_guideYs[3]-m_guideYs[1])));
	e=sqrt(((m_guideXs[3]-m_guideXs[1])*(m_guideXs[3]-m_guideXs[1]))+((m_guideYs[3]-m_guideYs[1])*(m_guideYs[3]-m_guideYs[1])));
	beta=1/(e*e*gama2*(1-gama2));
	cos_teta2=(((m_guideXs[2]-m_guideXs[1])*(m_guideXs[3]-m_guideXs[1]))+((m_guideYs[2]-m_guideYs[1])*(m_guideYs[3]-m_guideYs[1])))/(to*e);
	
	CDC* pDC = m_manager->GetRenderAreaDC();
	for (j=0;j<=1000;j++)
	{
		fj=float(j);
		t=to*fj/1000;
		rt=gama1*d+t*cos_teta1;
		st=t*cos_teta2;
		Pofr_x=m_guideXs[0]+((m_guideXs[2]-m_guideXs[0])*rt/d)+(alfa*rt*(d-rt)*((m_guideXs[1]-m_guideXs[0])-(gama1*(m_guideXs[2]-m_guideXs[0]))));
		Pofr_y=m_guideYs[0]+((m_guideYs[2]-m_guideYs[0])*rt/d)+(alfa*rt*(d-rt)*((m_guideYs[1]-m_guideYs[0])-(gama1*(m_guideYs[2]-m_guideYs[0]))));
		Qofs_x=m_guideXs[1]+((m_guideXs[3]-m_guideXs[1])*st/e)+(beta*st*(e-st)*((m_guideXs[2]-m_guideXs[1])-(gama2*(m_guideXs[3]-m_guideXs[1]))));
		Qofs_y=m_guideYs[1]+((m_guideYs[3]-m_guideYs[1])*st/e)+(beta*st*(e-st)*((m_guideYs[2]-m_guideYs[1])-(gama2*(m_guideYs[3]-m_guideYs[1]))));
		Coft_x=((1-(t/to))*Pofr_x) + (Qofs_x*t/to);
		Coft_y=((1-(t/to))*Pofr_y) + (Qofs_y*t/to);
		
		pDC->SetPixelV(Coft_x,-Coft_y, 0xff);
	} // for j

	m_manager->ReleaseRenderAreaDC(pDC);
}
void CSpaceCurvesContext::Menu1Selected()
{
	CUserContext::Menu1Selected();
	m_manager->ChangeContext(CCubicSplineContext::GetInstance());
//	m_manager->ShowApplyBtn(SW_SHOW);
	m_manager->ShowMenu9("Create New Point Set");
	howManyInputs = 0;
	m_manager->ClearInputArea();
	mPrincipleLine.RemoveAllPoints();
	m_manager->SetCurrentGraphObject(0, true);
}

void CSpaceCurvesContext::Menu2Selected()
{
	CUserContext::Menu2Selected();
	//parabolic blending
	howManyInputs = 4;
	m_manager->ClearInputArea();
	m_manager->ShowMenu9("",false);
	mPrincipleLine.RemoveAllPoints();
	m_manager->SetCurrentGraphObject(0, true);

}

void CSpaceCurvesContext::Menu3Selected()
{
	CUserContext::Menu3Selected();
	//bezier
	howManyInputs = 6;
	mPrincipleLine.RemoveAllPoints();
	m_manager->ClearInputArea();
	m_manager->ShowMenu9("",false);
	m_manager->SetCurrentGraphObject(0, true);
}

void CSpaceCurvesContext::Menu4Selected()
{
	CUserContext::Menu4Selected();
	howManyInputs = 20;
	m_manager->SetInput1Name("Poly Deg:");
	CSpaceCurvesContext::ApplyTransformation =	CSpaceCurvesContext::BSpline;
	m_manager->ShowMenu9("Create New Point Set");
}

void CSpaceCurvesContext::Menu5Selected()
{
	CUserContext::Menu5Selected();
	howManyInputs = 0;
	m_manager->ClearInputArea();
	m_manager->ShowMenu9("",false);
	m_manager->ChangeContext(CMainContext2::GetInstance());
	m_manager->SetCurrentGraphObject(0, true);
}

void CSpaceCurvesContext::Menu6Selected()
{
	CUserContext::Menu6Selected();
}

void CSpaceCurvesContext::Menu7Selected()
{
	CUserContext::Menu7Selected();
}
void CSpaceCurvesContext::Menu8Selected()
{
	CUserContext::Menu8Selected();
}
void CSpaceCurvesContext::Menu9Selected()
{
	mPrincipleLine.RemoveAllPoints();
	m_manager->SetCurrentGraphObject(0);
}

void CSpaceCurvesContext::ApplyBtnPressed()
{
	(this->*ApplyTransformation)();
}

void CSpaceCurvesContext::BSpline()
{
	int n = mPrincipleLine.GetPointCount();
	int ks = m_manager->GetInput1();


	int i,j,k,s,tmax,X,Y,B;
	int num;
	float t,bs_px,bs_py,temp1,temp2;
	int knot[20];
	float N[20][20];

	for (i=0;i<20;i++)
		knot[i]=0;
	bs_px=0;bs_py=0;


	n=n-1;
	tmax=n-ks+2;
	for (i=0;i<ks;i++)
		knot[i]=0;
	for (i=ks;i<tmax+ks-1;i++)
		knot[i]=i-ks+1;
	for (i=0;i<ks;i++)
		knot[ks+tmax-1+i]=tmax;

	CDC* pDC = m_manager->GetRenderAreaDC();

	for (j=0;j<=tmax*1000;j++)
	{
		t=float(j)/1000;
		for (k=1;k<=ks;k++)
		{
			for (i=0;i<=n;i++)
			{
				if(k==1)
				{
					if(((t>=knot[i])&&(t<knot[i+1]))||(t==knot[i]))
						N[i][k]=1;
					else
						N[i][k]=0;
				}
				else
				{
					if ((knot[i+k-1]-knot[i])==0)
						temp1=0;
					else
						temp1=((t-knot[i])*N[i][k-1]/(knot[i+k-1]-knot[i]));
					if ((knot[i+k]-knot[i+1])==0)
						temp2=0;
					else
						temp2=((knot[i+k]-t)*N[i+1][k-1]/(knot[i+k]-knot[i+1]));

					N[i][k]= temp1 + temp2;
				}
			}
		}
		for(s=0;s<=n;s++)
		{
			bs_px = bs_px+m_guideXs[s]*N[s][ks];
			bs_py = bs_py+m_guideYs[s]*N[s][ks];
		}
		pDC->SetPixelV(bs_px, -bs_py, 0xff0000);
		bs_px=0;
        bs_py=0;
	}

	m_manager->ReleaseRenderAreaDC(pDC);


}
