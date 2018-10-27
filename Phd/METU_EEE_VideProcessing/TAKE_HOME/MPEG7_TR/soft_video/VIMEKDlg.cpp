/*EE706 PROJECT*/
/*Salim SIRTKAYA*/


#include "stdafx.h"
#include "VIMEK.h"
#include "VIMEKDlg.h"
#include ".\vimekdlg.h"
#include "DirectShowWrapper.h"
#include <afx.h>
#include <stdlib.h>
#include <malloc.h>
#include "Feature.h"
#include "Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVIMEKApp theApp;
int block_size = 8;

CString fName;
/////////////////////////////////////////////////////////////////////////////
// CVIMEKDlg dialog

CVIMEKDlg::CVIMEKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVIMEKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVIMEKDlg)
	m_startframe = 16;
	m_endframe = 18;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVIMEKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVIMEKDlg)
	DDX_Control(pDX, IDC_LIST_txtOut, m_txtOut);
	DDX_Control(pDX, IDC_COMBO_blockSize, m_blockSize);
	DDX_Control(pDX, IDC_STATIC_FR2, m_FR2);
	DDX_Control(pDX, IDC_STATIC_FR1, m_FR1);
	DDX_Control(pDX, IDC_GROUPBOX_VIDEO, m_grpVideo);
	DDX_Control(pDX, IDC_STATIC_MOTION, m_motion);
	DDX_Text(pDX, IDC_EDIT_startframe, m_startframe);
	DDX_Text(pDX, IDC_EDIT_endframe, m_endframe);
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
	ON_CBN_SELENDOK(IDC_COMBO_blockSize, OnSelendokCOMBOblockSize)
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
		//m_vimek.DisplayFeatures(&m_frame1);
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

	theApp.m_bThreadAlive = FALSE;
//	m_rotation.SetFont(&myFont2,TRUE);
//	m_translation.SetFont(&myFont2,TRUE);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

UINT CVIMEKDlg::MyThreadFunction(LPVOID pParam)
{
	CVIMEKDlg* pObject = (CVIMEKDlg*) pParam;
	if (pObject==NULL)
		return 1;

	pObject->Process();

	theApp.m_bThreadAlive = FALSE;
	return 0;
}

void CVIMEKDlg::OnBeginProcessThread() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	myThread = AfxBeginThread(MyThreadFunction,this);
	if (myThread!=NULL)
		theApp.m_bThreadAlive = TRUE;
}

void CVIMEKDlg::Process()
{
	//UpdateData(false);
	//Grab the consecutive two frames of the video and write them into m_frame1 and m_frame2

	REFERENCE_TIME currentFrame = m_startframe;
	m_motion.SetWindowText("");
	long boyut;
	int n1=0;
	int n2=0;
	int r=0;
	int i_frame=0;
	bool tempMotion;
	long w,h;

	CPoint mPoint, pPoint, meanPoint;

	double temp_meanVx = 0, temp_meanVy = 0, temp_varVx = 0, temp_varVy = 0, temp_stdVx = 0, temp_stdVy = 0, temp_motion=0;
	long int temp_mean_x = 0, temp_mean_y = 0, temp_var_x = 0, temp_var_y = 0, temp_std_x = 0, temp_std_y = 0;
	long int temp_spatialDist = 0;

	unsigned char red_value, green_value, blue_value;
	unsigned char red_quant, green_quant, blue_quant;
	unsigned char dominant_color;
	unsigned char noDominantColor=5;
	unsigned char noDC=0;
	unsigned char DColors[10];

	unsigned long int max=0;
	unsigned int QL_red=4, QL_green=4, QL_blue=4, q_number_r, q_number_g, q_number_b, color_quant = 0;

	q_number_r = 256 / QL_red;
	q_number_g = 256 / QL_green;
	q_number_b = 256 / QL_blue;

	CColor	ColorSpace[64];

	unsigned char * k = new unsigned char[3 * 102000 * sizeof(unsigned char)] ;

	CString strRot, strTrnsl, strFR1, strFR2;

	FILE  *dosya_mpeg7;
///////////////////////////////////////////////////////////////////////////////////////////////////
	// Zamana baðlý dosya adý oluþturma
	CTime time;
	time = time.GetCurrentTime();
	CString strFile,strFile_mpeg7;

	//fName.Find('\');
	strFile.Format("%02d%02d%02d_%02d%02d",time.GetDay(),time.GetMonth(),time.GetYear(),time.GetHour(),time.GetMinute());
	strFile_mpeg7 = "D:\\MPEG7_salim_"+strFile+".txt" ;

	/////////////////////////////////////	
	dosya_mpeg7 = fopen(strFile_mpeg7,"wt");

	// write the header to the text file
	fprintf(dosya_mpeg7,"EE706-VIDEO PROCESSING - Spring 2005 \n");
	fprintf(dosya_mpeg7,"Final TakeHome MPEG7 Feature Extractor\n");
	fprintf(dosya_mpeg7,"Salim SIRTKAYA - 1124346 \n");

	fprintf(dosya_mpeg7,"Color Space: RGB\n");
	fprintf(dosya_mpeg7,"Quantization Level RED  :  %d\n", 4);
	fprintf(dosya_mpeg7,"Quantization Level GREEN:  %d\n", 4);
	fprintf(dosya_mpeg7,"Quantization Level BLUE :  %d\n", 4);
	fprintf(dosya_mpeg7,"Motion Activity Quantization Levels : 5 - LL,L,LH,H,HH\n\n");

	// write the header to the list box
	m_txtOut.InsertString(0,"EE706 - MPEG7 Feature Extractor");
	m_txtOut.InsertString(1,"DEMO Program - Salim SIRTKAYA");
	m_txtOut.InsertString(2,"Color Space: RGB");
	m_txtOut.InsertString(3,"Quantization Level RED : 4");
	m_txtOut.InsertString(4,"Quantization Level GREEN : 4");
	m_txtOut.InsertString(5,"Quantization Level BLUE : 4");
	m_txtOut.InsertString(6,"Quantization Levels for Motion Activity: 5 - LL,L,LH,H,HH");

////////////////////////////////////////////////////////////////////////////////////////////////////
	m_txtOut.InsertString(7,"Process started");
	
	m_wrapper.VideoSeekTo(currentFrame);
	m_wrapper.ShowWindow(true);

	//Grab the first paused image just to initialize the matrices we need
	m_wrapper.GrabCurrentFrame(k,boyut,w,h);
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
	
	
	while (i_frame<(m_endframe-m_startframe))
	{
		//new HRESULT IM;
		i_frame++;
		
		m_wrapper.VideoSeekTo(currentFrame);
		m_wrapper.ShowWindow(true);
		
		//Grab the first paused image
		m_wrapper.GrabCurrentFrame(k,boyut,w,h);
		
		m_vimek.m_frame1.Buff2GrayIm(k,h,w,VIDEO);
		m_vimek.m_frame1_R.Buff2ColorIm(k,h,w,VIDEO,'R');
		m_vimek.m_frame1_G.Buff2ColorIm(k,h,w,VIDEO,'G');
		m_vimek.m_frame1_B.Buff2ColorIm(k,h,w,VIDEO,'B');

		//// Find out the dominant colors ////

		for (n1=0;n1<h;n1++)
		{
			for (n2=0;n2<w;n2++)
			{
				red_value = unsigned char(m_vimek.m_frame1_R(n1,n2));
				green_value = unsigned char(m_vimek.m_frame1_G(n1,n2));
				blue_value = unsigned char(m_vimek.m_frame1_B(n1,n2));

				red_quant = red_value / 64;
				green_quant = green_value / 64;
				blue_quant = blue_value / 64;

				// form a 6 bit 
				green_quant= green_quant << 2;
				red_quant= red_quant << 4;

				color_quant = red_quant | green_quant | blue_quant;

				mPoint.x = n2;
				mPoint.y = n1;
				ColorSpace[color_quant].myPoint.SetSize(ColorSpace[color_quant].vote+1);

				ColorSpace[color_quant].myPoint.SetAt(ColorSpace[color_quant].vote, mPoint);
			
				ColorSpace[color_quant].vote++;															
			}
		}
	
		// find the ColorSpace that has the dominant colors
		for (int ITER=0;ITER<noDominantColor;ITER++)
		{
			for (int i=0; i<64; i++)
			{
				if (ColorSpace[i].vote > max)
				{
					max = ColorSpace[i].vote;
					dominant_color = i;
				}
			}
			
			ColorSpace[dominant_color].colorValue = dominant_color;
			ColorSpace[dominant_color].FindStatistics(m_vimek.m_frame1_R, m_vimek.m_frame1_G, m_vimek.m_frame1_B);

			if (ColorSpace[dominant_color].colorRatio > 4.0)
			{
				noDC++;
				max=0;
				ColorSpace[dominant_color].vote=0;
				DColors[ITER] = dominant_color;
			}

			else
				ITER = noDominantColor+1; 
		}
		// WRITE these values to atext file
		fprintf(dosya_mpeg7,"Dominant Color Parameters for Frame %d\n",currentFrame);
		fprintf(dosya_mpeg7,"DC\t");
		fprintf(dosya_mpeg7,"Perc.\t");
		fprintf(dosya_mpeg7,"Mean-R\t");
		fprintf(dosya_mpeg7,"Std-Red\t");
		fprintf(dosya_mpeg7,"Mean-G\t");
		fprintf(dosya_mpeg7,"Std-G\t");
		fprintf(dosya_mpeg7,"Mean-B\t");
		fprintf(dosya_mpeg7,"Std-B\t");
		fprintf(dosya_mpeg7,"Mean-x\t");
		fprintf(dosya_mpeg7,"Std-x\t");
		fprintf(dosya_mpeg7,"Mean-y\t");
		fprintf(dosya_mpeg7,"Std-y\n");

		for (int i=0;i<noDC;i++)
		{
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].colorValue);
			fprintf(dosya_mpeg7,"%.1f\t",ColorSpace[DColors[i]].colorRatio);
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].colorMean_R);
			fprintf(dosya_mpeg7,"%.1f\t",ColorSpace[DColors[i]].colorStd_R);
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].colorMean_G);
			fprintf(dosya_mpeg7,"%.1f\t",ColorSpace[DColors[i]].colorStd_G);
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].colorMean_G);
			fprintf(dosya_mpeg7,"%.1f\t",ColorSpace[DColors[i]].colorStd_G);
			
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].mean_x);
			fprintf(dosya_mpeg7,"%.1f\t",ColorSpace[DColors[i]].std_x);
			fprintf(dosya_mpeg7,"%d\t",ColorSpace[DColors[i]].mean_y);
			fprintf(dosya_mpeg7,"%.1f\n",ColorSpace[DColors[i]].std_y);
		}
		fprintf(dosya_mpeg7,"\n");

		// empty ColorSpaces
		for(i=0;i<64;i++)
		{
			max=0;
			noDC=0;
			ColorSpace[i].vote=0;
			ColorSpace[i].colorMean_R=0;
			ColorSpace[i].colorMean_G=0;
			ColorSpace[i].colorMean_B=0;
			ColorSpace[i].colorRatio=0;
			ColorSpace[i].colorStd_B=0;
			ColorSpace[i].colorStd_G=0;
			ColorSpace[i].colorStd_R=0;
			ColorSpace[i].colorValue=0;
			ColorSpace[i].colorVar_B=0;
			ColorSpace[i].colorVar_G=0;
			ColorSpace[i].colorVar_R=0;
			ColorSpace[i].mean_x=0;
			ColorSpace[i].mean_y=0;
			ColorSpace[i].std_x=0;
			ColorSpace[i].std_y=0;
			ColorSpace[i].var_x=0;
			ColorSpace[i].var_y=0;
		}

		//write the number of processed frame to the static box m_FR1
		strFR1.Format("%d", currentFrame);
		m_FR1.SetWindowText(strFR1);
		
		currentFrame=currentFrame+1;

		//write the number of processed frame to the static box m_FR1
		strFR2.Format("%d", currentFrame);
		m_FR2.SetWindowText(strFR2);
		
		m_wrapper.VideoSeekTo(currentFrame);
		m_wrapper.ShowWindow(true);
		
		//Grab the second paused image
		m_wrapper.GrabCurrentFrame(k,boyut,w,h);
		
		m_vimek.m_frame2.Buff2GrayIm(k,h,w,VIDEO);
		m_vimek.m_frame2_R.Buff2ColorIm(k,h,w,VIDEO,'R');
		m_vimek.m_frame2_G.Buff2ColorIm(k,h,w,VIDEO,'G');
		m_vimek.m_frame2_B.Buff2ColorIm(k,h,w,VIDEO,'B');
				
		// Find the feature points and calculate the corresponding motion vectors

		tempMotion = m_vimek.TrackFeatures(5,block_size);
		// write the motion activity parameters to the text file
		fprintf(dosya_mpeg7,"Motion Activity Parameters for Frame Pairs  %d\t",currentFrame-1);
		fprintf(dosya_mpeg7,"%d\n",currentFrame);
		fprintf(dosya_mpeg7,"MeanVx\t");
		fprintf(dosya_mpeg7,"StdVx\t");
		fprintf(dosya_mpeg7,"MeanVy\t");
		fprintf(dosya_mpeg7,"StdVy\t");
		fprintf(dosya_mpeg7,"SpDst\t");
		fprintf(dosya_mpeg7,"meanX\t");
		fprintf(dosya_mpeg7,"stdX\t");
		fprintf(dosya_mpeg7,"meanY\t");
		fprintf(dosya_mpeg7,"stdY\n");

		fprintf(dosya_mpeg7,"%.1f\t",m_vimek.meanVx);
		fprintf(dosya_mpeg7,"%.1f\t",m_vimek.stdVx);
		fprintf(dosya_mpeg7,"%.1f\t",m_vimek.meanVy);
		fprintf(dosya_mpeg7,"%.1f\t",m_vimek.stdVy);
		fprintf(dosya_mpeg7,"%d\t",m_vimek.spatialDist);
		fprintf(dosya_mpeg7,"%d\t",m_vimek.mean_x);
		fprintf(dosya_mpeg7,"%d\t",m_vimek.std_x);
		fprintf(dosya_mpeg7,"%d\t",m_vimek.mean_y);
		fprintf(dosya_mpeg7,"%d\n\n",m_vimek.std_y);

		temp_meanVx = temp_meanVx + m_vimek.meanVx;
		temp_stdVx = temp_stdVx + m_vimek.stdVx;
		temp_meanVy = temp_meanVy + m_vimek.meanVy;
		temp_stdVy = temp_stdVy + m_vimek.stdVy;
		temp_spatialDist = temp_spatialDist + m_vimek.spatialDist;
		temp_mean_x = temp_mean_x + m_vimek.mean_x;
		temp_mean_y = temp_mean_y + m_vimek.mean_y;
		temp_std_x = temp_std_x + m_vimek.std_x;
		temp_std_y = temp_std_y + m_vimek.std_y;
		
		// re-initialize the motion variables
		m_vimek.meanVx = 0;
		m_vimek.varVx = 0;
		m_vimek.stdVx = 0;
		m_vimek.meanVy = 0;
		m_vimek.varVy = 0;
		m_vimek.stdVy = 0;
		m_vimek.spatialDist = 0;
		m_vimek.mean_x = 0;
		m_vimek.var_x = 0;
		m_vimek.std_x = 0;
		m_vimek.mean_y = 0;
		m_vimek.var_y = 0;
		m_vimek.std_y = 0;
		
	}///end of while
	
	temp_meanVx = temp_meanVx / double(m_endframe-m_startframe);
	temp_stdVx = temp_stdVx / double(m_endframe-m_startframe);
	temp_meanVy = temp_meanVy / double(m_endframe-m_startframe);
	temp_stdVy = temp_stdVy / double(m_endframe-m_startframe);
	temp_spatialDist = temp_spatialDist / (m_endframe-m_startframe);
	temp_mean_x = temp_mean_x / (m_endframe-m_startframe);
	temp_mean_y = temp_mean_y / (m_endframe-m_startframe);
	temp_std_x = temp_std_x / (m_endframe-m_startframe);
	temp_std_y = temp_std_y / (m_endframe-m_startframe);

	// write the average motion activity parameters of the shot to text
	fprintf(dosya_mpeg7,"************************************************\n\n");
	fprintf(dosya_mpeg7,"Average Motion Activity Parameters of the Shot\n");
	fprintf(dosya_mpeg7,"MeanVx\t");
	fprintf(dosya_mpeg7,"StdVx\t");
	fprintf(dosya_mpeg7,"MeanVy\t");
	fprintf(dosya_mpeg7,"StdVy\t");
	fprintf(dosya_mpeg7,"SpDst\t");
	fprintf(dosya_mpeg7,"meanX\t");
	fprintf(dosya_mpeg7,"stdX\t");
	fprintf(dosya_mpeg7,"meanY\t");
	fprintf(dosya_mpeg7,"stdY\n");
	
	fprintf(dosya_mpeg7,"%.1f\t",temp_meanVx);
	fprintf(dosya_mpeg7,"%.1f\t",temp_stdVx);
	fprintf(dosya_mpeg7,"%.1f\t",temp_meanVy);
	fprintf(dosya_mpeg7,"%.1f\t",temp_stdVy);
	fprintf(dosya_mpeg7,"%d\t",temp_spatialDist);
	fprintf(dosya_mpeg7,"%d\t",temp_mean_x);
	fprintf(dosya_mpeg7,"%d\t",temp_std_x);
	fprintf(dosya_mpeg7,"%d\t",temp_mean_y);
	fprintf(dosya_mpeg7,"%d\n",temp_std_y);

	temp_motion = sqrt(pow(temp_stdVx,2)+pow(temp_stdVy,2));

	// write the motion activity level of the shot (LL-L-LH-H-HH)
	if (0<temp_motion && temp_motion<1.5)
		fprintf(dosya_mpeg7,"AVERAGE MOTION ACTIVITY: LL  -  %.1f",temp_motion);
	else if (1.5<temp_motion && temp_motion<3.0) 
		fprintf(dosya_mpeg7,"AVERAGE MOTION ACTIVITY: L  -  %.1f",temp_motion);
	else if (3.0<temp_motion && temp_motion<4.5)
		fprintf(dosya_mpeg7,"AVERAGE MOTION ACTIVITY: LH  -  %.1f",temp_motion);
	else if (4.5<temp_motion && temp_motion<6.0)
		fprintf(dosya_mpeg7,"AVERAGE MOTION ACTIVITY: H  -  %.1f",temp_motion);
	else if (6.0<temp_motion)
		fprintf(dosya_mpeg7,"AVERAGE MOTION ACTIVITY: HH  -  %.1f",temp_motion);

	fclose(dosya_mpeg7);
	m_motion.SetWindowText("FINISHED");
	delete []k;

	m_txtOut.InsertString(8,"Process finished");
	m_txtOut.InsertString(9,"The text file is saved to the following folder as:");
	m_txtOut.InsertString(10,"D:\\MPEG7_salim_"+strFile+".txt");
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
		fName = sTemp;
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
	char szFilter[255] = "Mpeg files |*.*|*.mpeg|*.m1v|*.mpg|";
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



void CVIMEKDlg::OnSelendokCOMBOblockSize() 
{
	// TODO: Add your control notification handler code here
	int index = m_blockSize.GetCurSel();

	switch (index)
	{
	case 0:
		block_size = 4;
		break;
	case 1:
		block_size = 8;
		break;
	case 2:
		block_size = 16;
		break;

	}
	
}
