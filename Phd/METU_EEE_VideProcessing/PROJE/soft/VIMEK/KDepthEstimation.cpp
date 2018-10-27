/**************************************************************
KDepthEstimation.cpp

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KDepthEstimation.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KDepthEstimation.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KDepthEstimation.cpp
or the use or other dealings in KDepthEstimation.cpp

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/DE"
**************************************************************/

// KDepthEstimation.cpp: implementation of the KDepthEstimation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KDepthEstimation.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KDepthEstimation::KDepthEstimation()
{
	mCorrespondenceList.clear();
}

KDepthEstimation::~KDepthEstimation()
{

}

void KDepthEstimation::DecomposeEMatrix()
{
	int size  = mCorrespondenceList.size();
	if( size <= 0 ) return;

	double* im1data=new double[3*size];
	double* im2data=new double[3*size];

	DynamicPairIterator itr = mCorrespondenceList.begin();

	for( int i=0; i<size; i++, itr++ )
	{
		im1data[3*i  ] = itr->p1.x;
		im1data[3*i+1] = itr->p1.y;
		im1data[3*i+2] = 1;

		im2data[3*i  ] = itr->p2.x;
		im2data[3*i+1] = itr->p2.y;
		im2data[3*i+2] = 1;
	}
	KMatrixWrapper im1points(3,size,im1data); delete []im1data;
	KMatrixWrapper im2points(3,size,im2data); delete []im2data;

	KMatrixWrapper Nim1points(size,3), Nim2points(size,3);
	
	Nim1points = ( !mCameraMatrix ) * ( im1points );
	Nim2points = ( !mCameraMatrix ) * ( im2points );

	KMatrixWrapper E = (~mCameraMatrix)*mFundamental*mCameraMatrix;

	KMatrixWrapper Et = ~E;

/////////////////////////////////////////////////////////////////////////////////////
///////////////////// CHECK EXISTENCE OF R & T //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
/////////////// SOLVE T FROM E //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
	
	mT = MES(E*Et);  // Get the eigenvector corr. to smallest eigenvalue.
		
/////////////////////////////////////////////////////////////////////////////////////
////////////////////// SELECT SIGN OF T /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	KMatrixWrapper Tx = crossMatrix( mT );
	KMatrixWrapper res = sum(sum(times(Tx*Nim2points , E*Nim1points)));
	
	double dat = MatrixData(res);
	if( dat < 0 ) mT = -mT;

/////////////////////////////////////////////////////////////////////////////////////
///////////////// SOLVE R FROM E & T ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	// Form The Bi matrices such that 
	// Bi = [ 0 ~(Ci-Di); (Di-Ci) [Di+C+]x ] where C = [-ts]x and D = ~E; 
	// Ai = ith column of the A matrix and 
	// []x represents the cross product matrix form of a vector
	// Define B matrix as B = sum( ~Bi * Bi )
	// q(4-vector) = unit eigenvector of B, associated with the smallest eigenvalue

	KMatrixWrapper B1(4,4), B2(4,4), B3(4,4);

	KMatrixWrapper C, D, CminusD, CplusD;

	C = crossMatrix( -mT );
	D = Et;
	
	CminusD = C-D;
	CplusD  = C+D;

	KMatrixWrapper col1m = KMatrixWrapper( 3,1, CminusD.column(1) );
	KMatrixWrapper col2m = KMatrixWrapper( 3,1, CminusD.column(2) );
	KMatrixWrapper col3m = KMatrixWrapper( 3,1, CminusD.column(3) );

	KMatrixWrapper col1p = KMatrixWrapper( 3,1, CplusD.column(1) );
	KMatrixWrapper col2p = KMatrixWrapper( 3,1, CplusD.column(2) );
	KMatrixWrapper col3p = KMatrixWrapper( 3,1, CplusD.column(3) );


	B1(1,1) = 0;
	subMatrix(B1,2,4,1,1, -col1m            );
	subMatrix(B1,1,1,2,4, transpose  (col1m));
	subMatrix(B1,2,4,2,4, crossMatrix(col1p));

	B2(1,1) = 0;
	subMatrix(B2,2,4,1,1, -col2m            );
	subMatrix(B2,1,1,2,4, transpose  (col2m));
	subMatrix(B2,2,4,2,4, crossMatrix(col2p));

	B3(1,1) = 0;
	subMatrix(B3,2,4,1,1, -col3m            );
	subMatrix(B3,1,1,2,4, transpose  (col3m));
	subMatrix(B3,2,4,2,4, crossMatrix(col3p));

	KMatrixWrapper Bsum = (~B1)*B1+(~B2)*B2+(~B3)*B3;

	KMatrixWrapper q = MES( Bsum ); // evec assoc. w/ smallest eval

	double *qDat = MatrixDataPointer(q);
	
	double q0 = qDat[0];
	double q1 = qDat[1];
	double q2 = qDat[2];
	double q3 = qDat[3];

	delete []qDat;

	double *rdata = new double[9];

	rdata[0] = q0*q0+q1*q1-q2*q2-q3*q3;	rdata[1] = 2*(q1*q2-q0*q3);			rdata[2] = 2*(q1*q3+q0*q2);
	rdata[3] = 2*(q2*q1+q0*q3);			rdata[4] = q0*q0-q1*q1+q2*q2-q3*q3;	rdata[5] = 2*(q2*q3-q0*q1);
	rdata[6] = 2*(q3*q1-q0*q2);			rdata[7] = 2*(q3*q2+q0*q1);			rdata[8] = q0*q0-q1*q1-q2*q2+q3*q3;
	
	mR = KMatrixWrapper(3,3,rdata); delete []rdata;

	Tx = crossMatrix( mT );
	KMatrixWrapper res1 = Tx * Nim2points;
	KMatrixWrapper res2 = cross(Nim2points, mR*Nim1points);

	res = sum(sum(times(res1,res2)));

	dat = MatrixData( res );

	if( dat < 0 ) mT = -mT;

	KMatrixWrapper AugRT1(3,4), AugRT2(3,4);
		
	subMatrix(AugRT1,1,3,1,3, identity(3) ); subMatrix(AugRT1,1,3,4,4, Zeros(3,1)  );
	subMatrix(AugRT2,1,3,1,3, mR		  ); subMatrix(AugRT2,1,3,4,4, mT		   );

	mP1 = mCameraMatrix*AugRT1;
	mP2 = mCameraMatrix*AugRT2;
}

void KDepthEstimation::PolynomialTriangulation()
{
	int sz = mCorrespondenceList.size();

	DynamicPair correctedCorr;

	// find the epipoles
	KMatrixWrapper U,S,V;
	U = svd(S,V,mFundamental);
	
	double *e1d = V.column(3); KMatrixWrapper e1(3,1,e1d);
	double *e2d = U.column(3); KMatrixWrapper e2(3,1,e2d);

	KMatrixWrapper L1 = identity(3); KMatrixWrapper L2 = identity(3);
	KMatrixWrapper R1 = identity(3); KMatrixWrapper R2 = identity(3);

	KMatrixWrapper T, Tp, tep, F, rt;
	
	double* temp;
	double* Fdata;
	double  rootsData[7];
	double* root;

	double x1,x2,y1,y2, theta1, theta2;
	double f, fp;
	double a,b,c,d,M,Mp,fp2,fp4,f2,f4;
	double line2a, line2b, line2c;
	double x_pro_1,y_pro_1,x_pro_2,y_pro_2;
	int rn, cn; 

	KMatrixWrapper p1, p2;
	double *p1data, *p2data;
	
	int minIndex;
	double minval, t,value;

	KMatrixWrapper error(1,1);error(1,1)=0;

	DynamicPairIterator   itr = mCorrespondenceList.begin();

	correspondencePair tmp;

	for( int index=0; index<sz; index++, itr++ )
	{
		x1 = itr->p1.x;
		y1 = itr->p1.y;
		x2 = itr->p2.x;
		y2 = itr->p2.y;

		L1(1,3) = -x1;    L2(1,3) = -x2;
		L1(2,3) = -y1;    L2(2,3) = -y2;

		theta1 = atan( (e1d[2]*y1-e1d[1])/(e1d[0]-e1d[2]*x1)  );
		theta2 = atan( (e2d[2]*y2-e2d[1])/(e2d[0]-e2d[2]*x2)  );
    
		R1 = rotation( theta1 , 3 );
		R2 = rotation( theta2 , 3 );

		T = R1*L1;
		Tp= R2*L2;

	    tep = T *e1; temp = MatrixDataPointer( tep ); f = temp[2]/temp[0]; delete []temp; temp = NULL;
        tep = Tp*e2; temp = MatrixDataPointer( tep ); fp= temp[2]/temp[0]; delete []temp; temp = NULL;

		F = ~(!Tp) * mFundamental*(!T);

		Fdata = MatrixDataPointer(F); // F is 3x3

	    a = Fdata[4];	b = Fdata[7];	c = Fdata[5];	d = Fdata[8];

		M   = b*c-a*d;
		Mp  = b*c+a*d;
		fp2 = fp*fp;
		fp4 = fp2*fp2;
		f2  = f*f;
		f4  = f2*f2;
		
		// coefficients of the polynomial
		rootsData[0] = a*c*f4*M;
		rootsData[1] = Mp*f4*M + pow(a,4) + fp4*pow(c,4)+ 2*fp2*pow(a,2)*pow(c,2);
		rootsData[2] = (b*d*f4+2*f2*a*c)*M + 4*( pow(a,3)*b+fp4*pow(c,3)*d+fp2*(pow(a,2)*c*d+a*b*pow(c,2)) );
		rootsData[3] = Mp*2*f2*M +6*pow(a,2)*pow(b,2)+ 6*fp4*pow(c,2)*pow(d,2)+2*fp2*(pow(a,2)*pow(d,2)+pow(b,2)*pow(c,2)+4*a*b*c*d);
		rootsData[4] = (a*c+2*b*d*f2)*M + 4*a*pow(b,3)+4*fp4*c*pow(d,3)+4*fp2*(pow(b,2)*c*d+a*b*pow(d,2));
		rootsData[5] = Mp*M + pow(b,4) + fp4*pow(d,4)+ 2*fp2*pow(b,2)*pow(d,2);
		rootsData[6] = b*d*M;
    
		rt   = roots( KMatrixWrapper(1,7, rootsData) );
		root = MatrixDataPointer( rt );

		MatrixSize(rt,rn,cn); 
    
		minval = 1/f2+c*c/(a*a+fp*fp*c*c); // at t = inf
		minIndex = rn+2;
		
		if( minval > d*d/(b*b+fp*fp*d*d) ) // at t = 0
		{
			minIndex = rn+1;
			minval = d*d/(b*b+fp*fp*d*d); 
		}

		for( int m=0; m<rn; m++ )
		{
			t = root[m];
        
			value = t*t/(1+t*t*f*f) + pow(c*t+d,2) / ( pow(a*t+b,2)+ pow(c*t+d,2)*fp*fp );
        
			if( value < minval )
			{
				minval = value;
				minIndex = m;
			}
		}
    
			 if( minIndex  < rn+1 )		t = root[minIndex];
		else if( minIndex == rn+1 )		t = 0;
		else							t = INT_MAX;
		
		y_pro_1 = t/(1+t*t*f*f);
		x_pro_1 = f*t*y_pro_1;
    
		line2a = Fdata[0]*x_pro_1+Fdata[3]*y_pro_1+Fdata[6];
		line2b = Fdata[1]*x_pro_1+Fdata[4]*y_pro_1+Fdata[7];
		line2c = Fdata[2]*x_pro_1+Fdata[5]*y_pro_1+Fdata[8];
			
		x_pro_2 = -line2a*line2c/(line2a*line2a+line2b*line2b);
		y_pro_2 = -line2b*line2c/(line2a*line2a+line2b*line2b);

		p1data = new double[3];
		p2data = new double[3];

		p1data[0] = x_pro_1; p2data[0] = x_pro_2;
		p1data[1] = y_pro_1; p2data[1] = y_pro_2;
		p1data[2] = 1;		 p2data[2] = 1;

		p1 = KMatrixWrapper(3,1,p1data); delete []p1data; p1data = NULL;
		p2 = KMatrixWrapper(3,1,p2data); delete []p2data; p2data = NULL;

		p1 = (!T )*p1; p1data = MatrixDataPointer(p1);
		p2 = (!Tp)*p2; p2data = MatrixDataPointer(p2);

		error = error + (~p2) * mFundamental * p1;

		tmp.p1.x = p1data[0]; 
		tmp.p1.y = p1data[1]; 
		tmp.p2.x = p2data[0]; 
		tmp.p2.y = p2data[1]; 
		correctedCorr.push_back(tmp);

   		delete []p1data; p1data = NULL;
		delete []p2data; p2data = NULL;
		delete []Fdata;  Fdata  = NULL;
	}

	mCorrespondenceList.clear();
	mCorrespondenceList = correctedCorr; 

	correctedCorr.clear();

	double err = MatrixData(error);

	delete []e1d;
	delete []e2d;

	delete []temp;
	delete []Fdata;
	delete []root;
}

void KDepthEstimation::EigenTriangulation()
{
	int sz = mCorrespondenceList.size();
	if( sz == 0 ) return;

	KMatrixWrapper B(4,4);

	double x1, y1, x2, y2;

	KMatrixWrapper P1row1(1,4,mP1.row(1)); KMatrixWrapper P2row1(1,4,mP2.row(1));
	KMatrixWrapper P1row2(1,4,mP1.row(2)); KMatrixWrapper P2row2(1,4,mP2.row(2));
	KMatrixWrapper P1row3(1,4,mP1.row(3)); KMatrixWrapper P2row3(1,4,mP2.row(3));

	double* res;

	mWorld = KMatrixWrapper(sz,3);

	KMatrixWrapper TDP;

	DynamicPairIterator itr = mCorrespondenceList.begin();

	int index =0;
	for( int i=0; i < sz; i++, itr++ )
	{
		x1 = itr->p1.x;
		y1 = itr->p1.y;
		x2 = itr->p2.x;
		y2 = itr->p2.y;
		
		subMatrix(B,1,1,1,4,x1*P1row3-P1row1);
		subMatrix(B,2,2,1,4,y1*P1row3-P1row2);
		subMatrix(B,3,3,1,4,x2*P2row3-P2row1);
		subMatrix(B,4,4,1,4,y2*P2row3-P2row2);

		TDP  = DLT(B, res); 
		TDP = TDP / res[3]; 
		subMatrix(mWorld,i+1,i+1,1,3,~TDP,1,1,1,3);
		delete [] res; res = NULL;
	}
}

void KDepthEstimation::SetFMatrix(KMatrixWrapper fmatrix)
{
	mFundamental = fmatrix;
}

void KDepthEstimation::Process()
{
	DecomposeEMatrix();
	FfromP();
	PolynomialTriangulation(); 
	EigenTriangulation();
	//Denoise3DData();
	//CalculateReprojectionError();

//	SaveCorrespondences("c:\\temp\\support.txt",&mCorrespondenceList);
//	SaveMatrix("D:\\DERS\\PHD\\VIDEO\\PROJE\\RANSAC_results\\R.txt",mR); 
//	SaveMatrix("D:\\DERS\\PHD\\VIDEO\\PROJE\\RANSAC_results\\T.txt",mT);
//	SaveMatrix("D:\\DERS\\PHD\\VIDEO\\PROJE\\RANSAC_results\\P1.txt",mP1);
//	SaveMatrix("D:\\DERS\\PHD\\VIDEO\\PROJE\\RANSAC_results\\P2.txt",mP2);
//	SaveMatrix("c:\\temp\\cal3d.txt",mWorld);
//	SaveMatrix("D:\\DERS\\PHD\\VIDEO\\PROJE\\RANSAC_results\\F.txt",mFundamental);
}

void KDepthEstimation::SetCameraMatrix(KMatrixWrapper cameraMat)
{
	mCameraMatrix = cameraMat;
}

void KDepthEstimation::SetCorrespondences(DynamicPair *pairs)
{
	mCorrespondenceList = *pairs;
}

void KDepthEstimation::CalculateReprojectionError()
{
	int sz = mCorrespondenceList.size();

	KMatrixWrapper m(3,1), mp(3,1);

	KMatrixWrapper TDP(sz,4);

	subMatrix(TDP,1,sz,1,3,mWorld    );
	subMatrix(TDP,1,sz,4,4,Ones(sz,1));

	KMatrixWrapper pnt1(sz,3), pnt2(sz,3);
	
	DynamicPairIterator itr = mCorrespondenceList.begin();

	for( int i=0; i<sz; i++, itr++ )
	{
		pnt1(i+1,1)	= itr->p1.x;
		pnt1(i+1,2)	= itr->p1.y;
		pnt1(i+1,3) = 1;

		pnt2(i+1,1)	= itr->p2.x;
		pnt2(i+1,2)	= itr->p2.y;
		pnt2(i+1,3) = 1;
	}

	KMatrixWrapper repPnt1 = TDP * ~mP1;
	KMatrixWrapper repPnt2 = TDP * ~mP2;

	subMatrix(repPnt1, 1,sz,1,1, rcdivide(repPnt1, 1, repPnt1, 3) );
	subMatrix(repPnt1, 1,sz,2,2, rcdivide(repPnt1, 2, repPnt1, 3) );
	subMatrix(repPnt1, 1,sz,3,3, rcdivide(repPnt1, 3, repPnt1, 3) );
	subMatrix(repPnt2, 1,sz,1,1, rcdivide(repPnt2, 1, repPnt2, 3) );
	subMatrix(repPnt2, 1,sz,2,2, rcdivide(repPnt2, 2, repPnt2, 3) );
	subMatrix(repPnt2, 1,sz,3,3, rcdivide(repPnt2, 3, repPnt2, 3) );

	KMatrixWrapper err1 = sum(sum( mag( pnt1 - repPnt1 ) ));
	KMatrixWrapper err2 = sum(sum( mag( pnt2 - repPnt2 ) ));

	double er1 = MatrixData( err1 )/sz;
	double er2 = MatrixData( err2 )/sz;
}

void KDepthEstimation::FfromP()
{
	KMatrixWrapper C = nullVector(mP1, 2); // right null vector

	KMatrixWrapper elx = crossMatrix(mP2 * C);

	KMatrixWrapper pseudoP1; 
	subMatrix(pseudoP1,1,3,1,3, !mCameraMatrix);
	subMatrix(pseudoP1,4,4,1,3, Zeros(1,3));

	mFundamental = elx * mP2 * pseudoP1;
	mFundamental = mFundamental/norm(mFundamental);
}

void KDepthEstimation::FindEpipoles(KMatrixWrapper &el, KMatrixWrapper &er)
{
	nullVector(mFundamental,el,er);
}

KMatrixWrapper KDepthEstimation::GetFmatrix()
{
	return mFundamental;
}

KMatrixWrapper KDepthEstimation::GetRMatrix()
{
	return mR;
}

KMatrixWrapper KDepthEstimation::GetTMatrix()
{
	return mT;
}

KMatrixWrapper KDepthEstimation::GetP1()
{
	return mP1;
}

KMatrixWrapper KDepthEstimation::GetP2()
{
	return mP2;
}

KMatrixWrapper KDepthEstimation::GetWorldCoords()
{
	return mWorld;
}

void KDepthEstimation::Denoise3DData()
{
	int rn,cn;

	MatrixSize(mWorld,rn,cn);

	KMatrixWrapper me = mean(mWorld);

	double* meData  = MatrixDataPointer(me);
	double* varData = MatrixDataPointer(variance(mWorld));
	double* reData  = MatrixDataPointer(~mWorld);

	KMatrixWrapper newMatrix;

	double x,y,z;

	double *dist = new double[rn];

	double sum=0;
	for( int i=0; i<rn; i++ )
	{
		x = reData[3*i  ];
		y = reData[3*i+1];
		z = reData[3*i+2];
		
		dist[i] = sqrt( x*x+y*y+z*z );
		
		if(  z < 0 )
			dist[i] = INT_MAX;
		else
			sum += dist[i];	
	}
	double meanD = sum / rn;
	
	double varD=0;

	for( i=0; i<rn; i++ )
	{
		if( dist[i] < INT_MAX ) 
		{
			varD += (dist[i]-meanD)*(dist[i]-meanD);
		}
	}
	double stdD = sqrt(varD / rn);

	double ltresh = meanD - 2.5*stdD;
	double utresh = meanD + 2.5*stdD;

	DynamicPair pnts;
	int index = 0;
	for( i=0; i<rn; i++ )
	{
		x = reData[3*i  ];
		y = reData[3*i+1];
		z = reData[3*i+2];
		
		if(  dist[i] > ltresh && dist[i] < utresh )
		{
			index++;
			newMatrix(index,1) = x;
			newMatrix(index,2) = y;
			newMatrix(index,3) = z;	
			pnts.push_back(mCorrespondenceList.at(i));
		}
	}

	mWorld = newMatrix;
	mCorrespondenceList = pnts;

	MatrixSize(mWorld,rn,cn);
	int szs = mCorrespondenceList.size();


}

DynamicPair KDepthEstimation::GetCorrList()
{
	return mCorrespondenceList;
}
