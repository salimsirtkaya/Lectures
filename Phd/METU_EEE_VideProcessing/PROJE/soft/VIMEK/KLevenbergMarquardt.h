/**************************************************************
KLevenbergMarquardt.h

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

The Algortihm implemented here is taken from 

A Brief Description of the Levenberg-Marquardt Algorithm Implemented by levmar
Manolis I. A. Lourakis
Institute of Computer Science
Foundation for Research and Technology - Hellas (FORTH)
Vassilika Vouton, P.O. Box 1385, GR 711 10
Heraklion, Crete, GREECE
Webpage: http://www.ics.forth.gr/~lourakis/levmar/

--

This piece of code ("KLevenbergMarquardt.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KLevenbergMarquardt.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KLevenbergMarquardt.h
or the use or other dealings in KLevenbergMarquardt.h

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/LM"
**************************************************************/

// KLevenbergMarquardt.h: interface for the KLevenbergMarquardt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLEVENBERGMARQUARDT_H__81439E47_2F3B_428F_8ED2_1459E7AF5193__INCLUDED_)
#define AFX_KLEVENBERGMARQUARDT_H__81439E47_2F3B_428F_8ED2_1459E7AF5193__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KMatrixWrapper.h"
#include "KBasicStructures.h"


void Calculate_f_Jsampson   (KMatrixWrapper param, void *data, KMatrixWrapper&f, KMatrixWrapper&J );
void Calculate_f_Jprojection(KMatrixWrapper param, void *data, KMatrixWrapper&f, KMatrixWrapper&J );

class KLevenbergMarquardt  
{
public:
	KMatrixWrapper GetOutput();
	void SetInitialPoint(KMatrixWrapper init);
	void SetParameters(int nMaxIteration, double dT, double dParamNormThreshold, double dUpdateNormThreshold);
	void SetData( void * data );
	void Process();
	KLevenbergMarquardt();
	virtual ~KLevenbergMarquardt();

	void UseExternalFunction( void (*ptrCalculate_f_J)(KMatrixWrapper,void*,KMatrixWrapper&,KMatrixWrapper&) );

private:
	BOOL check(KMatrixWrapper &f, KMatrixWrapper &J);

	void * m_vData;

	KMatrixWrapper m_mFinalPoint;			// output 
	KMatrixWrapper m_mStartingPoint;		// initial value of the parameter vector
	KMatrixWrapper m_dUpdateNormThreshold;	// stopping threshold for the norm of the update term. If update term
											// does not change bigger than this value iteration stops
	KMatrixWrapper m_dParamNormThreshold;	// if the infinite norm of the gradient vector is smaller than 
											// this threshold iteration stops.
	double m_dT;						    // starting value for marquardt parameter. Choose 1 if you are not
											// so certain of the init vector; if you are sure choose 1e-5 ...
	int m_nMaxIterationNumber;				// as it is
	void (*m_ptrCalculate_f_J)(KMatrixWrapper,void*,KMatrixWrapper&,KMatrixWrapper&);
};

#endif // !defined(AFX_KLEVENBERGMARQUARDT_H__81439E47_2F3B_428F_8ED2_1459E7AF5193__INCLUDED_)

