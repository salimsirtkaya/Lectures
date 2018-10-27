/**************************************************************
KRANSAC.h

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Engin Tola <etola@yahoo.com>
MMRG Research Lab. 
March 20, 2005

--

This piece of code ("KRANSAC.h") can be
used, copied, modified, merged, published, and/or have copies 
distributed for academic or research purposes without 
restriction under the following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
KRANSAC.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or MMRG Research Lab. be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with KRANSAC.h
or the use or other dealings in KRANSAC.h

3. If you use this piece of code for research purposes, refer to 

Tola, Engin. "http://www.eee.metu.edu.tr/~etola/downloads/RANSAC"
**************************************************************/

// KRANSAC.h: interface for the KRANSAC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KRANSAC_H__57FE5193_58FD_4403_893A_C6E3FF17FC46__INCLUDED_)
#define AFX_KRANSAC_H__57FE5193_58FD_4403_893A_C6E3FF17FC46__INCLUDED_

#include "KBasicStructures.h"	
//#include "messaging.h"
#include "KMatrixWrapper.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KRANSAC  
{
public:
	DynamicPair GetSupportList();
	KMatrixWrapper GetFundamentalMatrix();
	void SetInput( DynamicPair mainList, int w, int h );
	void GenerateReport(CString str);
	void Process();
	KRANSAC();
	virtual ~KRANSAC();
	KMatrixWrapper Normalized8PointFundamental( DynamicPair *list );

private:
	int mIterationNumber;
	int mHeight;
	int mWidth;

	double mSampsonError;
	double mFmError;

	DynamicPair mBestSupportList;
	DynamicPair mMainList;

	KMatrixWrapper mFundamentalMatrix;

	std::vector<int> mIndexList;

	int search( std::vector<int> *list, int m);
};

#endif // !defined(AFX_KRANSAC_H__57FE5193_58FD_4403_893A_C6E3FF17FC46__INCLUDED_)
