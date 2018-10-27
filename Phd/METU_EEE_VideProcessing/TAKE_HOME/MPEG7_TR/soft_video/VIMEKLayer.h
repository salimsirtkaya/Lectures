// VIMEKLayer.h: interface for the CVIMEK class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_)
#define AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "imge.h"
#include "Feature.h"

class CVIMEK  
{
public:
	bool	TrackFeatures(int window, int block_size);
	CImge	m_frame1;
	CImge	m_frame2;
	CImge	Diff,I_x,I_y,temp_diff,Grad_curr,Vx,Vy,v,b,n,d,g,g_v,g_v_tam,g_v_dec;
	CImge	m_frame1_R,m_frame1_B,m_frame1_G, m_frame2_R,m_frame2_B,m_frame2_G;
	
	double meanVx, meanVy, varVx, varVy, stdVx, stdVy;
	long int mean_x, mean_y, var_x, var_y, std_x, std_y;
	long int spatialDist;
	CPoint spatialLoc;
	
	void	DisplayFeatures(CWnd* wnd);	
	void SetRGBFrame(CString fileName, int frameNo);
	void ShowRGBFrame(CWnd* wnd, int frameNo);
	void RGBImsToBuff(unsigned char* & buf, int frameNo);

	CArray<CBlock,CBlock> myBlock;

	CVIMEK();
	virtual ~CVIMEK();
	
private:

	
protected:
	CPoint NormalizePointLocations(CPoint p, CSize s, const CRect &r);
};

#endif // !defined(AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_)
