/*EE706 PROJECT*/
/*Salim SIRTKAYA*/


#include "stdafx.h"


//#include <dshow.h>
//#include <qedit.h>
//#include <math.h>
//#include "MpegFile.h"
//#include "DirectShowWrapper.h"
//#include <math.h>
//
////#include "GdiplusWrapper.h"
//#include  <wingdi.h>
#include "VIMEK.h"
#include "VIMEKDlg.h"
#include ".\vimekdlg.h"
//#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVIMEKDlg dialog

CVIMEKDlg::CVIMEKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVIMEKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVIMEKDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVIMEKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVIMEKDlg)
	DDX_Control(pDX, IDC_STATIC_Tz, m_Tz);
	DDX_Control(pDX, IDC_STATIC_Ty, m_Ty);
	DDX_Control(pDX, IDC_STATIC_Tx, m_Tx);
	DDX_Control(pDX, IDC_STATIC_Rz, m_Rz);
	DDX_Control(pDX, IDC_STATIC_Ry, m_Ry);
	DDX_Control(pDX, IDC_STATIC_Rx, m_Rx);
	DDX_Control(pDX, IDC_STATIC_TRANSLATION, m_translation);
	DDX_Control(pDX, IDC_STATIC_ROTATION, m_rotation);
	DDX_Control(pDX, IDC_STATIC_MOTION, m_motion);
	DDX_Control(pDX, IDC_STATIC2, m_frame2);
	DDX_Control(pDX, IDC_STATIC1, m_frame1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVIMEKDlg, CDialog)
	//{{AFX_MSG_MAP(CVIMEKDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, OnOpenFrames)
	ON_BN_CLICKED(IDC_BUTTON1, OnExtractFeatures)
	ON_BN_CLICKED(IDC_BUTTON2, OnTrackFeatures)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVIMEKDlg message handlers

void CVIMEKDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the dc
		dc.DrawIcon(x, y, m_hIcon);		
	}

	else
	{
		m_vimek.ShowFrame(&m_frame1, 1);
		m_vimek.ShowFrame(&m_frame2, 2);
		m_vimek.DisplayFeatures(&m_frame1);
		CDialog::OnPaint();
	}
}

HCURSOR CVIMEKDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CVIMEKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//Extra code
	myFont1.CreateFont(22,
					  10,
					   0,
					   0,
					   FW_BOLD,
					   0,
					   0,
					   0,
					   DEFAULT_CHARSET,
					   OUT_DEVICE_PRECIS,
					   CLIP_DEFAULT_PRECIS,
					   DEFAULT_QUALITY,
					   DEFAULT_PITCH,
					   "Arial");

	myFont2.CreateFont(14,
					   8,
					   0,
					   0,
					   FW_BOLD,
					   0,
					   0,
					   0,
					   DEFAULT_CHARSET,
					   OUT_DEVICE_PRECIS,
					   CLIP_DEFAULT_PRECIS,
					   DEFAULT_QUALITY,
					   DEFAULT_PITCH,
					   "Arial");


	m_motion.SetFont(&myFont1,TRUE);
	m_rotation.SetFont(&myFont2,TRUE);
	m_translation.SetFont(&myFont2,TRUE);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVIMEKDlg::OnOpenFrames() 
{
	char szFilter[255] = "All Files (*.*)|*.*|*.(bmp)|*.bmp|(*.jpg)|*.jpg";
	char szTitle[50] = "Select frame files";

	CFileDialog dlg (TRUE,
					 NULL, 
					 NULL,
					 OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
					 szFilter);
	
	dlg.m_ofn.lpstrTitle = szTitle;


	if (dlg.DoModal () == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		CString pathName = dlg.GetNextPathName(pos);
		m_vimek.SetFrame(pathName, 1);
		m_vimek.SetRGBFrame(pathName,1);
		
		pathName = dlg.GetNextPathName(pos);
		m_vimek.SetFrame(pathName, 2);
		m_vimek.SetRGBFrame(pathName,2);

	}
	m_vimek.ShowRGBFrame(&m_frame1, 1);
	m_vimek.ShowRGBFrame(&m_frame2, 2);
}


void CVIMEKDlg::OnExtractFeatures()
{
	

	CString strRot, strTrnsl;

	// Find the feature points and calculate the corresponding motion vectors
	bool tempMotion;
	tempMotion = m_vimek.TrackFeatures(5);

	m_vimek.DisplayFeatures(&m_frame1);
}

void CVIMEKDlg::OnTrackFeatures()
{
}

HBRUSH CVIMEKDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_STATIC) {

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MOTION)
			pDC->SetTextColor(RGB(255,0,0));

	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
