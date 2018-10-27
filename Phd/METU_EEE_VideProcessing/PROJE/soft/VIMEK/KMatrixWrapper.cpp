/**************************************************************
KMatrixWrapper.cpp

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KMatrixWrapper.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KMatrixWrapper.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KMatrixWrapper.cpp
or the use or other dealings in KMatrixWrapper.cpp

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/MatrixWrapper"
**************************************************************/

// KMatrixWrapper.cpp: implementation of the KMatrixWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "k3dreconstruction.h"
#include "KMatrixWrapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KMatrixWrapper::KMatrixWrapper()
{
	mat = mwArray();
}

KMatrixWrapper::KMatrixWrapper(int r, int c)
{
	mat(r,c) = 0;
}

KMatrixWrapper::KMatrixWrapper(int r, int c, double *arr)
{
	mat = mwArray(r,c,arr);
}

KMatrixWrapper::KMatrixWrapper(CString str)
{
	mat = mwArray(str);
}

KMatrixWrapper::KMatrixWrapper(double arr)
{
	mat = mwArray();
	mat(1,1) = arr;
}


mwNumericSubArray KMatrixWrapper::operator() (const int m, const int n)
{
	return mat(m,n);
}

mwNumericSubArray KMatrixWrapper::operator() (const int m)
{
	return mat(m);
}

void KMatrixWrapper::operator= (const double m)
{
	this->mat = m;
}

void KMatrixWrapper::operator= (const char* m)
{
	this->mat = mwArray(m);
}

void KMatrixWrapper::operator= (const mwNumericSubArray& m)
{
	this->mat = m;
}

void KMatrixWrapper::operator= (const KMatrixWrapper& m)
{
	this->mat = m.mat;
}

KMatrixWrapper KMatrixWrapper::operator- () const
{
	KMatrixWrapper output; 
	output.mat = -this->mat;
	return output;
}

KMatrixWrapper KMatrixWrapper::operator+ () const
{
	return *this;
}

void KMatrixWrapper::operator+= (const KMatrixWrapper& m)
{
	mat = mat + m.mat;
}

void KMatrixWrapper::operator+= (const double m)
{
	mat = mat + m;
}

void KMatrixWrapper::operator-= (const KMatrixWrapper& m)
{
	mat = mat - m.mat;
}

void KMatrixWrapper::operator-= (const double m)
{
	mat = mat - m;
}

void KMatrixWrapper::operator*= (const KMatrixWrapper& m)
{
	mat = mat * m.mat;
}

void KMatrixWrapper::operator*= (const double m)
{
	mat = mat * m;
}

void KMatrixWrapper::operator/= (const KMatrixWrapper& m)
{
	mat = mat / m.mat;
}

void KMatrixWrapper::operator/= (const double m)
{
	mat = mat / m;
}


double* KMatrixWrapper::column(int m)
{
	int r,c;
	r = mat.Size(1);
	c = mat.Size(2);

	double* tmp = mxGetPr( mat.GetData() );

	double* output = new double[r];

	for(int i=0; i<r; i++)
	{
		output[i]=tmp[(m-1)*r+i];
	}

	return output;
}

double* KMatrixWrapper::row(int n)
{
	int r,c;
	r = mat.Size(1);
	c = mat.Size(2);

	double* tmp = mxGetPr( mat.GetData() );

	double* output = new double[c];

	for(int i=0; i<c; i++)
	{
		output[i]=tmp[(n-1)+i*r];
	}

	return output;
}

double KMatrixWrapper::at(int r, int c)
{
	int w = mat.Size(2);

	double* tmp = mxGetPr( mat.GetData() );

	r--;
	c--;
	return tmp[r*w+c];
}

/////////////////////////////////////////////////////////////////////////////////
//////////////////////NonMember Arithmetic Operators/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
KMatrixWrapper operator! (const KMatrixWrapper& m)
{
	KMatrixWrapper output;
	output.mat = inv( m.mat );
	return output;
}

KMatrixWrapper operator~ (const KMatrixWrapper& m)
{
	KMatrixWrapper output;
	output.mat = transpose( m.mat );
	return output;
}

KMatrixWrapper operator+ (const KMatrixWrapper& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m.mat + n.mat;
	return output;
}

KMatrixWrapper operator+ (const KMatrixWrapper& m, const double& n)
{
	KMatrixWrapper output;
	output.mat = m.mat + n;
	return output;
}

KMatrixWrapper operator+ (const double& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m + n.mat;
	return output;
}

KMatrixWrapper operator- (const KMatrixWrapper& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m.mat - n.mat;
	return output;
}

KMatrixWrapper operator- (const KMatrixWrapper& m, const double& n)
{
	KMatrixWrapper output;
	output.mat = m.mat - n;
	return output;
}

KMatrixWrapper operator- (const double& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m - n.mat;
	return output;
}

KMatrixWrapper operator* (const KMatrixWrapper& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m.mat * n.mat;
	return output;
}

KMatrixWrapper operator* (const KMatrixWrapper& m, const double& n)
{
	KMatrixWrapper output;
	output.mat = m.mat * n;
	return output;
}

KMatrixWrapper operator* (const double& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m * n.mat;
	return output;
}

KMatrixWrapper operator/ (const KMatrixWrapper& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m.mat / n.mat;
	return output;
}

KMatrixWrapper operator/ (const KMatrixWrapper& m, const double& n)
{
	KMatrixWrapper output;
	output.mat = m.mat / n;
	return output;
}

KMatrixWrapper operator/ (const double& m, const KMatrixWrapper& n)
{
	KMatrixWrapper output;
	output.mat = m * inv(n.mat);
	return output;
}

KMatrixWrapper columnOp(const KMatrixWrapper& m, const KMatrixWrapper& n, char oper)
{
	KMatrixWrapper output;
	
	int rm,cm,rn,cn;
	MatrixSize(n,rn,cn);
	MatrixSize(m,rm,cm);

	if( cn == cm && rn == 1 ) 
	{
		for( int i=1; i<=rm; i++ )
		{
			switch(oper)
			{
			case '+':
				output.mat(i,colon(1,cm)) = m.mat(i,colon(1,cm)) + n.mat;
				break;
			case '-':
				output.mat(i,colon(1,cm)) = m.mat(i,colon(1,cm)) - n.mat;
				break;
			}
		}

	}

	return output;
}
/////////////////////////////////////////////////////////////////////////////////
//////////////////////////     FILE I/O    //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void printToFile(const KMatrixWrapper &fid, const KMatrixWrapper &format, const KMatrixWrapper &data)
{
	fprintf(fid.mat, format.mat,data.mat);
}

void printToFile(const KMatrixWrapper &fid, const char* format, const char* data)
{
	fprintf(fid.mat, format, data);
}

void printToFile(const KMatrixWrapper &fid, const char* format, const KMatrixWrapper &data)
{
	fprintf(fid.mat, format, data.mat);
}

KMatrixWrapper openFile(const KMatrixWrapper &filename, const KMatrixWrapper &permission)
{
	KMatrixWrapper output; 
	output.mat = fopen( filename.mat, permission.mat );
	return output;
}

KMatrixWrapper openFile(KMatrixWrapper *message, const KMatrixWrapper &filename,
						const KMatrixWrapper &permission, const KMatrixWrapper &format)
{
	KMatrixWrapper output; 
	output.mat = fopen( &(message->mat), filename.mat, permission.mat, format.mat );
	return output;
}

KMatrixWrapper openFile(const KMatrixWrapper &all)
{
	KMatrixWrapper output; 
	output.mat = fopen( all.mat );
	return output;
}

KMatrixWrapper openFile(KMatrixWrapper *permission, KMatrixWrapper *format,
						const KMatrixWrapper &fid)
{
	KMatrixWrapper output; 
	output.mat = fopen( &(permission->mat), &(format->mat), fid.mat );
	return output;
}

KMatrixWrapper openFile(const KMatrixWrapper &filename, const KMatrixWrapper &permission,
						const KMatrixWrapper &format)
{
	KMatrixWrapper output; 
	output.mat = fopen( filename.mat, permission.mat, format.mat );
	return output;
}

KMatrixWrapper closeFile(const KMatrixWrapper &fid)
{
	KMatrixWrapper output; 
	output.mat = fclose( fid.mat );
	return output;
}

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////Utility Functions//////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void MatrixSize(KMatrixWrapper tempMat, int &r, int &c)
{
	r = tempMat.mat.Size(1); // row number
	c = tempMat.mat.Size(2); // column number
}

void LoadMatrix(CString str, KMatrixWrapper &tempMat)
{
	mwArray fid = fopen(mwArray(str), mwArray("r"));
	tempMat.mat = fscanf( fid, "%f" );
	fclose(fid);
}

void SaveMatrix(CString str, KMatrixWrapper tempMat )
{
	mwArray fid = fopen(mwArray(str),mwArray("w"));

	int r,c;  MatrixSize(tempMat,r,c);

	CString tmp="";
	for( int i=0; i<c; i++ )
	{
		tmp = tmp+(CString)"%3.10e\t";
	}
	tmp = tmp+(CString)"\n";
	mwArray format(tmp);
	fprintf(fid, format, transpose(tempMat.mat));
	fclose(fid);
}

double MatrixData( KMatrixWrapper tempMat )
{
	int r,c; MatrixSize(tempMat,r,c);

	if( r != c && c != 1 ) 
	{
		AfxMessageBox("Misuse of MatrixData Function");
		return 0;
	}
	
	return *mxGetPr( tempMat.mat.GetData() );
}

double* MatrixDataPointer( KMatrixWrapper tempMat )
{
	int r,c; MatrixSize(tempMat,r,c);

	double* tmp = mxGetPr( tempMat.mat.GetData() );
	
	double *tmp2 = new double[r*c];
	memcpy(tmp2,tmp,sizeof(double)*r*c);

	return tmp2;
	//returns in column order
}

KMatrixWrapper inv(KMatrixWrapper a)
{
	KMatrixWrapper out;
	out.mat = inv(a.mat);
	return out;
}

KMatrixWrapper conv2(KMatrixWrapper a, KMatrixWrapper b, KMatrixWrapper opt )
{
	KMatrixWrapper out; 
	out.mat = conv2( a.mat, b.mat, opt.mat );
	return out;
}

KMatrixWrapper svd(const KMatrixWrapper &x)
{
	KMatrixWrapper out; 
	out.mat = svd( x.mat );
	return out;
}

KMatrixWrapper svd(KMatrixWrapper &s, KMatrixWrapper &v, const KMatrixWrapper &x)
{
	KMatrixWrapper out; 
	out.mat = svd( &(s.mat), &(v.mat), x.mat );
	return out;
}

KMatrixWrapper transpose(KMatrixWrapper a)
{
	KMatrixWrapper out;
	out.mat = transpose(a.mat);
	return out;
}

KMatrixWrapper ctranspose(KMatrixWrapper a)
{
	KMatrixWrapper out;
	out.mat = ctranspose(a.mat);
	return out;
}

KMatrixWrapper det(const KMatrixWrapper &X)
{
	KMatrixWrapper output;
	output.mat = det(X.mat);
	return output;
}

KMatrixWrapper times(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = times(a.mat, b.mat);
	return out;
}

KMatrixWrapper mtimes(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = mtimes(a.mat, b.mat);
	return out;
}

KMatrixWrapper mldivide(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = mldivide(a.mat, b.mat);
	return out;
}

KMatrixWrapper mrdivide(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = mrdivide(a.mat, b.mat);
	return out;
}

KMatrixWrapper lrdivide(const KMatrixWrapper &a, int ar, const KMatrixWrapper &b, int br)
{
	KMatrixWrapper out;
	out.mat = ldivide( a.mat( ar,colon() ) , b.mat( br,colon() ) );
	return out;
}

KMatrixWrapper lcdivide(const KMatrixWrapper &a, int ac, const KMatrixWrapper &b, int bc)
{
	KMatrixWrapper out;
	out.mat = ldivide( a.mat( colon(),ac ) , b.mat( colon(),bc ) );
	return out;
}

KMatrixWrapper rrdivide(const KMatrixWrapper &a, int ar, const KMatrixWrapper &b, int br)
{
	KMatrixWrapper out;
	out.mat = rdivide( a.mat( ar,colon() ) , b.mat( br,colon() ) );
	return out;
}

KMatrixWrapper rcdivide(const KMatrixWrapper &a, int ac, const KMatrixWrapper &b, int bc)
{
	KMatrixWrapper out;
	out.mat = rdivide( a.mat( colon(),ac ) , b.mat( colon(),bc ) );
	return out;
}

KMatrixWrapper plus(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = plus(a.mat, b.mat);
	return out;
}

KMatrixWrapper minus(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = minus(a.mat, b.mat);
	return out;
}

KMatrixWrapper rdivide(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = rdivide(a.mat, b.mat);
	return out;
}

KMatrixWrapper ldivide(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = ldivide(a.mat, b.mat);
	return out;
}

KMatrixWrapper power(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = power(a.mat, b.mat);
	return out;
}

KMatrixWrapper mpower(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = mpower(a.mat, b.mat);
	return out;
}

KMatrixWrapper lt(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = lt(a.mat, b.mat);
	return out;
}

KMatrixWrapper gt(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = gt(a.mat, b.mat);
	return out;
}

KMatrixWrapper le(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = le(a.mat, b.mat);
	return out;
}

KMatrixWrapper ge(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = ge(a.mat, b.mat);
	return out;
}

KMatrixWrapper eq(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = eq(a.mat, b.mat);
	return out;
}

KMatrixWrapper neq(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = neq(a.mat, b.mat);
	return out;
}

KMatrixWrapper and_func(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = and_func(a.mat, b.mat);
	return out;
}

KMatrixWrapper or_func(KMatrixWrapper a, KMatrixWrapper b)
{
	KMatrixWrapper out;
	out.mat = or_func(a.mat, b.mat);
	return out;
}

KMatrixWrapper not_func(KMatrixWrapper a)
{
	KMatrixWrapper out;
	out.mat = not_func(a.mat);
	return out;
}

KMatrixWrapper sqrt(KMatrixWrapper a)
{
	KMatrixWrapper out;
	out.mat = sqrt(a.mat);
	return out;
}

KMatrixWrapper mean(const KMatrixWrapper &a )
{
	KMatrixWrapper out;
	out.mat = mean(a.mat);
	return out;
}

KMatrixWrapper mean(const KMatrixWrapper &a, const KMatrixWrapper &dim )
{
	KMatrixWrapper out;
	out.mat = mean(a.mat, dim.mat);
	return out;
}

KMatrixWrapper median(const KMatrixWrapper &a )
{
	KMatrixWrapper out;
	out.mat = median(a.mat);
	return out;
}

KMatrixWrapper median(const KMatrixWrapper &a, const KMatrixWrapper &dim )
{
	KMatrixWrapper out;
	out.mat = median(a.mat, dim.mat);
	return out;
}

KMatrixWrapper variance(const KMatrixWrapper &a )
{
	KMatrixWrapper out;
	out.mat = var(a.mat);
	return out;
}

void subMatrix( KMatrixWrapper &a, uint str, uint enr, uint stc, uint enc, const KMatrixWrapper &b)
{
	double temp[1]; 
	
	temp[0] = str; mwArray mstr(1,1,temp);
	temp[0] = enr; mwArray menr(1,1,temp);
	temp[0] = stc; mwArray mstc(1,1,temp);
	temp[0] = enc; mwArray menc(1,1,temp);


	a.mat( colon(mstr,menr), colon(mstc,menc) ) = b.mat;
}

void subMatrix( KMatrixWrapper &a, uint astr, uint aenr, uint astc, uint aenc, 
		  const KMatrixWrapper &b, uint bstr, uint benr, uint bstc, uint benc )
{
	double temp[1]; 
	
	temp[0] = astr; mwArray mastr(1,1,temp);
	temp[0] = aenr; mwArray maenr(1,1,temp);
	temp[0] = astc; mwArray mastc(1,1,temp);
	temp[0] = aenc; mwArray maenc(1,1,temp);
	temp[0] = bstr; mwArray mbstr(1,1,temp);
	temp[0] = benr; mwArray mbenr(1,1,temp);
	temp[0] = bstc; mwArray mbstc(1,1,temp);
	temp[0] = benc; mwArray mbenc(1,1,temp);

	a.mat( colon(mastr,maenr), colon(mastc,maenc) ) = 
	b.mat( colon(mbstr,mbenr), colon(mbstc,mbenc) );
}

KMatrixWrapper reshape(const KMatrixWrapper &a, int r, int c)
{
	KMatrixWrapper out;
	out.mat = reshape(a.mat, r, c);
	return out;
}

KMatrixWrapper norm(const KMatrixWrapper &a)
{
	KMatrixWrapper out;
	out.mat = norm(a.mat);
	return out;
}

KMatrixWrapper norm(const KMatrixWrapper &a, const KMatrixWrapper &p)
{
	KMatrixWrapper out;
	out.mat = norm(a.mat, p.mat);
	return out;
}

KMatrixWrapper randu(int n)
{
	double temp[1]; temp[0] = n; mwArray in(1,1,temp);
	KMatrixWrapper out;
	out.mat = rand(in);
	return out;
}

KMatrixWrapper randu(int m, int n)
{
	double temp[1]; 
	temp[0] = m; mwArray inr(1,1,temp);
	temp[0] = n; mwArray inc(1,1,temp);

	KMatrixWrapper out;
	out.mat = rand(inr,inc);
	return out;
}

KMatrixWrapper min(const KMatrixWrapper &a)
{
	KMatrixWrapper out;
	out.mat = min(a.mat);
	return out;
}

KMatrixWrapper min(const KMatrixWrapper &a, const KMatrixWrapper &b)
{
	KMatrixWrapper out;
	out.mat = min(a.mat,b.mat);
	return out;
}

KMatrixWrapper min(const KMatrixWrapper &a, const KMatrixWrapper &b, const KMatrixWrapper &dim)
{
	KMatrixWrapper out;
	out.mat = min(a.mat,b.mat,dim.mat);
	return out;
}

KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a)
{
	KMatrixWrapper out;
	out.mat = min(&(I->mat),a.mat);
	return out;
}

KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b)
{
	KMatrixWrapper out;
	out.mat = min(&(I->mat),a.mat,b.mat);
	return out;
}

KMatrixWrapper min(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b
				  , const KMatrixWrapper &dim)
{
	KMatrixWrapper out;
	out.mat = min(&(I->mat),a.mat,b.mat,dim.mat);
	return out;
}

KMatrixWrapper max(const KMatrixWrapper &a)
{
	KMatrixWrapper out;
	out.mat = max(a.mat);
	return out;
}

KMatrixWrapper max(const KMatrixWrapper &a, const KMatrixWrapper &b)
{
	KMatrixWrapper out;
	out.mat = max(a.mat,b.mat);
	return out;
}

KMatrixWrapper max(const KMatrixWrapper &a, const KMatrixWrapper &b, const KMatrixWrapper &dim)
{
	KMatrixWrapper out;
	out.mat = max(a.mat,b.mat,dim.mat);
	return out;
}

KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a)
{
	KMatrixWrapper out;
	out.mat = max(&(I->mat),a.mat);
	return out;
}

KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b)
{
	KMatrixWrapper out;
	out.mat = max(&(I->mat),a.mat,b.mat);
	return out;
}

KMatrixWrapper max(KMatrixWrapper *I, const KMatrixWrapper &a, const KMatrixWrapper &b
				  , const KMatrixWrapper &dim)
{
	KMatrixWrapper out;
	out.mat = max(&(I->mat),a.mat,b.mat,dim.mat);
	return out;
}


KMatrixWrapper identity()
{
	KMatrixWrapper out;
	out.mat = eye();
	return out;
}

KMatrixWrapper identity(const int &n)
{
	KMatrixWrapper out;
	out.mat = eye(n);
	return out;
}

KMatrixWrapper identity(const int &m, const int &n)
{
	KMatrixWrapper out;
	out.mat = eye(m,n);
	return out;
}

KMatrixWrapper eig(const KMatrixWrapper &A)
{
	KMatrixWrapper output;
	output.mat = eig( A.mat );
	return output;
}

KMatrixWrapper eig(KMatrixWrapper *D, const KMatrixWrapper &A)
{
	KMatrixWrapper output;
	output.mat = eig( &(D->mat), A.mat );
	return output;
}

KMatrixWrapper eig(KMatrixWrapper &A, const KMatrixWrapper &B)
{
	KMatrixWrapper output;
	output.mat = eig( A.mat, B.mat );
	return output;
}

KMatrixWrapper eig(KMatrixWrapper *D, KMatrixWrapper &A, const KMatrixWrapper &B)
{
	KMatrixWrapper output;
	output.mat = eig( &(D->mat), A.mat, B.mat );
	return output;
}

KMatrixWrapper eig(KMatrixWrapper *D, KMatrixWrapper &A, const KMatrixWrapper &B
				   , const KMatrixWrapper &flag)
{
	KMatrixWrapper output;
	output.mat = eig( &(D->mat), A.mat, B.mat, flag.mat );
	return output;
}

void SetMatrixData(KMatrixWrapper &A, int r, int c, const double &d )
{
	A.mat(r,c) = d;
}

KMatrixWrapper crossMatrix(const KMatrixWrapper &A )
{
	KMatrixWrapper output(3,3);

	output(1,1) =  0;			output(1,2) = -A.mat(3,1);	output(1,3) =  A.mat(2,1);
	output(2,1) =  A.mat(3,1);	output(2,2) =  0;			output(2,3) = -A.mat(1,1);
	output(3,1) = -A.mat(2,1);	output(3,2) =  A.mat(1,1);	output(3,3) =  0;

	return output;
}

KMatrixWrapper sum(const KMatrixWrapper &A )
{
	KMatrixWrapper output;
	output.mat = sum(A.mat);
	return output;
}

KMatrixWrapper sum(const KMatrixWrapper &A,const KMatrixWrapper &dim )
{
	KMatrixWrapper output;
	output.mat = sum(A.mat,dim.mat);
	return output;
}

// returns the eigenvector associated with the minimum eigenvalue of A
// A must be square.
KMatrixWrapper MES(const KMatrixWrapper &A)
{
	int rn,cn; // row number == column number
	
	MatrixSize(A, rn,cn);


	if( rn != cn ) AfxMessageBox("Matrix must be square");

	mwArray eval, evec;
	evec = eig( &eval, A.mat );

	mwArray d = diag( eval );
	
	double *data = mxGetPr( d.GetData() );

	int minIndex = 0;
	double min=data[0];
	for( int i=1; i<rn; i++ )
	{
		if( min > data[i] )
		{
			minIndex = i;
			min = data[i];
		}
	}

	data = mxGetPr( evec.GetData() );
	
	double * ret = new double[rn];
	for( i=0; i<rn; i++ )
	{
		ret[i] = data[minIndex*rn+i];
	}

	KMatrixWrapper output(rn,1, ret ); 
	
	delete[]ret;
	return output;
}

// returns the leftmost vector of V.
// the singularvector corresponding to the smallest singularvalue.
KMatrixWrapper DLT(const KMatrixWrapper &A, double* &ret)
{
	int rn,cn; MatrixSize(A,rn,cn);
	
	KMatrixWrapper U,S,V;
	
	U = svd(S,V,A);
	
	ret = V.column(cn);
	
	return KMatrixWrapper(cn,1, ret );
}

KMatrixWrapper cross(const KMatrixWrapper &U,const KMatrixWrapper &V )
{
	KMatrixWrapper output;
	output.mat = cross(U.mat, V.mat);
	return output;
}

KMatrixWrapper cross(const KMatrixWrapper &U,const KMatrixWrapper &V,const KMatrixWrapper &dim )
{
	KMatrixWrapper output;
	output.mat = cross(U.mat, V.mat, dim.mat);
	return output;
}

KMatrixWrapper Zeros(const int&rn, const int &cn)
{
	KMatrixWrapper output;
	output.mat = zeros(rn,cn);
	return output;
}

KMatrixWrapper Ones(const int&rn, const int &cn)
{
	KMatrixWrapper output;
	output.mat = ones(rn,cn);
	return output;
}

KMatrixWrapper rotation(const double &theta, int sz)
{
	KMatrixWrapper output;
	output = identity(sz);

	double kos=cos(theta);
	double zin=sin(theta);
	
	output.mat(1,1) =  kos;
	output.mat(1,2) = -zin;
	output.mat(2,1) =  zin;
	output.mat(2,2) =  kos;

	return output;
}

KMatrixWrapper roots( const KMatrixWrapper &c )
{
	KMatrixWrapper output;
	output.mat = roots( c.mat );
	return output;
}

KMatrixWrapper signum( const KMatrixWrapper &A )
{
	KMatrixWrapper output;
	output.mat = sign( A.mat );
	return output;
}

KMatrixWrapper signum( const mwNumericSubArray &A )
{
	KMatrixWrapper output;
	output.mat = sign( A );
	return output;
}

KMatrixWrapper sqrt( const KMatrixWrapper &A )
{
	KMatrixWrapper output;
	output.mat = sqrt( A.mat );
	return output;
}

KMatrixWrapper mag(const KMatrixWrapper &A)
{
	KMatrixWrapper output;
	output.mat = abs( A.mat );
	return output;
}

KMatrixWrapper diag(const KMatrixWrapper &A)
{
	KMatrixWrapper output;
	output.mat = diag( A.mat );
	return output;
}

KMatrixWrapper nullVector(const KMatrixWrapper &A, uint opt)
{
	KMatrixWrapper U,S,V;

	int rn,cn; MatrixSize(A,rn,cn);

	U = svd(S,V,A);

	if( opt == 1 ) // left null vector
	{
		return KMatrixWrapper(rn,1,U.column(cn));
	}
	else // right null vector
	{
		return KMatrixWrapper(cn,1,V.column(cn));
	}
}

void nullVector(const KMatrixWrapper &A, KMatrixWrapper &left, KMatrixWrapper &right)
{
	int rn,cn; MatrixSize(A,rn,cn);

	KMatrixWrapper U,S,V;
	U = svd(S,V,A);

	left  = KMatrixWrapper(rn,1,U.column(cn));
	right = KMatrixWrapper(cn,1,V.column(cn));
}

KMatrixWrapper DecreaseRank(const KMatrixWrapper &input, const int rank)
{
	KMatrixWrapper output;
	
	KMatrixWrapper U,S,V;
	int rn, cn;
	MatrixSize(input,rn,cn);

	U = svd(S,V,input);

	int minr;
	
	if( rn < cn ) 
		minr = rn; 
	else 
		minr = cn;

	if( minr <= rank ) return input;

	for( int i=rank+1; i<=minr; i++ )
	{
		S.mat(i,i) = 0;
	}

	output = U*S*(~V);

	return output;
}

int matcmp(const KMatrixWrapper &A, const KMatrixWrapper &B )
{
// returns  0 if A == B
// returns  1 if A >  B
// returns  2 if A <  B
// returns -1 if size(A) != size(B)

	int ra,ca;	MatrixSize(A,ra,ca);
	int rb,cb;	MatrixSize(B,rb,cb);

	if( ra != rb && ca != cb ) return -1; // not equal matrices

	double *adata = MatrixDataPointer(A); // returns row order
	double *bdata = MatrixDataPointer(B);

	int index; 
	for( int y=0; y<ra; y++ )
	{
		for( int x=0; x<ca; x++ )
		{
			index = y*ca+x;
			if( adata[index] < bdata[index] )
			{
				delete []adata;
				delete []bdata;
				return 2;
			}
			if( adata[index] > bdata[index] ) 
			{
				delete []adata;
				delete []bdata;
				return 1;
			}
		}
	}

	delete []adata;
	delete []bdata;
	return 0;
}


void qr(const KMatrixWrapper &in1, KMatrixWrapper &out1, KMatrixWrapper &out2)
{
	out1.mat = qr(&(out2.mat),in1.mat);
}















