// VIMEKLayer.h: interface for the CVIMEK class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_)
#define AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "imge.h"

class CVIMEK  
{
public:
	bool	TrackFeatures(int window);
	void	DisplayFeatures(CWnd* wnd);
	void	RANSAC();
	double Rx,Ry,Rz,Tx,Ty,Tz;
	CImge	m_frame1;
	CImge	m_frame2;
	CImge	Diff,I_x,I_y,temp_diff,Grad_curr,Vx,Vy,v,b,n,d,g,g_v,g_v_tam,g_v_dec;
	CVIMEK();
	virtual ~CVIMEK();
	
private:

	
protected:
	CPoint NormalizePointLocations(CPoint p, CSize s, const CRect &r);
};

#endif // !defined(AFX_VIMEKLAYER_H__E4FEF210_0578_4709_A1DC_CFDC39CAD1C8__INCLUDED_)
