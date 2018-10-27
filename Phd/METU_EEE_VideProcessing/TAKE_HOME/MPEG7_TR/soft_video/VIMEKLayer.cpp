// VIMEKLayer.cpp: implementation of the CVIMEK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VIMEK.h"
//#include "VIMEKDlg.h"
#include "VIMEKLayer.h"
#include "DirectShowWrapper.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//CVIMEKDlg m_dlgVIMEK;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVIMEK::CVIMEK()
{
	meanVx = 0;
	meanVy = 0;
	varVx = 0;
	varVy = 0;
	stdVx = 0;
	stdVy = 0;
	mean_x = 0;
	mean_y = 0;
	var_x = 0;
	var_y = 0;
	std_x = 0;
	std_y = 0;
	spatialDist = 0;
}

CVIMEK::~CVIMEK()
{
	
}


bool CVIMEK::TrackFeatures(int window, int block_size)
{
	// Extract the features using the gradient matrix
	double variance;
	double mean;

	bool motion = false; // 0 --> no motion ; 1 --> motion
	double motion_threshold = 5;
	
	int h = m_frame1.height;
	int w = m_frame1.width;

	int block_no_x = int(w/block_size);
	int block_no_y = int(h/block_size);
	int block_no = block_no_x * block_no_y;

	myBlock.SetSize(block_no);

	CBlock blk;
	
	//CImge Diff(h,w);
	Diff.Resize(h,w);
	

	Diff = m_frame1 - m_frame2;
	
	Diff = Diff.Abs();
	
	// analyze the variance of the difference images in order to decide on the motion/no-motion cases
	
	variance = Diff.Variance();
	mean = Diff.Mean();
	
	if ((mean+0.05*variance) > motion_threshold)
	{
		motion = true;
		//m_dlgVIMEK.SetStaticMotion(motion);
		
	}
	else 
	{
		motion = false;
		//m_dlgVIMEK.SetStaticMotion(motion);
		
	}
	
	if(motion)
	{
		
		I_x = m_frame1.Diff_x();
		I_y = m_frame1.Diff_y();
			
		// Track the features using Kanade Lucas Fature Tracker
		
		Grad_curr.Resize(2,2);
		
		CImge Vx(h,w);
		CImge Vy(h,w);

		Vx.SetAllPxlsTo(0);
		Vy.SetAllPxlsTo(0);

		v.SetAllPxlsTo(0);
		b.SetAllPxlsTo(0);
		n.SetAllPxlsTo(0);
		d.SetAllPxlsTo(0);
		g.SetAllPxlsTo(0);
		g_v.SetAllPxlsTo(0);
		g_v_dec.SetAllPxlsTo(0);
		g_v_tam.SetAllPxlsTo(0);
		temp_diff.SetAllPxlsTo(0);
		
		int K=4;
		int gt=0;
		int i;
		int j;
		int n1=0;
		int n2=0;
		int i_0;
		int j_0;
		int i_eski=-5;
		int j_eski=-5;
		int ft=0;
		int ind=0;
		int win_x=0;
		int win_y=0;
		int g_det=0;
		int h_l=0;
		int w_l=0;
		int pyr_level=2;
		int level=0;
		int nBlk=0;
		
		//////////////////////////////////////////////////////////
		CImge* Pyr_I=new CImge[pyr_level];
		CImge* Pyr_I_x=new CImge[pyr_level];
		CImge* Pyr_I_y=new CImge[pyr_level];
		CImge* Pyr_J=new CImge[pyr_level];
		CImge* Pyr_J_temp=new CImge[pyr_level];
		
		Pyr_I[0]=m_frame1;
		Pyr_J[0]=m_frame2;
		Pyr_J_temp[0]=m_frame2;
		
		for(i=1;i<pyr_level;i++)
		{
			Pyr_I[i]=Pyr_I[i-1].PyramidSeed();
			Pyr_J[i]=Pyr_J[i-1].PyramidSeed();
		}
		
		for (i=pyr_level-1; i>=1;i--)
		{
			//Construct the x and y derivatives of the image for each hierarchical level
			Pyr_I_x[i]=Pyr_I[i].Diff_x();
			Pyr_I_y[i]=Pyr_I[i].Diff_y();
		}
		
		// First level derivative is equal to the original difference image
		Pyr_I_x[0]=I_x ;
		Pyr_I_y[0]=I_y;
		
		////////////////////////////////////////////////////////////////////////						
		// Iterative Optical Flow Estimation using Kanade Lucas Tracker Algorithm
		for (i_0=block_size;i_0<h-block_size;i_0=i_0+block_size)
		{			
			for(j_0=block_size;j_0<w-block_size;j_0=j_0+block_size)
			{
				b.SetAllPxlsTo(0);
				v.SetAllPxlsTo(0);
				n.SetAllPxlsTo(0);
				d.SetAllPxlsTo(0);
				g_v.SetAllPxlsTo(0);
				g.SetAllPxlsTo(0);
				level=pyr_level;
				
				if (i_0>=window+1 && i_0<=h-window-1 && j_0>=window+1 && j_0<=w-window-1)
				{
					///////////////Outer iteration loop (Pyramidal tracking)/////////////
					while(level>0)
					{
						b.SetAllPxlsTo(0);
						v.SetAllPxlsTo(0);
						n.SetAllPxlsTo(0);
						d.SetAllPxlsTo(0);
						
						i=i_0/(pow(2,level-1));
						j=j_0/(pow(2,level-1));
						h_l=h/(pow(2,level-1));
						w_l=w/(pow(2,level-1));								
						
						if (i>=window+window && i<=h_l-window-window && j>=window+window && j<=w_l-window-window)
						{					
							//Calculate the inverse G matrix for this feature point
							Grad_curr.SetAllPxlsTo(0);
							
							for (win_x=i-window;win_x<=i+window;win_x++)
							{
								for(win_y=j-window;win_y<=j+window;win_y++)
								{
									Grad_curr(0,0)+=pow(Pyr_I_x[level-1](win_x,win_y),2);
									Grad_curr(0,1)+=Pyr_I_x[level-1](win_x,win_y)*Pyr_I_y[level-1](win_x,win_y);
									Grad_curr(1,1)+=pow(Pyr_I_y[level-1](win_x,win_y),2);
								}
							}
							
							Grad_curr(1,0)=Grad_curr(0,1);
							
							g_det=Grad_curr(0,0)*Grad_curr(1,1)-Grad_curr(1,0)*Grad_curr(0,1);
							
							if (abs(g_det)>0.1)
							{					
								Grad_curr=Grad_curr.Inverse();
								
								///////////////Inner iteration loop (Iterative KLT)/////////////
								for (int k=0;k<K;k++)
								{				
									b.SetAllPxlsTo(0);
									n.SetAllPxlsTo(0);									
									g_v=g+v;
									
									g_v_tam(0,0)=floor(g_v(0,0));
									g_v_dec(0,0)=g_v(0,0)-g_v_tam(0,0);
									
									g_v_tam(1,0)=floor(g_v(1,0));
									g_v_dec(1,0)=g_v(1,0)-g_v_tam(1,0);
									
									if ( abs(g_v(0,0))>=window || abs(g_v(1,0))>=window )
									{
										g_v.SetAllPxlsTo(window-2);
										break;
									}
									
									for (win_x=i-window;win_x<=i+window;win_x++)
									{
										for(win_y=j-window;win_y<=j+window;win_y++)
										{							
											temp_diff(win_x,win_y)=Pyr_I[level-1](win_x,win_y)-((1-g_v_dec(0,0))*(1-g_v_dec(1,0))*\
												Pyr_J[level-1](win_x+g_v_tam(0,0),win_y+g_v_tam(1,0))+\
												(1-g_v_dec(0,0))*g_v_dec(1,0)*Pyr_J[level-1](win_x+g_v_tam(0,0),win_y+1+g_v_tam(1,0))+\
												(1-g_v_dec(1,0))*g_v_dec(0,0)*Pyr_J[level-1](win_x+1+g_v_tam(0,0),win_y+g_v_tam(1,0))+\
												g_v_dec(0,0)*g_v_dec(1,0)*Pyr_J[level-1](win_x+1+g_v_tam(0,0),win_y+1+g_v_tam(1,0)));
										}
									}	
									
									for (win_x=i-window;win_x<=i+window;win_x++)
									{
										for(win_y=j-window;win_y<=j+window;win_y++)
										{
											b(0,0)+=temp_diff(win_x,win_y)*Pyr_I_x[level-1](win_x,win_y);
											b(1,0)+=temp_diff(win_x,win_y)*Pyr_I_y[level-1](win_x,win_y);
										}
									}
									
									n(0,0)=Grad_curr(0,0)*b(0,0)+Grad_curr(1,0)*b(1,0);
									n(1,0)=Grad_curr(0,1)*b(0,0)+Grad_curr(1,1)*b(1,0);
									
									
									if ( abs(n(0,0))>=7 || abs(n(1,0))>=7 )
									{
										v.SetAllPxlsTo(0);
										n.SetAllPxlsTo(0);
										break;
									}
									
									v=v+n;
									
									if ( abs(v(0,0))>=7 || abs(v(1,0))>=7 )
										break;
									
									if (v(0,0)<=0.1 && v(1,0)<=0.1 && v(0,0)>=-0.1 && v(1,0)>=-0.1)
										break;
								}//end of inner iteration loop
								
								d=v;
								
								g=(g+d);
								if (level-1!=0)
									g=g*2;
								
								level--;
							}//end of if (g_det>0.5)
							else
							{
								level--;
							}
						}//end of if (i<...)
						else
							level--;
						
					}//end of while (level>0)				
				
					///////////// The result //////////				
					Vy(i_0,j_0)=g(0,0);
					Vx(i_0,j_0)=g(1,0);	
		
					///////////////////////////////////						
				}//end of if (i>=5 && i<=h-5 && j>=5 && j<=w-5) 
					
				blk.block_no = nBlk;
				blk.vx = Vx(i_0,j_0);
				blk.vy = Vy(i_0,j_0);
				blk.x = j_0 - block_size/2;
				blk.y = i_0 - block_size/2;

				meanVx = meanVx + blk.vx;
				meanVy = meanVy + blk.vy;

				myBlock.SetAt(nBlk,blk);
				nBlk++;	
			}
		}//end of for 

		// calculate the mean of the motion vectors
		meanVx = meanVx / block_no;
		meanVy = meanVy / block_no;
		short signX;
		if(meanVx < 0)
			signX = -1;
		else
			signX = 1;
		short signY;
		if(meanVy < 0)
			signY = -1;
		else
			signY = 1;

		// calculate the variance and std of motion vectors and spatial distribution of motion
		for (i=0; i<block_no; i++)
		{
			varVx = varVx + pow((myBlock.GetAt(i).vx - meanVx),2);
			varVy = varVy + pow((myBlock.GetAt(i).vy - meanVy),2);
			if ((fabs(myBlock.GetAt(i).vx) < fabs(meanVx)) && (fabs(myBlock.GetAt(i).vy) < fabs(meanVy)))
				spatialDist++;
		}

		varVx = varVx / block_no;
		varVy = varVy / block_no;

		stdVx = sqrt(varVx);
		stdVy = sqrt(varVy);

		// find the spatial location of the global motion
		int nSp=0;
		for (i=0; i<block_no; i++)
		{
			if ((signX*myBlock.GetAt(i).vx > fabs(meanVx)+0.2*stdVx) || (signY*myBlock.GetAt(i).vy > fabs(meanVy)+0.2*stdVy))
			{
				mean_x = mean_x + myBlock.GetAt(i).x;			
				mean_y = mean_y + myBlock.GetAt(i).y;
				nSp++;
			}
		}

		mean_x = mean_x / nSp;
		mean_y = mean_y / nSp;

		// calculate the variance of the spatial location
		for (i=0; i<block_no; i++)
		{		
			if ((signX*myBlock.GetAt(i).vx > fabs(meanVx)+0.2*stdVx) || (signY*myBlock.GetAt(i).vy > fabs(meanVy)+0.2*stdVy))
			{		
				var_x = var_x + pow((myBlock.GetAt(i).x - mean_x),2);
				var_y = var_y + pow((myBlock.GetAt(i).y - mean_y),2);
			}
		}

		var_x = var_x / nSp;
		var_y = var_y / nSp;
		std_x = sqrt(var_x);
		std_y = sqrt(var_y);

		/********************************************************/
		/**************writing to a text file********************/
		/********************************************************/
		
		/*FILE *dosya1;
		dosya1=fopen("D:\\KLT_V_x.txt","wt");
		
		for (n1=10;n1<h-10;n1++)
		{
			for (n2=10;n2<w-10;n2++)
			{
				fprintf(dosya1,"%f\t",Vx(n1,n2));	
			}	
		}
		fclose(dosya1);
		
		FILE *dosya2;
		dosya2=fopen("D:\\KLT_V_y.txt","wt");
		
		for (n1=10;n1<h-10;n1++)
		{
			for (n2=10;n2<w-10;n2++)
			{
				fprintf(dosya2,"%f\t",Vy(n1,n2));	
			}	
		}
		fclose(dosya2);*/

		delete []Pyr_I;
		delete []Pyr_I_x;
		delete []Pyr_I_y;
		delete []Pyr_J;
		delete []Pyr_J_temp;
	}

	return motion;
}

void CVIMEK::DisplayFeatures(CWnd* wnd)
{
	CRect	r;
	CSize	s;
	CDC* pDC = wnd->GetDC();
	CBrush	rb(0xff);

	wnd->GetWindowRect(r);
	s.cx = m_frame1.height;
	s.cy = m_frame2.width;
	pDC->SelectObject(&rb);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(0xff);

	for (int i = 0; i < m_frame1.Feature_no; i ++)
	{
		CPoint fp, dp;

		fp.x = m_frame1.mFeature[i].x;
		fp.y = m_frame1.mFeature[i].y;
		dp = NormalizePointLocations(fp, s, r);

		pDC->TextOut(dp.y, dp.x, "O");
	}

	pDC->SelectStockObject(BLACK_BRUSH);
	rb.DeleteObject();
	wnd->ReleaseDC(pDC);
}


CPoint CVIMEK::NormalizePointLocations(CPoint p, CSize s, const CRect &r)
{
	CPoint normalPt;

	normalPt.x = (p.x)*r.Height()/s.cx - 4;
	normalPt.y = (p.y)*r.Width()/s.cy - 5;

	return normalPt;
}

void CVIMEK:: SetRGBFrame (CString fileName, int frameNo)
{
	CImge &frame_B = (frameNo == 1) ? m_frame1_B : m_frame2_B;
	CImge &frame_G = (frameNo == 1) ? m_frame1_G : m_frame2_G;
	CImge &frame_R = (frameNo == 1) ? m_frame1_R : m_frame2_R;
	
	m_frame1_B.GetColorFromFromFile(fileName, 'B');
	m_frame1_G.GetColorFromFromFile(fileName, 'G');
	m_frame1_R.GetColorFromFromFile(fileName, 'R');
	m_frame2_B.GetColorFromFromFile(fileName, 'B');
	m_frame2_G.GetColorFromFromFile(fileName, 'G');
	m_frame2_R.GetColorFromFromFile(fileName, 'R');
}

void CVIMEK::RGBImsToBuff(unsigned char* & buf, int frameNo) /* buffer'i CGdiplusWrapper nesnesine yüklemek
													istedigimizi varsayarak... (stride=4k) */
{
	CImge &frame_B = (frameNo == 1) ? m_frame1_B : m_frame2_B;
	CImge &frame_G = (frameNo == 1) ? m_frame1_G : m_frame2_G;
	CImge &frame_R = (frameNo == 1) ? m_frame1_R : m_frame2_R;
	int padding=frame_R.width%4;//4-((width*3)%4);
	int i,j,size;
	size=frame_R.height*(3*frame_R.width+padding);
	buf=new unsigned char[size];
	int b_index,h_index;

	for (i=frame_R.height-1;i>=0;i--)
	{
		h_index=i*(3*frame_R.width+padding);
		for (j=frame_R.width-1;j>=0;j--)
		{
			b_index=h_index+j*3;
			buf[b_index+2]=frame_R.Image[i][j];
			buf[b_index+1]=frame_G.Image[i][j];
			buf[b_index]=frame_B.Image[i][j];
		}
	}
}
void CVIMEK::ShowRGBFrame(CWnd* wnd, int frameNo)
{
	BYTE* buf;
	CImge &frame = (frameNo == 1) ? m_frame1 : m_frame2;
	CRect r;
	wnd->GetClientRect(r);
	RGBImsToBuff(buf, frameNo);
	CGdiplusWrapper wrap;
	wrap.LoadPixelData(buf, Point(frame.width, frame.height));
	wrap.Display(wnd->m_hWnd, Rect(0,  0,r.Width(), r.Height()));
	delete [] buf;
}
