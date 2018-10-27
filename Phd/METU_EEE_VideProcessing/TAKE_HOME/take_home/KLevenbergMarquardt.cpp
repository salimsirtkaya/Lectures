/**************************************************************
KLevenbergMarquardt.cpp

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KLevenbergMarquardt.cpp") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KLevenbergMarquardt.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KLevenbergMarquardt.cpp
or the use or other dealings in KLevenbergMarquardt.cpp

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/LM"
**************************************************************/

// KLevenbergMarquardt.cpp: implementation of the KLevenbergMarquardt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "k3dreconstruction.h"
#include "KLevenbergMarquardt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KLevenbergMarquardt::KLevenbergMarquardt()
{
	m_nMaxIterationNumber = 10;
	m_dT = 1;
	m_dUpdateNormThreshold = 1e-16;
	m_dParamNormThreshold  = 1e-16;

	m_ptrCalculate_f_J = NULL;

//	m_mStartingPoint = 0;
//	m_bUsingExternalFunction = false;
}

KLevenbergMarquardt::~KLevenbergMarquardt()
{

}

void KLevenbergMarquardt::Process()
{
	// minimizes F=sum( f(i)^2 ) cost function w.r.t a parameter vector
	// J(i) is the derivative of f(i) w.r.t parameter vector
	// g is the gradient
	// F is the total cost
	// f is the cost for each sample

	if( m_ptrCalculate_f_J == NULL  ) 
	{
		AfxMessageBox("Error in LM: External Cost function Not Specified");
	}

	KMatrixWrapper A;
	KMatrixWrapper f, fn, J, Jn, g, h;
	KMatrixWrapper nullmw; nullmw(1,1)=0;
	
	KMatrixWrapper ng, nx, mu, dL, F, Fn, dF;

	if( !check(f, J) ) return;

	A = transpose(J)*J;
	g = transpose(J)*f; 
    F = norm(f)*norm(f)/2; 

	int iteration = 1;
	int nu;
	
	nu = 2;   

	KMatrixWrapper nh; nh(1,1)=0;

	ng = norm(g,KMatrixWrapper("inf"));

	int rn,cn; MatrixSize(A,rn,cn);

	KMatrixWrapper infA = max( diag(A) );
	KMatrixWrapper Identity = identity(rn,cn);
	
	mu = m_dT * infA;   // maximum of the diagonal
   
	int stop = 0;

	KMatrixWrapper x = m_mStartingPoint;
	KMatrixWrapper xnew;

	while( !stop )
	{
		if( matcmp( ng , m_dParamNormThreshold )%2 == 0 )
		{
			stop = true;  
		}
		else
		{			
			h = mldivide( A+mu*Identity, -g  );

//			h = (inv(A + mu*Identity))*(-g);

			nh = norm(h);
			nx = m_dUpdateNormThreshold + norm(x);

			if( matcmp( nh , m_dUpdateNormThreshold*nx )%2 == 0 ) 
			{
				stop = 2;
			}
			else if( matcmp(nx/2e-16, nh)%2 == 2 ) 
			{
				stop = 4; 
			}
			// Almost singular ?
		}
		if( !stop )
		{
			xnew = x + h;  
			h    = xnew - x;  
			dL   = (transpose(h)*(mu*h - g))/2; 

			m_ptrCalculate_f_J(xnew, m_vData, fn,Jn);

			Fn = (transpose(fn)*fn)/2; 
			dF = F - Fn;

			if( matcmp( dL , nullmw) == 1 && matcmp(dF, nullmw ) == 1 ) // Update x and modify mu
			{
				x = xnew;    
				F = Fn;
				J = Jn; 
				f = fn; 
				A = transpose(J)*J;
				g = transpose(J)*f;  
				ng = norm(g,KMatrixWrapper("inf"));

				KMatrixWrapper modifier = (1 - pow(2*MatrixData(dF/dL)-1,3) );
				if( matcmp( 1/3.0 , modifier ) == 1  )
					mu = mu/3.0;
				else 
					mu = mu*modifier; 
				
				nu = 2;
			}
			else                                  // Same  x, increase  mu
			{
				mu = mu*nu;  
				nu *= 2; 
			}
			
			iteration++;

			if(  iteration > m_nMaxIterationNumber )
			{
				stop = 3; 
			}
		}    
	} 

	m_mFinalPoint = x;
}

BOOL KLevenbergMarquardt::check(KMatrixWrapper &f, KMatrixWrapper &J)
{
	int rp, cp; MatrixSize(m_mStartingPoint, rp, cp);

	if( cp != 1 )
	{
		AfxMessageBox("Initial Parameter array must be a column vector");
		return false;
	}

	m_ptrCalculate_f_J(m_mStartingPoint,m_vData, f, J);


	int r, c;
	MatrixSize( f, r, c );

	int r2, c2;
	MatrixSize( J, r2, c2 );

	if( c != 1  )
	{
		AfxMessageBox("f must be a column vector");
		return false;
	}

	if( r != r2 )
	{
		AfxMessageBox("row numbers of f and J do not match");
		return false;
	}

	if( c2 != rp )
	{
		AfxMessageBox("number of columns in J does not match param vector");
		return false;
	}

	return true;
}

void KLevenbergMarquardt::SetData(void *data)
{
	m_vData = data;
}

void KLevenbergMarquardt::SetParameters(int nMaxIteration, double dT, double dParamNormThreshold, double dUpdateNormThreshold)
{
	m_nMaxIterationNumber  = nMaxIteration;
	m_dT = dT;
	m_dUpdateNormThreshold(1,1) = dUpdateNormThreshold;
	m_dParamNormThreshold (1,1) = dParamNormThreshold;
}

void KLevenbergMarquardt::SetInitialPoint(KMatrixWrapper init)
{
	m_mStartingPoint = init;
}

KMatrixWrapper KLevenbergMarquardt::GetOutput()
{
	return m_mFinalPoint;
}

void KLevenbergMarquardt::UseExternalFunction( void (*ptrCalculate_f_J)(KMatrixWrapper,void*,KMatrixWrapper&,KMatrixWrapper&) )
{
	m_ptrCalculate_f_J = ptrCalculate_f_J;
}


// sampson error cost function
void Calculate_f_Jsampson(KMatrixWrapper param, void *data, KMatrixWrapper&f, KMatrixWrapper&J )
{
	DynamicPair* fpar = (DynamicPair*)data;

	DynamicPair::iterator itr = fpar->begin();
	
	int size = fpar->size();

	// get param data;
	double *F = MatrixDataPointer(param);

	double x,y, xp,yp;
	double A,B,C, Ap, Bp, Cp, M, Mp, Msq, Mpsq, D, E, sqE, D_sqE;

	for( int i=0; i<size; i++, itr++ )
	{
		x  = itr->p1.x;
		y  = itr->p1.y;;
    
		xp = itr->p2.x;
		yp = itr->p2.y;
    
		A = F[0]*x+F[1]*y+F[2];	Ap = F[0]*xp+F[3]*yp+F[6];
		B = F[3]*x+F[4]*y+F[5];	Bp = F[1]*xp+F[4]*yp+F[7];
		C = F[6]*x+F[7]*y+F[8];	Cp = F[2]*xp+F[5]*yp+F[8];

		M = A*A+B*B; Mp = Ap*Ap+Bp*Bp;
		Msq = M*M;   Mpsq = Mp*Mp;
			
		D = A*xp+B*yp+C;

		E   = 1/M + 1/Mp;
		sqE = sqrt(E);
    
		f(i+1,1) = D*sqE;
		
		D_sqE = D/sqE;
        
		J(i+1,1) = x*xp * sqE - D_sqE * ( A*x/Msq + Ap*xp/Mpsq );
		J(i+1,2) = y*xp * sqE - D_sqE * ( A*y/Msq + Bp*xp/Mpsq );
		J(i+1,3) = xp   * sqE - D_sqE * ( A/Msq   );
		J(i+1,4) = x*yp * sqE - D_sqE * ( B*x/Msq + Ap*yp/Mpsq );
		J(i+1,5) = y*yp * sqE - D_sqE * ( B*y/Msq + Bp*yp/Mpsq );
		J(i+1,6) = yp   * sqE - D_sqE * ( B/Msq   );
		J(i+1,7) = x    * sqE - D_sqE * ( Ap/Mpsq );
		J(i+1,8) = y    * sqE - D_sqE * ( Bp/Mpsq );
		J(i+1,9) = 1    * sqE;  
    }

	delete[] F;
}


// projection error cost function
void Calculate_f_Jprojection(KMatrixWrapper param, void *data, KMatrixWrapper&f, KMatrixWrapper&J )
{
	KMatrixWrapper* matdat = (KMatrixWrapper*)data;
	KMatrixWrapper projectData = *matdat;

	int rn, cn; MatrixSize(projectData,rn,cn);

	double *fpar = MatrixDataPointer(transpose(projectData));

	// get param data;
	double *P = MatrixDataPointer(param);

	double u,v, X,Y,Z,P1X,P2X,P3X;
	double A, B, D, E, Fa, Fb, Ga, Gb;

	for( int i=0; i<rn; i++ )
	{
		u  = fpar[5*i  ];
		v  = fpar[5*i+1];
    
		X  = fpar[5*i+2];
		Y  = fpar[5*i+3];
		Z  = fpar[5*i+4];
    
		P1X = P[0]*X+P[1]*Y+P[ 2]*Z+P[ 3];
		P2X = P[4]*X+P[5]*Y+P[ 6]*Z+P[ 7];
		P3X = P[8]*X+P[9]*Y+P[10]*Z+P[11];
		
		A = u - P1X/P3X;
		B = v - P2X/P3X;

		D = A*A+B*B;

		f(i+1,1) = sqrt(D);
		
		E = 1/sqrt(D);

		Fa = A / P3X;
		Fb = B / P3X;
		
		Ga = Fa * P1X / P3X;
		Gb = Fb * P2X / P3X;

		J(i+1, 1) = E * ( -Fa*X );
		J(i+1, 2) = E * ( -Fa*Y );
		J(i+1, 3) = E * ( -Fa*Z ); 
		J(i+1, 4) = E * ( -Fa*1 ); 
		J(i+1, 5) = E * ( -Fb*X );
		J(i+1, 6) = E * ( -Fb*Y );
		J(i+1, 7) = E * ( -Fb*Z );
		J(i+1, 8) = E * ( -Fb*1 );
		J(i+1, 9) = E * (Ga+Gb)*X; 
		J(i+1,10) = E * (Ga+Gb)*Y; 
		J(i+1,11) = E * (Ga+Gb)*Z; 
		J(i+1,12) = E * (Ga+Gb)*1; 
    }

	delete[] P;
}
