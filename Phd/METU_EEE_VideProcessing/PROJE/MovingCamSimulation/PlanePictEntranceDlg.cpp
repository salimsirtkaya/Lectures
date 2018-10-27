// PlanePictEntranceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "PlanePictEntranceDlg.h"
#include ".\planepictentrancedlg.h"
#include "gdiplus.h"

// CPlanePictEntranceDlg dialog

IMPLEMENT_DYNAMIC(CPlanePictEntranceDlg, CDialog)
CPlanePictEntranceDlg::CPlanePictEntranceDlg(TRegionMap& rMap, Bitmap* &mask, CWnd* pParent /*=NULL*/)
	: CDialog(CPlanePictEntranceDlg::IDD, pParent),m_regionMap(rMap), m_maskBmp(mask)
{
//	m_maskBmp = mask;
	m_intensity = -1;
}

CPlanePictEntranceDlg::~CPlanePictEntranceDlg()
{
}

void CPlanePictEntranceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICT_FRAME, m_pictFrame);
	DDX_Control(pDX, IDC_COMBO1, m_intensityCombo);
	DDX_Control(pDX, IDC_CHECK1, m_isImoCheck);
	DDX_Control(pDX, IDC_EDIT2, m_paramsEdit);
	DDX_Control(pDX, IDC_LIST1, m_summaryList);
}


BEGIN_MESSAGE_MAP(CPlanePictEntranceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnOpenFile)
	ON_BN_CLICKED(IDC_BUTTON2, OnApplyParams)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnIntensitySelectionChange)
END_MESSAGE_MAP()


// CPlanePictEntranceDlg message handlers

BOOL CPlanePictEntranceDlg::DisplayMask()
{
	if (m_maskBmp == NULL)
	{
		return 0;
	}

	HDC hdc = ::GetDC(m_pictFrame.m_hWnd);
	CRect r;

	m_pictFrame.GetClientRect(&r);
	Graphics* m_pGraph = new Graphics(hdc);
	Status result;
	result = (Status) m_pGraph->DrawImage(m_maskBmp,(REAL) 0,(REAL) 0, (REAL)r.Width(),(REAL) r.Height() );
	delete m_pGraph;//This dynamic variable is free now.
	if (result == Ok) return 1;
	else return 0;
	
}
void CPlanePictEntranceDlg::OnOpenFile()
{
	TRegionMap::iterator it;
	Color clr;
	char szTitle[]="Select the planar world MASK file";
	TCHAR FileNameList[16384]= {0};
	TCHAR szFilters[]=_T("BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif|PNG Files (*.png)|*.png|TIFF Files (*.tif)|*.tif|All Files (*.*)|*.*||)");
	CFileDialog fileDlg(TRUE,_T("bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_EXPLORER ,szFilters);
	fileDlg.m_ofn.lpstrTitle=szTitle;
	fileDlg.m_ofn.lpstrFile=FileNameList;
	fileDlg.m_ofn.nMaxFile=16384;

	if (fileDlg.DoModal()==IDOK)
	{
		m_regionMap.clear();
		delete m_maskBmp;
		m_maskBmp = new Bitmap(fileDlg.GetPathName().AllocSysString());
		RedrawWindow();

		for (int i = 0; i < m_maskBmp->GetWidth(); i++)
		{
			for (int j = 0; j < m_maskBmp->GetHeight(); j++)
			{
				m_maskBmp->GetPixel(i, j, &clr);
				m_regionMap[clr.GetBlue()];
			}
		}

		int index = 0;
		it = m_regionMap.begin();
		while (it != m_regionMap.end())
		{
			CString str;
			str.Format("%d", it->first);
			m_intensityCombo.InsertString(index, str);
			m_intensityCombo.SetItemData(index++, it->first);
			it++;
		}
		m_intensityCombo.SetCurSel(0);
	}

}

void CPlanePictEntranceDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DisplayMask();
}

void CPlanePictEntranceDlg::OnIntensitySelectionChange()
{
    BYTE	intensity;
	Color	clr;

	intensity = m_intensityCombo.GetItemData(m_intensityCombo.GetCurSel());

	for (int i = 0; i < m_maskBmp->GetWidth(); i++)
	{
		for (int j = 0; j < m_maskBmp->GetHeight(); j++)
		{
			m_maskBmp->GetPixel(i, j, &clr);

			if (clr.GetBlue() == m_intensity)
			{
				Color clr2(m_intensity, m_intensity, m_intensity);
				m_maskBmp->SetPixel(i, j, clr2);
			}
			else
			{
				if (clr.GetBlue() == intensity)
				{
					Color clr2(255, 0, intensity);
					m_maskBmp->SetPixel(i, j, clr2);
				}
			}
		}
	}

	m_intensity = intensity;

	RedrawWindow();

}

void CPlanePictEntranceDlg::OnApplyParams()
{
    BYTE	intensity;
	CString s, param;
	int		sepIndex, sepIndex2;

	intensity = m_intensityCombo.GetItemData(m_intensityCombo.GetCurSel());
	m_paramsEdit.GetWindowText(s);	
	
	CPlanarPictureSegment &pps = m_regionMap[intensity];

	if (0 == m_isImoCheck.GetCheck()) //Plane
	{
		pps.m_isIMO = false;
		sepIndex = s.Find(";");
		param = s.Left(sepIndex);
		pps.m_planeOrMotion.m_plane.m_A = atof(param);
		sepIndex2 = s.Find(";", ++sepIndex);
		param = s.Mid(sepIndex, sepIndex2-sepIndex);
		pps.m_planeOrMotion.m_plane.m_B = atof(param);
		param = s.Mid(++sepIndex2, s.GetLength()-sepIndex2);
		pps.m_planeOrMotion.m_plane.m_C = atof(param);
	}
	else //IMO
	{
		pps.m_isIMO = true;
		sepIndex = s.Find(";");
		param = s.Left(sepIndex);
		pps.m_planeOrMotion.m_motion.m_u = atof(param);
		param = s.Mid(++sepIndex, s.GetLength()-sepIndex);
		pps.m_planeOrMotion.m_motion.m_v = atof(param);
	}
}