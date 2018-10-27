// Feature.h: interface for the CFeature class.
//
//////////////////////////////////////////////////////////////////////
#include <afxtempl.h>
#include "Imge.h"

class CColor
{
public:
	CColor();
	virtual ~CColor();

	unsigned long int vote;
	unsigned char colorValue;

	CPoint mPoint, pPoint, meanPoint;
	long int mean_x, mean_y;
	double var_x,var_y;
	double std_x, std_y;
	double colorRatio;
	unsigned long colorMean_R; 
	unsigned long colorMean_G;
	unsigned long colorMean_B;
	double colorVar_R, colorVar_G, colorVar_B;
	double colorStd_R, colorStd_G, colorStd_B;

	void FindStatistics(CImge &IMM_R, CImge &IMM_G, CImge &IMM_B);

	CArray<CPoint, CPoint> myPoint;
};

