// MovingCamSimulationDlg.cpp : implementation file
//
#include "stdafx.h"
#include "MovingCamSimulation.h"
#include "MovingCamSimulationDlg.h"
#include "MotionPathEntranceDlg.h"
#include "PlanePictEntranceDlg.h"
#include ".\movingcamsimulationdlg.h"
#include "figurewindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovingCamSimulationDlg dialog

CMovingCamSimulationDlg::CMovingCamSimulationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMovingCamSimulationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMovingCamSimulationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_maskBmp = NULL;
	m_roiSelect = FALSE;
}

void CMovingCamSimulationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMovingCamSimulationDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, m_instructionsEdit);
	DDX_Control(pDX, IDC_STATIC_P, m_pictFrame);
	DDX_Control(pDX, IDC_EDIT3, m_roiStartEdit);
	DDX_Control(pDX, IDC_EDIT4, m_roiEndEdit);
	DDX_Control(pDX, IDC_EDIT2, m_roiDimsEdit);
}

BEGIN_MESSAGE_MAP(CMovingCamSimulationDlg, CDialog)
	//{{AFX_MSG_MAP(CMovingCamSimulationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON6, OnOpenPlanarImage)
	ON_BN_CLICKED(IDC_BUTTON3, OnEnterCameraMotion)
	ON_BN_CLICKED(IDC_BUTTON2, OnEnterImageMask)
	ON_BN_CLICKED(IDC_BUTTON4, OnSelectCameraRegion)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON5, OnSimulate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovingCamSimulationDlg message handlers

BOOL CMovingCamSimulationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_instructionsEdit.SetWindowText("INSTRUCTIONS\r\n1. Load Planar Image\r\n2. Load Mask Image\r\n3. Enter plane parameters for\r\neach region of mask image\r\n4.Enter Camera Motion Parameters\r\n5.Select the area in the viewfinder\r\n6.Simulate");
	m_viewFinderCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMovingCamSimulationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMovingCamSimulationDlg::OnPaint() 
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

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect r;
		m_pictFrame.GetClientRect(&r);

		CDialog::OnPaint();
		m_planeBmp.Display(m_pictFrame.m_hWnd, Rect(0,0, r.Width(), r.Height()));
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMovingCamSimulationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMovingCamSimulationDlg::OnButton1() 
{
	CFigureWindow w;
	w.DoModal();
}

void CMovingCamSimulationDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	delete m_maskBmp;
	m_maskBmp = NULL;
	CDialog::OnClose();
}

void CMovingCamSimulationDlg::OnSimulate()
{
	TRegionMap::iterator	it = m_regionMap.begin();
	C3DMotion	motion;
	CImge	imageU(m_imageInView.height, m_imageInView.width);
	CImge	imageV(m_imageInView.height, m_imageInView.width);
	POSITION pos;

	pos = m_camMotionPathPoints.GetHeadPosition();

	while (pos != NULL)
	{
		motion = m_camMotionPathPoints.GetNext(pos);
		while ( it != m_regionMap.end() )
		{
			if (!it->second.m_isIMO)
			{
				it->second.m_motionOfPlane = it->second.m_planeOrMotion.m_plane.Motion(motion);
			}
			it++;
		}

		for (int i = 0; i < m_imageInView.height; i++)
		{
			for (int j = 0; j < m_imageInView.width; j++)
			{
				CPlanarPictureSegment &segment = m_regionMap[m_imageInView(i,j)];
				if (segment.m_isIMO)
				{
					imageU(i, j) = segment.m_planeOrMotion.m_motion.m_u;
					imageV(i, j) = segment.m_planeOrMotion.m_motion.m_v;
				}
				else
				{
					C2DMotion m = segment.m_motionOfPlane.UVofPlane(j, i, m_imageInView.width, m_imageInView.height);
					imageU(i, j) = m.m_u;
					imageV(i, j) = m.m_v;
				}
			}
		}
	}

	imageU.SaveAsText("D:\\imageU.txt");
	imageV.SaveAsText("D:\\imageV.txt");
}

void CMovingCamSimulationDlg::OnOpenPlanarImage() 
{
	char szTitle[]="Select the planar world IMAGE file";
	TCHAR FileNameList[16384]= {0};
	TCHAR szFilters[]=_T("BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif|PNG Files (*.png)|*.png|TIFF Files (*.tif)|*.tif|All Files (*.*)|*.*||)");
	CFileDialog fileDlg(TRUE,_T("bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_EXPLORER ,szFilters);
	fileDlg.m_ofn.lpstrTitle=szTitle;
	fileDlg.m_ofn.lpstrFile=FileNameList;
	fileDlg.m_ofn.nMaxFile=16384;

	if (fileDlg.DoModal()==IDOK)
	{
		m_planeBmp.InitializeBmp(fileDlg.GetPathName());
		RedrawWindow();
	}
}

void CMovingCamSimulationDlg::OnEnterCameraMotion() 
{
	CMotionPathEntranceDlg dlg;
	dlg.RegisterPathPointsList(&m_camMotionPathPoints);
	dlg.DoModal();
}

void CMovingCamSimulationDlg::OnEnterImageMask() 
{
	CPlanePictEntranceDlg d(m_regionMap, m_maskBmp);
	d.DoModal();	
}

void CMovingCamSimulationDlg::OnSelectCameraRegion() 
{
	if (m_roiSelect)
	{
		m_roiSelect = FALSE;
		ReleaseCapture();
	}
	else
	{
		m_roiSelect = TRUE;
		SetCapture();
		SetCursor(m_viewFinderCursor);
	}
}

void CMovingCamSimulationDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( m_roiSelect )
	{
		CRect r;

		RedrawWindow();
		m_ROIRect.TopLeft()=point; 
		m_ROIRect.BottomRight()=point;

		m_pictFrame.GetClientRect(r);

		m_imageInViewStart.x = (point.x-7)*m_planeBmp.m_pBmp->GetWidth()/r.Width();
		m_imageInViewStart.y = (point.y-7)*m_planeBmp.m_pBmp->GetHeight()/r.Height();

		CString s;
		s.Format("%d; %d",m_imageInViewStart.x, m_imageInViewStart.y);
		m_roiStartEdit.SetWindowText(s);
		m_roiStartEdit.UpdateWindow();
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CMovingCamSimulationDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_roiSelect )
	{
		CRect r;

		m_ROIRect.BottomRight() = point ;	
		CDC* pDC = GetDC();
		CBrush dragRectBr;
		dragRectBr.CreateSolidBrush( RGB( 255, 0, 0 ) );
		pDC->FrameRect( m_ROIRect, &dragRectBr );
		ReleaseDC(pDC);
		m_roiSelect = FALSE;
		ReleaseCapture();
		m_pictFrame.GetClientRect(r);

		m_imageInViewEnd.x = (point.x-7)*m_planeBmp.m_pBmp->GetWidth()/r.Width();
		m_imageInViewEnd.y = (point.y-7)*m_planeBmp.m_pBmp->GetHeight()/r.Height();
		
		CString s;
		s.Format("%d; %d",m_imageInViewEnd.x, m_imageInViewEnd.y);
		m_roiEndEdit.SetWindowText(s);
		m_roiEndEdit.UpdateWindow();
		
		CGdiplusWrapper wr;
		wr.m_pBmp = m_maskBmp;
		CImge im(wr);
		m_imageInView = im.Crop(m_imageInViewStart.y, m_imageInViewStart.x, m_imageInViewEnd.y, m_imageInViewEnd.x);
		m_imageInView.SaveAsType(JPG, "C:\\crop.jpg");
		wr.m_pBmp = NULL;
	}	
	CDialog::OnLButtonUp(nFlags, point);
}

void CMovingCamSimulationDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( m_roiSelect )
	{
		if ( nFlags & MK_LBUTTON )
		{
			CRect oldDummy;
			CRect r;
			CDC* pDC = GetDC();
			CSize sz(2,2);
			CBrush dragRectBr;
			dragRectBr.CreateSolidBrush( RGB( 0, 255, 0 ) );
			oldDummy = m_ROIRect;
			oldDummy.NormalizeRect();
			m_ROIRect.BottomRight() = point;
			m_ROIRect.NormalizeRect();
			pDC->DrawDragRect( oldDummy, sz, m_ROIRect, sz, &dragRectBr );
			ReleaseDC(pDC);

			m_pictFrame.GetClientRect(r);
			m_imageInViewEnd.x = (point.x-7)*m_planeBmp.m_pBmp->GetWidth()/r.Width();
			m_imageInViewEnd.y = (point.y-7)*m_planeBmp.m_pBmp->GetHeight()/r.Height();
			
			CString s;
			s.Format("%d; %d",m_imageInViewEnd.x, m_imageInViewEnd.y);
			m_roiEndEdit.SetWindowText(s);
			m_roiEndEdit.UpdateWindow();

			s.Format("%d; %d",m_imageInViewEnd.x-m_imageInViewStart.x+1, m_imageInViewEnd.y-m_imageInViewStart.y+1);
			m_roiDimsEdit.SetWindowText(s);
			m_roiDimsEdit.UpdateWindow();
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}
