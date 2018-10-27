/**************************************************************
KDepthEstimation.h

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KDepthEstimation.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KDepthEstimation.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KDepthEstimation.h
or the use or other dealings in KDepthEstimation.h

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/DE"
**************************************************************/

// KDepthEstimation.h: interface for the KDepthEstimation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KDEPTHESTIMATION_H__BB5A1504_AA4F_4AF1_B164_86874321C262__INCLUDED_)
#define AFX_KDEPTHESTIMATION_H__BB5A1504_AA4F_4AF1_B164_86874321C262__INCLUDED_

#include "KBasicStructures.h"	// Added by ClassView
#include "KMatrixWrapper.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KDepthEstimation  
{
public:
	DynamicPair GetCorrList();
	KMatrixWrapper GetWorldCoords();
	KMatrixWrapper GetP2();
	KMatrixWrapper GetP1();
	KMatrixWrapper GetTMatrix();
	KMatrixWrapper GetRMatrix();
	KMatrixWrapper GetFmatrix();
	void FindEpipoles(KMatrixWrapper &el, KMatrixWrapper &er);
	void FfromP();
	void CalculateReprojectionError();
	KMatrixWrapper mWorld;
	void SetCameraMatrix(KMatrixWrapper cameraMat);
	void Process();
	void SetFMatrix(KMatrixWrapper fmatrix);
	void SetCorrespondences(DynamicPair *pairs);
	KDepthEstimation();
	virtual ~KDepthEstimation();

private:
	void Denoise3DData();
	KMatrixWrapper mP2;
	KMatrixWrapper mP1;
	KMatrixWrapper mCameraMatrix;
	KMatrixWrapper mT;
	KMatrixWrapper mR;
	KMatrixWrapper mFundamental;
	
	DynamicPair	mCorrespondenceList;
	
	void EigenTriangulation();
	void PolynomialTriangulation();
	void DecomposeEMatrix();
};

#endif // !defined(AFX_KDEPTHESTIMATION_H__BB5A1504_AA4F_4AF1_B164_86874321C262__INCLUDED_)
