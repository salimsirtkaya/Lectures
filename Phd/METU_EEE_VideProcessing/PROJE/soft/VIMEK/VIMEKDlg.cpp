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
#include "DirectShowWrapper.h"
#include <afx.h>
#include <stdlib.h>
#include <malloc.h>
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
	DDX_Control(pDX, IDC_STATIC_FR2, m_FR2);
	DDX_Control(pDX, IDC_STATIC_FR1, m_FR1);
	DDX_Control(pDX, IDC_GROUPBOX_VIDEO, m_grpVideo);
	DDX_Control(pDX, IDC_GROUPBOX_IMAGE, m_grpImage);
	DDX_Control(pDX, IDC_STATIC_Tz, m_Tz);
	DDX_Control(pDX, IDC_STATIC_Ty, m_Ty);
	DDX_Control(pDX, IDC_STATIC_Tx, m_Tx);
	DDX_Control(pDX, IDC_STATIC_Rz, m_Rz);
	DDX_Control(pDX, IDC_STATIC_Ry, m_Ry);
	DDX_Control(pDX, IDC_STATIC_Rx, m_Rx);
	DDX_Control(pDX, IDC_STATIC_TRANSLATION, m_translation);
	DDX_Control(pDX, IDC_STATIC_ROTATION, m_rotation);
	DDX_Control(pDX, IDC_STATIC_MOTION, m_motion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVIMEKDlg, CDialog)
	//{{AFX_MSG_MAP(CVIMEKDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnTrackFeatures)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON4, OnOpenVideo)
	ON_BN_CLICKED(IDC_BUTTON1, OnBeginProcessThread)
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

/*void CVIMEKDlg::OnOpenFrames() 
{
	char szFilter[255] = "All Files (*.*)|*.*|*.(bmp)|*.bmp|(*.jpg)|*.jpg";
	char szTitle[50] = "Select frame files";

	CFileDialog dlg (TRUE,
					 NULL, 
					 NULL,
					 OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
					 szFilter);
	
	dlg.m_ofn.lpstrTitle = szTitle;
	dlg.m_ofn.lpstrInitialDir = "D:\\DERS\\PHD\\VIDEO\\PROJE\\VIMEK_testdata\\images_translation_MOV10381";


	if (dlg.DoModal () == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();

		m_vimek.SetFrame(dlg.GetNextPathName(pos), 1);
		m_vimek.SetFrame(dlg.GetNextPathName(pos), 2);
	}

	m_vimek.ShowFrame(&m_frame1, 1);
	m_vimek.ShowFrame(&m_frame2, 2);
}*/

UINT CVIMEKDlg::MyThreadFunction(LPVOID pParam)
{
	CVIMEKDlg* pObject = (CVIMEKDlg*) pParam;
	if (pObject==NULL)
		return 1;

	pObject->OnProcess();
	return 0;
}

void CVIMEKDlg::OnBeginProcessThread() 
{
	// TODO: Add your control notification handler code here
	myThread = AfxBeginThread(MyThreadFunction,this);
}

void CVIMEKDlg::OnProcess()
{
	//Grab the consecutive two frames of the video and write them into m_frame1 and m_frame2
	REFERENCE_TIME currentFrame = 1;

	int n1=0;
	int n2=0;
	int r=0;
	int i_frame=0;
	bool tempMotion;
	long w,h;

	unsigned char * k;
			
	CString strRot, strTrnsl, strFR1, strFR2;

	FILE  *dosya_rot, *dosya_trl;

	// Zamana baðlý dosya adý oluþturma
	CTime time;
	time = time.GetCurrentTime();
	CString strFile,strFile_rot, strFile_trl;
	strFile.Format("%02d%02d%02d_%02d%02d%02d",time.GetDay(),time.GetMonth(),time.GetYear(),time.GetHour(),time.GetMinute(),time.GetSecond());
	strFile_rot = "C:\\ROT_"+strFile+".txt" ;
//	strFile_rot = "D:\\ROT_"+strFile+".txt" ;

	/////////////////////////////////////	
	dosya_rot = fopen(strFile_rot,"wt");

	strFile_trl = "C:\\TRL_"+strFile+".txt" ;
//	strFile_trl = "D:\\TRL_"+strFile+".txt" ;

	dosya_trl = fopen(strFile_trl, "wt");

	m_wrapper.VideoSeekTo(currentFrame);
	m_wrapper.ShowWindow(true);

	//Grab the first paused image
	m_wrapper.GrabCurrentFrame(k,w,h);
	m_vimek.m_frame2.Buff2GrayIm(k,h,w,VIDEO);

	h = m_vimek.m_frame2.height;
	w = m_vimek.m_frame2.width;

	m_vimek.b.Resize(2,1);
	m_vimek.d.Resize(2,1);
	m_vimek.Diff.Resize(h,w);
	m_vimek.g.Resize(2,1);
	m_vimek.g_v.Resize(2,1);
	m_vimek.g_v_dec.Resize(2,1);
	m_vimek.g_v_tam.Resize(2,1);
	m_vimek.Grad_curr.Resize(2,2);
	m_vimek.I_x.Resize(h-2,w-2);
	m_vimek.I_y.Resize(h-2,w-2);
	m_vimek.n.Resize(2,1);
	m_vimek.temp_diff.Resize(h,w);
	m_vimek.v.Resize(2,1);
	m_vimek.Vx.Resize(h,w);
	m_vimek.Vy.Resize(h,w);
	
	
	while (i_frame<575)
	{
		//new HRESULT IM;
		i_frame++;
		
		m_wrapper.VideoSeekTo(currentFrame);
	//	m_wrapper.VideoRun(currentFrame);
	//	m_wrapper.VideoPause(currentFrame);
		m_wrapper.ShowWindow(true);
		
		//Grab the first paused image
		m_wrapper.GrabCurrentFrame(k,w,h);
		
		m_vimek.m_frame1.Buff2GrayIm(k,h,w,VIDEO);	

		strFR1.Format("%d", currentFrame);
		m_FR1.SetWindowText(strFR1);
		
		currentFrame=currentFrame+2;

		strFR2.Format("%d", currentFrame);
		m_FR2.SetWindowText(strFR2);
		
		m_wrapper.VideoSeekTo(currentFrame);
	//	m_wrapper.VideoRun(currentFrame);
	//	m_wrapper.VideoPause(currentFrame);
		m_wrapper.ShowWindow(true);
		
		//Grab the second paused image
		m_wrapper.GrabCurrentFrame(k,w,h);
		
		m_vimek.m_frame2.Buff2GrayIm(k,h,w,VIDEO);
		
		//currentFrame++;
		
		//////////////////////////////////////////////////////////////////
	
		// Find the feature points and calculate the corresponding motion vectors

		tempMotion = m_vimek.TrackFeatures(5);
		
		m_vimek.DisplayFeatures(&m_frame1);
		
		if(tempMotion)
		{
			m_motion.SetWindowText("MOTION");
			
			/*start RANSAC if there is motion*/
			m_vimek.RANSAC();
			
			strRot.Format("%f", m_vimek.Rx);
			m_Rx.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\t",m_vimek.Rx);

			strRot.Format("%f", m_vimek.Ry);
			m_Ry.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\t",m_vimek.Ry);

			strRot.Format("%f", m_vimek.Rz);
			m_Rz.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\n",m_vimek.Rz);
			
			strTrnsl.Format("%f", m_vimek.Tx);
			m_Tx.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\t",m_vimek.Tx);

			strTrnsl.Format("%f", m_vimek.Ty);
			m_Ty.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\t",m_vimek.Ty);

			strTrnsl.Format("%f", m_vimek.Tz);
			m_Tz.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\n",m_vimek.Tz);
		}
		
		else 
		{
			m_motion.SetWindowText("NO MOTION");
			
			strRot.Format("%f", 0);
			m_Rx.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\t",0);

			strRot.Format("%f", 0);
			m_Ry.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\t",0);

			strRot.Format("%f", 0);
			m_Rz.SetWindowText( strRot);
			fprintf(dosya_rot,"%f\n",0);
			
			strTrnsl.Format("%f", 0);
			m_Tx.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\t",0);

			strTrnsl.Format("%f", 0);
			m_Ty.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\t",0);

			strTrnsl.Format("%f", 0);
			m_Tz.SetWindowText( strTrnsl);
			fprintf(dosya_trl,"%f\n",0);
		}
		
	}///end of while

	fclose(dosya_rot);
	fclose(dosya_trl);
	m_motion.SetWindowText("FINISHED");
	delete []k;

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

void CVIMEKDlg::OnOpenVideo() 
{
	// TODO: Add your control notification handler code here
		CString sTemp;

	if (GetVideoFileName(sTemp))
	{
		CWaitCursor cW;

		m_wrapper.DestroyFilterGraph();
		
		if (FAILED(m_wrapper.OpenFile(sTemp)))
		{
			AfxMessageBox("Unable to build filter graph for the video.", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		m_wrapper.SetOwnerAndResize((OAHWND) m_grpVideo.m_hWnd);
		m_wrapper.ShowWindow();
	}
	
}

bool CVIMEKDlg::GetVideoFileName(CString & name) 
{
	char szFilter[255] = "Mpeg files |*.MPG|(*.mpeg)|*.mpeg|(*.mpg)|(*.m1v)|*.m1v|All Files (*.*)|*.*||";
	char szTitle[50] = "Select video file";

	CFileDialog dlg (TRUE,
					 NULL, 
					 NULL,
					 OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, 
					 szFilter);
	
	dlg.m_ofn.lpstrTitle = szTitle;

	if (dlg.DoModal () == IDOK)
	{
		name = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}


