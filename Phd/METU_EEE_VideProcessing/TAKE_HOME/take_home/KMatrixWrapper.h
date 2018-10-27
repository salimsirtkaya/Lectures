/**************************************************************
KMatrixWrapper.h

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KMatrixWrapper.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KMatrixWrapper.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KMatrixWrapper.h
or the use or other dealings in KMatrixWrapper.h

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/MatrixWrapper"
**************************************************************/

// KMatrixWrapper.h: interface for the KMatrixWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXWRAPPER_H__4F1C2D96_F78E_4857_AB20_677E87A46444__INCLUDED_)
#define AFX_MATRIXWRAPPER_H__4F1C2D96_F78E_4857_AB20_677E87A46444__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "matlab.hpp"

typedef unsigned int uint;

class KMatrixWrapper  
{
public:

	// Constructors
	KMatrixWrapper();
	KMatrixWrapper(int r, int c);
	KMatrixWrapper(int r, int c, double *arr);

	KMatrixWrapper(double arr);
	KMatrixWrapper(CString str);

//	virtual ~KMatrixWrapper();

	
	KMatrixWrapper operator- () const;
	KMatrixWrapper operator+ () const;

	void operator = (const double m);
	void operator = (const char* m);
	void operator = (const KMatrixWrapper& m);
	void operator = (const mwNumericSubArray& m);

	void operator+= (const KMatrixWrapper& m);
	void operator+= (const double m);
	void operator-= (const KMatrixWrapper& m);
	void operator-= (const double m);
	void operator*= (const KMatrixWrapper& m);
	void operator*= (const double m);
	void operator/= (const KMatrixWrapper& m);
	void operator/= (const double m);

	mwNumericSubArray operator() (const int m);
	mwNumericSubArray operator() (const int m, const int n);

	double* column(int m); // returns the column m
	double* row   (int n); // returns the row n
public:
	double at(int r, int c);
	mwArray mat;
};

#endif // !defined(AFX_KMATRIXWRAPPER_H__4F1C2D96_F78E_4857_AB20_677E87A46444__INCLUDED_)

KMatrixWrapper operator! (const KMatrixWrapper& m);
KMatrixWrapper operator~ (const KMatrixWrapper& m);

KMatrixWrapper operator+ (const KMatrixWrapper& m, const KMatrixWrapper& n);
KMatrixWrapper operator+ (const KMatrixWrapper& m, const double& n);
KMatrixWrapper operator+ (const double& m, const KMatrixWrapper& n);

KMatrixWrapper operator- (const KMatrixWrapper& m, const KMatrixWrapper& n);
KMatrixWrapper operator- (const KMatrixWrapper& m, const double& n);
KMatrixWrapper operator- (const double& m, const KMatrixWrapper& n);

KMatrixWrapper operator* (const KMatrixWrapper& m, const KMatrixWrapper& n);
KMatrixWrapper operator* (const KMatrixWrapper& m, const double& n);
KMatrixWrapper operator* (const double& m, const KMatrixWrapper& n);

KMatrixWrapper operator/ (const KMatrixWrapper& m, const KMatrixWrapper& n);
KMatrixWrapper operator/ (const KMatrixWrapper& m, const double& n);
KMatrixWrapper operator/ (const double& m, const KMatrixWrapper& n);

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////Utility Functions//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void MatrixSize(KMatrixWrapper tempMat, int &r, int &c);
void LoadMatrix(CString str, KMatrixWrapper &tempMat);
void SaveMatrix(CString str, KMatrixWrapper  tempMat );
double MatrixData( KMatrixWrapper tempMat );
double* MatrixDataPointer( KMatrixWrapper tempMat );

KMatrixWrapper inv(KMatrixWrapper a);
KMatrixWrapper det(const KMatrixWrapper &X);
KMatrixWrapper conv2(KMatrixWrapper a, KMatrixWrapper b, KMatrixWrapper opt );
KMatrixWrapper svd(const KMatrixWrapper &x);
KMatrixWrapper svd(KMatrixWrapper &s, KMatrixWrapper &v, const KMatrixWrapper &x);
KMatrixWrapper transpose(KMatrixWrapper a);
KMatrixWrapper ctranspose(KMatrixWrapper a);
KMatrixWrapper times(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper mtimes(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper mldivide(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper mrdivide(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper rdivide(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper ldivide(KMatrixWrapper a, KMatrixWrapper b);

KMatrixWrapper lrdivide(const KMatrixWrapper &a, int ar, const KMatrixWrapper &b, int br);
KMatrixWrapper lcdivide(const KMatrixWrapper &a, int ac, const KMatrixWrapper &b, int bc);
KMatrixWrapper rrdivide(const KMatrixWrapper &a, int ar, const KMatrixWrapper &b, int br);
KMatrixWrapper rcdivide(const KMatrixWrapper &a, int ac, const KMatrixWrapper &b, int bc);

KMatrixWrapper plus(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper minus(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper power(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper mpower(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper lt(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper gt(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper le(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper ge(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper eq(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper neq(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper and_func(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper or_func(KMatrixWrapper a, KMatrixWrapper b);
KMatrixWrapper not_func(KMatrixWrapper a);
KMatrixWrapper sqrt(KMatrixWrapper a);
KMatrixWrapper mean(const KMatrixWrapper &a );
KMatrixWrapper mean(const KMatrixWrapper &a, const KMatrixWrapper &dim );
KMatrixWrapper median(const KMatrixWrapper &a );
KMatrixWrapper median(const KMatrixWrapper &a, const KMatrixWrapper &dim );
KMatrixWrapper variance(const KMatrixWrapper &a );
KMatrixWrapper reshape(const KMatrixWrapper &a, int r, int c);
KMatrixWrapper norm(const KMatrixWrapper &a);
KMatrixWrapper norm(const KMatrixWrapper &a, const KMatrixWrapper &p);
KMatrixWrapper randu(int n=1);
KMatrixWrapper randu(int m, int n);
KMatrixWrapper min(const KMatrixWrapper &a);
KMatrixWrapper min(const KMatrixWrapper &a, const KMatrixWrapper &b);
KMatrixWrapper min(const KMatrixWrapper &a, const KMatrixWrapper &b, const KMatrixWrapper &dim);
KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a);
KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b);
KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b
				  , const KMatrixWrapper &dim);
KMatrixWrapper max(const KMatrixWrapper &a);
KMatrixWrapper max(const KMatrixWrapper &a, const KMatrixWrapper &b);
KMatrixWrapper max(const KMatrixWrapper &a, const KMatrixWrapper &b, const KMatrixWrapper &dim);
KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a);
KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b);
KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b
				  , const KMatrixWrapper &dim);
KMatrixWrapper identity();
KMatrixWrapper identity(const int &n);
KMatrixWrapper identity(const int &m, const int &n);

KMatrixWrapper eig(KMatrixWrapper *D, const KMatrixWrapper &A);
KMatrixWrapper eig(KMatrixWrapper &A, const KMatrixWrapper &B);
KMatrixWrapper eig(KMatrixWrapper *D, KMatrixWrapper &A, const KMatrixWrapper &B);
KMatrixWrapper eig(KMatrixWrapper *D, KMatrixWrapper &A, const KMatrixWrapper &B
				   , const KMatrixWrapper &flag);
KMatrixWrapper sum(const KMatrixWrapper &A );
KMatrixWrapper sum(const KMatrixWrapper &A,const KMatrixWrapper &dim );
KMatrixWrapper cross(const KMatrixWrapper &U,const KMatrixWrapper &V );
KMatrixWrapper cross(const KMatrixWrapper &U,const KMatrixWrapper &V,const KMatrixWrapper &dim );
KMatrixWrapper crossMatrix(const KMatrixWrapper &A );
KMatrixWrapper Ones (const int&rn, const int &cn);
KMatrixWrapper Zeros(const int&rn, const int &cn);
KMatrixWrapper rotation(const double &theta, int sz);
KMatrixWrapper roots( const KMatrixWrapper &c );
KMatrixWrapper signum( const KMatrixWrapper    &A );
KMatrixWrapper signum( const mwNumericSubArray &A );
KMatrixWrapper sqrt( const KMatrixWrapper &A );

KMatrixWrapper nullVector(const KMatrixWrapper &A, uint opt);
void		   nullVector(const KMatrixWrapper &A, KMatrixWrapper &left, KMatrixWrapper &right);

KMatrixWrapper mag(const KMatrixWrapper &A);
KMatrixWrapper diag(const KMatrixWrapper &A);

void SetMatrixData(KMatrixWrapper &A, int r, int c, const double &d );
void subMatrix( KMatrixWrapper &a, uint str, uint enr, uint stc, uint enc, const KMatrixWrapper &b);
void subMatrix( KMatrixWrapper &a, uint astr, uint aenr, uint astc, uint aenc, 
		  const KMatrixWrapper &b, uint bstr, uint benr, uint bstc, uint benc );

KMatrixWrapper columnOp(const KMatrixWrapper& m, const KMatrixWrapper& n, char oper);
int matcmp(const KMatrixWrapper &A, const KMatrixWrapper &B );

void qr(const KMatrixWrapper &in1, KMatrixWrapper &out1, KMatrixWrapper &out2);

// Special Functions
KMatrixWrapper MES(const KMatrixWrapper &A);
KMatrixWrapper DLT(const KMatrixWrapper &A, double* &ret);



KMatrixWrapper DecreaseRank(const KMatrixWrapper &A, const int rank);


// FILE I/O
void printToFile(const KMatrixWrapper &fid, const KMatrixWrapper &format, const KMatrixWrapper &data);
void printToFile(const KMatrixWrapper &fid, const char* format, const char* data);
void printToFile(const KMatrixWrapper &fid, const char* format, const KMatrixWrapper &data);

KMatrixWrapper openFile(const KMatrixWrapper &filename, const KMatrixWrapper &permission);
KMatrixWrapper openFile(KMatrixWrapper *message, const KMatrixWrapper &filename,
						const KMatrixWrapper &permission, const KMatrixWrapper &format);
KMatrixWrapper openFile(const KMatrixWrapper &all);
KMatrixWrapper openFile(KMatrixWrapper *permission, KMatrixWrapper *format,
						const KMatrixWrapper &fid);
KMatrixWrapper openFile(const KMatrixWrapper &filename, const KMatrixWrapper &permission,
						const KMatrixWrapper &format);
KMatrixWrapper closeFile(const KMatrixWrapper &fid);