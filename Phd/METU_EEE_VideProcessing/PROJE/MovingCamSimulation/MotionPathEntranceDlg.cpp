// MotionPathEntranceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "MotionPathEntranceDlg.h"
#include ".\motionpathentrancedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionPathEntranceDlg dialog


CMotionPathEntranceDlg::CMotionPathEntranceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotionPathEntranceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotionPathEntranceDlg)
	m_pathPointString = _T("");
	//}}AFX_DATA_INIT
}

void CMotionPathEntranceDlg::DDX_PathPoint( CDataExchange* pDX, int nIDC, CString& value)
{
	if (pDX->m_bSaveAndValidate)
	{
		//value.
	}
};

void CMotionPathEntranceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionPathEntranceDlg)
	DDX_Control(pDX, IDC_LIST1, m_pathPointsList);
	DDX_Text(pDX, IDC_EDIT1, m_pathPointString);
	//}}AFX_DATA_MAP
	DDX_PathPoint(pDX, IDC_EDIT1, m_pathPointString);
}


BEGIN_MESSAGE_MAP(CMotionPathEntranceDlg, CDialog)
	//{{AFX_MSG_MAP(CMotionPathEntranceDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnMovePointDown)
	ON_BN_CLICKED(IDC_BUTTON2, OnMovePointUp)
	ON_BN_CLICKED(IDC_BUTTON3, OnDeletePoint)
	ON_BN_CLICKED(IDC_BUTTON4, OnChangePoint)
	ON_BN_CLICKED(IDC_BUTTON5, OnAddNewPoint)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangePathPointsList)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionPathEntranceDlg message handlers
void CMotionPathEntranceDlg::RegisterPathPointsList(CList<C3DMotion, C3DMotion>* points)
{
	m_camMotionPathPoints = points;
}

void CMotionPathEntranceDlg::OnMovePointDown() 
{
	int sel = m_pathPointsList.GetCurSel();

	if ( (sel != LB_ERR) && (sel < m_pathPointsList.GetCount()-1))
	{
		CString	swap;
		m_pathPointsList.GetText(sel, swap);
		m_pathPointsList.InsertString(sel+2, swap);
		m_pathPointsList.DeleteString(sel);
		m_pathPointsList.SetCurSel(sel+1);
	}
}

void CMotionPathEntranceDlg::OnMovePointUp() 
{
	int sel = m_pathPointsList.GetCurSel();

	if (sel > 0)
	{
		CString	swap;
		m_pathPointsList.GetText(sel-1, swap);
		m_pathPointsList.InsertString(sel+1, swap);
		m_pathPointsList.DeleteString(sel-1);
		m_pathPointsList.SetCurSel(sel-1);
	}	
}

void CMotionPathEntranceDlg::OnDeletePoint() 
{
	int sel = m_pathPointsList.GetCurSel();

	if (sel != LB_ERR)
	{
		m_pathPointsList.DeleteString(sel);
	}		
}

void CMotionPathEntranceDlg::OnChangePoint() 
{
	UpdateData();
	int sel = m_pathPointsList.GetCurSel();
	if (sel != LB_ERR)
	{
		m_pathPointsList.InsertString(sel, m_pathPointString);
		m_pathPointsList.DeleteString(sel+1);
	}	
}

void CMotionPathEntranceDlg::OnAddNewPoint() 
{
	UpdateData();
	m_pathPointsList.InsertString(-1, m_pathPointString);
}

void CMotionPathEntranceDlg::OnSelchangePathPointsList() 
{
	int sel = m_pathPointsList.GetCurSel();

	if (sel != LB_ERR)
	{
		CString	swap;
		m_pathPointsList.GetText(sel, swap);
		m_pathPointString = swap;
		UpdateData(FALSE);
	}		
}

void CMotionPathEntranceDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CMotionPathEntranceDlg::OnInitDialog() 
{
	POSITION	 pos;

	CDialog::OnInitDialog();
	
	pos = m_camMotionPathPoints->GetHeadPosition();

	while (NULL != pos)
	{
		C3DMotion motion;
		CString str;
		motion = m_camMotionPathPoints->GetNext(pos);
		str = motion.ParametersString();

		m_pathPointsList.InsertString(-1, str);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMotionPathEntranceDlg::OnBnClickedOk()
{
	m_camMotionPathPoints->RemoveAll();

	for (int i = 0; i < m_pathPointsList.GetCount(); i++)
	{
		CString s;
		m_pathPointsList.GetText(i, s);
		m_camMotionPathPoints->AddTail(C3DMotion(s));
	}

	OnOK();
}
