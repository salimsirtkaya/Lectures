/*
/* If you intend to use the source code provided, please contact tubabayik@yahoo.com
/* The materials are provided on an "as is" basis without warranties of any kind. 
*/
#ifndef IMGE_H_
#define IMGE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <limits>
#include <memory.h>
#include <math.h>					
#define P(x) ((x) > 0 ? (x)*(x)*(x) : 0)
#include "GdiplusWrapper.h"
#include <time.h>
#define randSign ( rand()<(RAND_MAX/2) )?1:-1

enum BUFFER_FROM {VIDEO, IMAGE};
enum INTERPOLATION_METHOD {NEAREST, BILINEAR, BICUBIC};

class ImList;

class CImge
{
public:
	CImge ThresholdedMaskedDifference( CImge &subtractor, CRect mask, double thr );
	CImge MaskedDifference( CImge &subtractor, CRect mask );
	CImge MaskedDifference( const CImge &subtractor, short left_h, short left_w, short right_h, short right_w);
	double CosineBetween( CImge &prod );
	double DotProduct( const CImge &prod );
	double RecogRate();
	double**		Image;
	short	width;
	short	height;
	
	CImge (short h=0, short w=0);
	CImge (CGdiplusWrapper &source);
	CImge (const CImge&);
	~CImge ();
	
	double* operator [] (short index);
	CImge operator = (const CImge& rhs);
	double& operator () (short i, short j);
	
	void BGRBuff2GrayIm(unsigned char* buf, short h, short w, BUFFER_FROM buffer_from);
	void GrayIm2BGRBuff(unsigned char* &buf);
	void ListValues(CDC* pDC, CRect* listArea);
	void Vectorize(CImge &vectIm);
	void Resize(short i, short j);
	CImge Crop(short left_h, short left_w, short right_h, short right_w);
	CImge Transpose ();
	double SqrdNorm();
	CImge Interpolate(short h_new,short w_new,INTERPOLATION_METHOD intMethod=BICUBIC);
	int Eigen(double* val, CImge &Vec);
	CImge Inverse();
	double Mean();
	double Variance();
	double NonIntPxlValueBilinear(double x, double y);
	void MinMax(double& mn, double& mx);
	void Extrapolate(int vert,int horiz);
	CImge PyramidSeed();
	void SetAllPxlsTo(double value);
	void HistogramStretch();
	void Split(CImge &Im1, CImge &Im2);
	BOOL ImShow(HWND hWnd, Rect dispArea);
	BOOL SaveAsType(int Type, CString filename);
	CImge* Project(CImge &OnTo, int AxisNum);
	void PCAProject(CImge &Psi, CImge &eigenImages, int PCcount);

	double DiffAt1Pxl(double x, double y, char direction);//uygun þekilde extrapolate edilmiþ image üzerinde çalýþýr ancak..
	CImge SpatialGradientMtr (double Px, double Py, int Wx, int Wy);

	int findNNtuba(ImList &representatives, double &distance, CImge* &nearestV);
	void findNNinclass_outclass( ImList &representatives, int imClass, \
						   CImge* &NNinClass, CImge* &NNoutClass, double &distanceIn, double &distanceOut);
	int findNN(ImList &representatives, double &distance, int &loc, CImge* &nearestV);

private:
	//Auxiliary functions for bicubic interpoplation
	double WeightFunc(float x)
	{
		return ((P(x+2)-4*P(x+1)+6*P(x)-4*P(x-1))/6);
	}
	//Auxiliary functions for eigenvector calculations
	void tri_diagonalize(double *d,double *e, CImge &A,  double tol);
	int calc_eigenstructure(double *d, double *e, CImge &A, double macheps);
public:
	void SaveAsText(CString filename);
	int Arts(int partHeight, int partWidth, ImList& imList);
};

/************************************************************************************************/
/* Auxiliary functions for CImge																*/
/************************************************************************************************/

short crout( CImge& A, CImge& index, double& sign, double tol);
short luSolve( CImge& A, CImge& index,CImge& b, double tol);
void Vector2Image(CImge &Im, double* vect, short h, short w);

CImge operator+ (const CImge& ,const CImge& Adder);
CImge operator+ (const CImge& Translated,double Translator);
CImge operator- (const CImge&Subtracted ,const CImge& Subtractor);
CImge operator- (const CImge& Translated,double Translator);
CImge operator* (const CImge&Multiplier ,double Multiplicant);
CImge operator* (const CImge&Multiplier ,const CImge& Multiplicant);




/************************************************************************************************/

void NonReducedEigenImages( int h, int w, double* val, CImge &reducedEigenIms, CImge &Atransposed, CImge &eigenImages);
void OLVQ1Method(ImList &trainers, ImList &CodeBook, int classCount, int CVperClass, int maxIter, double alpha);
void PCAforICA(ImList &PCAtrainSet, CImge &Psi, CImge &reducedEigenIms, CImge &Atransposed, double* &val);
void SwapPtrs(void* ptr1, void* ptr2);
void Vector2Image(CImge &Im, double* vect, short h, short w);


#endif