/**************************************************************

MpegFile.cpp

Header file for class CMpegFile.

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Yagiz Yasaroglu
TUBITAK BILTEN
November 20, 2002

--

This file ("MpegFile.h") can be used, copied, modified, 
merged, published, and/or have copies distributed for 
academic or research purposes without restriction under the 
following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
MpegFile.h.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with MpegFile.h
or the use or other dealings in MpegFile.h.

DirectShow is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/

#ifndef __MpegFile_h_
#define __MpegFile_h_

//-- class CMpegFile ------------------------------------------
class CMpegFile
{
public:
	CMpegFile();	// Default constructor.
	~CMpegFile();
	CMpegFile(const CMpegFile & source);

	CMpegFile & operator = (const CMpegFile & source);

	void SetFileName (const char * filename);
	char * GetFileName ();

	long int width;
	long int height;
	__int64 frameCount;
	float framesPerSecond;

protected:
	char * fileName;
};

#endif