// Feature.cpp: implementation of the CFeature class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VIMEK.h"
#include "Color.h"
#include "Feature.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CColor::CColor()
{
	vote=0;	
	mean_x=0;
	mean_y=0;
	var_x=0;
	var_y=0;
	std_x=0;
	std_y=0;
	colorRatio=0;
	colorMean_R=0;
	colorMean_G=0;
	colorMean_B=0;
	colorVar_R=0;
	colorVar_G=0;
	colorVar_B=0;
	colorStd_R=0;
	colorStd_G=0;
	colorStd_B=0;
	colorValue=0;
}

CColor::~CColor()
{

}

void CColor::FindStatistics(CImge &IMM_R, CImge &IMM_G, CImge &IMM_B)
{
	int i=0;
	int n1,n2;
		// calculate the mean of the dominant color for each sb-band
		for (i=0; i<vote; i++)
		{
			n2=myPoint.GetAt(i).x;
			n1=myPoint.GetAt(i).y;
			colorMean_R=colorMean_R+IMM_R(n1,n2);
			colorMean_G=colorMean_G+IMM_G(n1,n2);
			colorMean_B=colorMean_B+IMM_B(n1,n2);
		}

		colorMean_R= colorMean_R / vote;
		colorMean_G= colorMean_G / vote;
		colorMean_B= colorMean_B / vote;

		// calculate the variance of the dominant color for each sb-band
		for (i=0; i<vote; i++)
		{
			n2=myPoint.GetAt(i).x;
			n1=myPoint.GetAt(i).y;
			colorVar_R=colorVar_R+pow((IMM_R(n1,n2)-colorMean_R),2);
			colorVar_G=colorVar_G+pow((IMM_G(n1,n2)-colorMean_G),2);
			colorVar_B=colorVar_B+pow((IMM_B(n1,n2)-colorMean_B),2);
		}
		
		colorVar_R= colorVar_R / vote;
		colorVar_G= colorVar_G / vote;
		colorVar_B= colorVar_B / vote;
		
		// convert variance to standadrd deviation
		colorStd_R = sqrt(colorVar_R);
		colorStd_G = sqrt(colorVar_G);
		colorStd_B = sqrt(colorVar_B);

		// calculate the mean position of dominant color
		for (i=0; i<vote; i++)
		{
			n2=myPoint.GetAt(i).x;
			n1=myPoint.GetAt(i).y;
			mean_x = mean_x + n2;
			mean_y = mean_y + n1;
		}
		
		mean_x = mean_x / vote;
		mean_y = mean_y / vote;

		// calculate the variance position of dominant color
		for (i=0; i<vote; i++)
		{
			n2=myPoint.GetAt(i).x;
			n1=myPoint.GetAt(i).y;
			var_x = var_x + pow((n2-mean_x),2);
			var_y = var_y + pow((n2-mean_y),2);
		}

		var_x = var_x / vote;
		var_y = var_y / vote;

		std_x = sqrt(var_x);
		std_y = sqrt(var_y);

		// find the color ratio (the ratio of dominat colored pixels to tatl number of pixels)
		colorRatio = 100 * vote / double((IMM_R.width*IMM_R.height)); 
}