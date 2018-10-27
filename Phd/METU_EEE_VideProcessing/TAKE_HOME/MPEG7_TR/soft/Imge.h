/**************************************************************

Imge.h

--


Tuba M. BAYIK & Salim SIRTKAYA
June, 2004

--

This file ("Imge.h") or a part of it can be used, copied, modified, 
merged, published, and/or have copies distributed for 
academic or research purposes without restriction under the 
following condition:

The above header and this permission notice shall be 
included in all copies or substantial portions of 
Imge.h.

**************************************************************/


#ifndef IMGE_H_
#define IMGE_H_

#include "GdiplusWrapper.h"
#include <memory.h>
#include <afxtempl.h>
#include <limits>
#include <math.h>	//for bicubic interpolation
#include "Feature.h"				
#define P(x) ((x) > 0 ? (x)*(x)*(x) : 0)	//

enum BUFFER_FROM {VIDEO, IMAGE};

class CImge
{
public:
	int Feature_no;

	CFeature mFeature[100]; // maximum number of features allowed

	CArray<int,int> Feature_List;  
	double** Image;
	int	width;
	int	height;
	
	CImge (short h=0, short w=0);
	CImge (CGdiplusWrapper &source);
	CImge (const CImge&);
	~CImge ();
	void FromFile(CString filename);
	
	double* operator [] (short index);
	CImge operator = (const CImge& rhs);
	double& operator () (short i, short j);
	//Conversion operators???
	
	void Buff2GrayIm(unsigned char* buf, short h, short w, BUFFER_FROM buffer_from);
	void GrayIm2Buff(unsigned char* &buf);
	void Resize(short i, short j);
	CImge Crop(short left_x, short left_y, short right_x, short right_y);//***
	CImge Transpose ();
	double Sqrd_Norm();// double olup olmýcagý da apayrý bir sorun....
	CImge Interpolate(short h_new,short w_new);
	int Eigen(double* val, CImge &Vec);
	double Mean();
	double Variance();
	void MinMax(double& mn, double& mx, int& indx, int& indy);
	void Extrapolate(int vert,int horiz);
	CImge PyramidSeed();
	CImge Inverse();
	void SetAllPxlsTo(double value);
	BOOL ImShow(HWND hWnd, Rect dispArea);
	CImge Diff_x();
	CImge Diff_y();
	CImge Abs();
	CImge Product(double a);
	CImge Inv();
	void Feature_inv(CImge &I_x, CImge &I_y, int window);

	void GetColorFromFromFile(CString filename, char ch);
	void Buff2ColorIm(unsigned char* buf, short h, short w, BUFFER_FROM buffer_from, char ch);
	int MapCharToColorCode(char ch);


private:
	//Auxiliary functions for bicubic interpoplation
	double WeightFunc(float x)
	{
		return ((P(x+2)-4*P(x+1)+6*P(x)-4*P(x-1))/6);
	}
	//Auxiliary functions for eigenvector calculations
	void tri_diagonalize(double *d,double *e, CImge &A,  double tol);
	int calc_eigenstructure(double *d, double *e, CImge &A, double macheps);
};

short crout( CImge& A, CImge& index, double& sign, double tol);
short luSolve( CImge& A, CImge& index,CImge& b, double tol);

CImge operator+ (const CImge& ,const CImge& Adder);
CImge operator+ (const CImge& Translated,double Translator);
CImge operator- (const CImge&Subtracted ,const CImge& Subtractor);
CImge operator- (const CImge& Translated,double Translator);
CImge operator* (const CImge&Multiplier ,double Multiplicant);
CImge operator* (const CImge&Multiplier1, const CImge&Multiplier2);

#endif