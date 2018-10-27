/**************************************************************
KRANSAC.cpp

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KRANSAC.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KRANSAC.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KRANSAC.cpp
or the use or other dealings in KRANSAC.cpp

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/RANSAC"
**************************************************************/

// KRANSAC.cpp: implementation of the KRANSAC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KRANSAC.h"
#include <Winbase.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KRANSAC::KRANSAC()
{

}

KRANSAC::~KRANSAC()
{

}

// uses normalized 8-point F matrix  
void KRANSAC::Process()
{
	CString statTag;
//	TellParentText((CString)"RANSAC"); // messaging, unnecessary

	int sz = mMainList.size();

	int sampleSize = 8;

	if( sz < sampleSize ) return;
	
	mIndexList.clear();

	double halfWidth  = mWidth /2.0;
	double halfHeight = mHeight/2.0;

	DynamicPair list;
	correspondencePair temp;
	
	for( int i=0; i<sz; i++ )
	{
		temp = mMainList[i];

		temp.p1.x -= halfWidth;
		temp.p2.x -= halfWidth;
		temp.p1.y -= halfHeight;
		temp.p2.y -= halfHeight;
		
		list.push_back( temp );
	}
	DynamicPair *samples = new DynamicPair();
	
	std::vector<int>  indexList;

	// Randomize rand function wrt time
	int loop = clock()/100;
	for(int k=0; k<loop; k++ )
	{
		rand();
	}

	int nIterationNumber   = 5000;
	double ERROR_THRESHOLD = 4; // 2*3^2 before;

//	TellParentRange(0, nIterationNumber); // messaging, unnecessary
	
	int m,p,index;

	int support = 0, best_support = 0;

	KMatrixWrapper fundamentalMatrix (3,3);
	KMatrixWrapper fundamentalNominee(3,3);

	double error, inlier_prob;

	
	// In order to make Random Selection Regularly Distributed use Bucketizing. 
	/************** BUCKETIZING THE INPUT *****************************/
	int minx=INT_MAX, maxx=INT_MIN, miny=INT_MAX, maxy=INT_MIN;
	for(int i=0; i<sz; i++ )
	{
		if( list[i].p1.x < minx ) minx = list[i].p1.x;
		if( list[i].p1.x > maxx ) maxx = list[i].p1.x;
		if( list[i].p1.y < miny ) miny = list[i].p1.y;
		if( list[i].p1.y > maxy ) maxy = list[i].p1.y;
	}

	// divide the region defined by {minx,miny} and {maxx,maxy} into BxB buckets

	// B = 8 -->  Bucket Number along x and y directions
	DynamicPair *pBuckets[64]; // 8*8
	
	for(int i=0; i<64; i++ )
	{
		pBuckets[i] = new DynamicPair();
	}
	double spanx = maxx - minx;
	double spany = maxy - miny;
 
	int u,v;
	for(int i=0; i<sz; i++ )
	{
		u = ( list[i].p1.x - minx ) / spanx * 8; if( u == 8 ) u = 7; if( u < 0 ) u = 0;
		v = ( list[i].p1.y - miny ) / spany * 8; if( v == 8 ) v = 7; if( v < 0 ) v = 0;
		pBuckets[v * 8 + u]->push_back( list[i] );
	}

	// calculate P{ x element of B(i) }

	double dBucketProbs[64];
	
	dBucketProbs[0] = pBuckets[0]->size()/(double)sz;
	for(int i=0; i<63; i++ )
	{
		dBucketProbs[i+1] = dBucketProbs[i] + pBuckets[i+1]->size()/(double)sz;
	}

	/***************** START RANSAC **********************/
	double x1,x2,y1,y2, num, den;
	double * F = NULL;
	double n;
	int i=0;

	mwArray t;

	double *rnd;

	for(i=0; i<nIterationNumber; i++ )
	{
		/***********  RANDOM SAMPLE SELECTION  *************/
	
		// reset indexList vector
		indexList.clear();

		// reset samples vector
		samples->clear();

		int counter =0;
		KMatrixWrapper sample;
		// choose 8 random samples 
		while( indexList.size() < sampleSize )
		{
			// choose which bucket to use

			// salim sýrtkaya 21.05.2005
			t = rand();
			rnd = mxGetPr( t.GetData() );
			n= rnd[0];// a number between [0,1]
			// salim sýrtkaya 21.05.2005

			// find the bucket
			for( m=0; m<64; m++ )
			{
				if( n <= dBucketProbs[m] ) break;
			}
			if( m == 64 ) m = 1;

			if( pBuckets[m]->size() == 0 ) continue;

			
			// choose which element in bucket(m) to use

			// salim sýrtkaya 21.05.2005
			t = rand();
			rnd = mxGetPr( t.GetData() );
			n= rnd[0];// a number between [0,1]
			// salim sýrtkaya 21.05.2005
			
			if( n == 1 ) 
				p = pBuckets[m]->size()-1;
			else
				p = n*pBuckets[m]->size();
			

			// check if p exists
			if( m != 0 ) 
			{
				index  = ceil(dBucketProbs[m-1]*sz);
				index += p;
			}
			else
				index = p;

			if( search( &indexList, index ) < 0 )
			{
				indexList.push_back( index );
				samples->push_back( pBuckets[m]->at(p)  );
			}
		}


		/***************** F MATRIX CALCULATION *******************/
		// calculate fundamental matrix for the selected samples
//		time_t st = clock();
		fundamentalNominee = Normalized8PointFundamental(samples);
		
//		time_t en = clock();
//		int dur = en -st;

		/************ SUPPORT NUMBER CALCULATION *******************/
		// calculate SAMPSON ERROR( Multiple View Geometry, p271, Hartley and Zisserman )
		mSampsonError=0;
		support = 0;

		delete []F;	
		F = MatrixDataPointer( transpose(fundamentalNominee) );

		for(int j=0; j<sz; j++)
		{
			x1 = list[j].p1.x;	x2 = list[j].p2.x;
			y1 = list[j].p1.y;	y2 = list[j].p2.y;

			num = F[0]*x1*x2+F[1]*y1*x2+F[2]*x2+
				  F[3]*x1*y2+F[4]*y1*y2+F[5]*y2+
				  F[6]*x1   +F[7]*y1   +F[8];
			num = num*num;

			den = pow(F[0]*x1+F[1]*y1+F[2],2)+pow(F[3]*x1+F[4]*y1+F[5],2)
				 +pow(F[0]*x2+F[3]*y2+F[6],2)+pow(F[1]*x2+F[4]*y2+F[7],2);

			if( den != 0 )		error = num/den;
			else if( num = 0 )	error = 0;
			else				error = INT_MAX;

			if( error < ERROR_THRESHOLD )
			{
				support++;
			}
			mSampsonError += error;
		}

		if( i%50 == 0 )
		{
			statTag.Format("RANSAC:%d//%d",i,nIterationNumber);
//			TellParentText( statTag );  // messaging, unnecessary
//			TellParentStatus(i);  // messaging, unnecessary
		}

		if( support > best_support )
		{
			best_support = support;

			fundamentalMatrix = fundamentalNominee;

			// Update maximum IterationNumber
			inlier_prob  = best_support/(double)sz;
			if( pow(inlier_prob,8) > 0.99  )
				nIterationNumber = 100;
			else
			{
				nIterationNumber = -2/( log10( 1-pow(inlier_prob,8) ) )+100;
			}
						
			if( nIterationNumber > 5000 || nIterationNumber < 0 )
				nIterationNumber = 5000;

	//		nIterationNumber = 2000;
//			TellParentRange(0, nIterationNumber);  // messaging, unnecessary
		}
	}

	nIterationNumber = i;

	/***************** GUIDED MATCHING STARTS *******************************/
	
	double mFmError=0;
	
	int prevSupport;
	int counter=0;

	delete[] F;
	F = MatrixDataPointer(transpose(fundamentalMatrix));

	while( true )
	{
		// reset samples vector
		samples->clear();

		mBestSupportList.clear();

		mSampsonError=0;
		for( int j=0; j<sz; j++ )
		{
			x1 = list[j].p1.x;	x2 = list[j].p2.x;
			y1 = list[j].p1.y;	y2 = list[j].p2.y;

			num = F[0]*x1*x2+F[1]*y1*x2+F[2]*x2+
				  F[3]*x1*y2+F[4]*y1*y2+F[5]*y2+
				  F[6]*x1   +F[7]*y1   +F[8];
			num = num*num;

			den = pow(F[0]*x1+F[1]*y1+F[2],2)+pow(F[3]*x1+F[4]*y1+F[5],2)
				 +pow(F[0]*x2+F[3]*y2+F[6],2)+pow(F[1]*x2+F[4]*y2+F[7],2);

			if( den != 0 )		error = num/den;
			else if( num = 0 )	error = 0;
			else				error = INT_MAX;


			if( error < ERROR_THRESHOLD/5 )
			{
				mFmError	  += num;
				mSampsonError += error;

				samples->push_back(list[j]);
				mBestSupportList.push_back(mMainList[j]);	
				mIndexList.push_back(j);
			}			
		}

		fundamentalMatrix = Normalized8PointFundamental(samples);
		delete[] F;
		F = MatrixDataPointer(transpose(fundamentalMatrix));

		counter++;
		if( counter == 1 )
		{ 
			support = samples->size();
			prevSupport = support;
		}

		if( counter != 1 )
		{
			support = samples->size();
		
			if( support == prevSupport || counter == 15 )
				break;

			prevSupport = support;
		}
	}
	mIterationNumber = nIterationNumber;
	
	mFundamentalMatrix = fundamentalMatrix;

	delete[] F;
}

void KRANSAC::GenerateReport(CString str)
{/*
	int support = mBestSupportList.size();
	int size    = mMainList.size();
	
	KMatrixWrapper temp;
	KMatrixWrapper Report(7,17); 
	
	Report(1,colon(1,17)) = "#inliers        :";
	Report(2,colon(1,17)) = "#outliers       :";
	Report(3,colon(1,17)) = "#iteration      :";
	Report(4,colon(1,17)) = "#sampson error  :";
	Report(5,colon(1,17)) = "#sampson/inlier :";
	Report(6,colon(1,17)) = "#m'tFm          :";
	Report(7,colon(1,17)) = "#m'tFm/inlier   :";

	KMatrixWrapper mode("w");
	KMatrixWrapper file(str);
	KMatrixWrapper fid = fopen(file,mode);


	KMatrixWrapper Results;

	Results(1,1)=support;
	Results(2,1)=size-support;
	Results(3,1)=mIterationNumber;
	Results(4,1)=mSampsonError;
	Results(5,1)=mSampsonError/support;
	Results(6,1)=mFmError;
	Results(7,1)=mFmError/support;

	Results = num2str(Results);

	Report = Report + Results;

	KMatrixWrapper count = fprintf(fid, "%s", transpose(Report));
	fclose(fid);
/*
	FILE* fp = fopen(str,"w+");
	fprintf(fp,"#inliers  : %d\n",support);
	fprintf(fp,"#outliers : %d\n",size-support);
	fprintf(fp,"#iteration: %d\n",nIterationNumber);
	fprintf(fp,"sampson error: %f\n",mSampsonError);
	fprintf(fp,"sampson error per inlier: %f\n",mSampsonError/support);
	fprintf(fp,"m'Fm error: %f\n",mFmError);
	fprintf(fp,"m'Fm error per inlier: %f\n",mFmError/support);
	fclose(fp);
*/
	
}

KMatrixWrapper KRANSAC::Normalized8PointFundamental( DynamicPair *list )
{
	int size = list->size();
	
	if( size < 8 ) return KMatrixWrapper();

	double *img1x = new double[size];
	double *img1y = new double[size];
	double *img2x = new double[size];
	double *img2y = new double[size];

	for( int i=0; i<size; i++ )
	{
		img1x[i] = (*list)[i].p1.x;
		img1y[i] = (*list)[i].p1.y;
		img2x[i] = (*list)[i].p2.x;
		img2y[i] = (*list)[i].p2.y;
	}

	KMatrixWrapper list1X(size,1,img1x); delete []img1x;
	KMatrixWrapper list1Y(size,1,img1y); delete []img1y;
	KMatrixWrapper list2X(size,1,img2x); delete []img2x;
	KMatrixWrapper list2Y(size,1,img2y); delete []img2y;

	// Normalize Data Points
	double meanx1=0, meanx2=0, meany1=0, meany2=0;

	meanx1 = MatrixData(mean( list1X )); list1X = list1X - meanx1;
	meany1 = MatrixData(mean( list1Y )); list1Y = list1Y - meany1;
	meanx2 = MatrixData(mean( list2X )); list2X = list2X - meanx2;
	meany2 = MatrixData(mean( list2Y )); list2Y = list2Y - meany2;

	double variance1, variance2;
	variance1 = MatrixData( mean( sqrt_a( times(list1X,list1X)+times(list1Y,list1Y) ) ) );
	variance2 = MatrixData( mean( sqrt_a( times(list2X,list2X)+times(list2Y,list2Y) ) ) );

	double sqrt2 = sqrt(2);

	list1X = list1X/variance1*sqrt2;
	list1Y = list1Y/variance1*sqrt2;
	list2X = list2X/variance2*sqrt2;
	list2Y = list2Y/variance2*sqrt2;

	// Form De-Normalization
	double  T1data[] = {sqrt2/variance1, 0, 0, 0, sqrt2/variance1, 0, -sqrt2/variance1*meanx1, -sqrt2/variance1*meany1, 1};
	KMatrixWrapper T1(3,3,T1data);

	double  T2data[] = {sqrt2/variance2, 0, 0, 0, sqrt2/variance2, 0, -sqrt2/variance2*meanx2, -sqrt2/variance2*meany2, 1};
	KMatrixWrapper T2(3,3,T2data);

	// Minimization of |Af| with respect to |f| = 1 constraint. 
	// The solution of this minimization problem is the vector
	// corresponding to the minimum singularvalue, namely 
	// rightmost vector of Z.( where Z is obtained by A = UWZ' 
	// decomposition{SVD} )

	KMatrixWrapper  xprod = times(list1X,list2X);
	KMatrixWrapper xyprod = times(list1X,list2Y);
	KMatrixWrapper yxprod = times(list1Y,list2X);
	KMatrixWrapper  yprod = times(list1Y,list2Y);

	KMatrixWrapper A(size,9);

	subMatrix(A,1,size,1,1,  xprod);
	subMatrix(A,1,size,2,2, yxprod);
	subMatrix(A,1,size,3,3, list2X);
	subMatrix(A,1,size,4,4, xyprod);
	subMatrix(A,1,size,5,5,  yprod);
	subMatrix(A,1,size,6,6, list2Y);
	subMatrix(A,1,size,7,7, list1X);
	subMatrix(A,1,size,8,8, list1Y);
	subMatrix(A,1,size,9,9, Ones(size,1));

	KMatrixWrapper U, S, V;
	U = svd( S, V, A);

	// take the V matrices corresponding vector to the smallest singular vector
	KMatrixWrapper F(1,9,V.column(9));
	
	// reshape to 3x3
	F = transpose(reshape( F, 3, 3));

	// This F Matrix have to be converted to its Rank 2 form by
	// minimizing the Frobenius Norm.

	// To find the closest rank 2 matrix to the F matrix, 
	// set the smallest singular value of the decomposition to 0.
	U = svd( S, V, F );

	// Set the smallest singular value to 0
	S(3,3) = 0;

	// Recompose Fprime --> Rank 2 Fundamental Matrix.
	KMatrixWrapper Fprime = U * S * transpose(V);

	// Recompense for the normalization of points.
	Fprime = transpose(T2) * Fprime * T1; 

	// Normalize Fprime;
	double nrm = MatrixData(norm(Fprime));
	Fprime = Fprime/nrm;

	return Fprime;
}

void KRANSAC::SetInput(DynamicPair mainList, int w, int h)
{
	mMainList = mainList;
	mWidth  = w;
	mHeight = h;

	mBestSupportList.clear();
}

KMatrixWrapper KRANSAC::GetFundamentalMatrix()
{
	return mFundamentalMatrix;
}

DynamicPair KRANSAC::GetSupportList()
{
	return mBestSupportList;
}

int KRANSAC::search( std::vector<int> *list, int m)
{
	for(int i=0; i<list->size(); i++)
	{
		if( (*list)[i] == m )
			return i;
	}

	return -1;
}
