/**************************************************************

MpegFile.cpp

Implementation file for class CMpegFile

Refer to documentation for further information related to
usage of the class, and setting up of the environment.

--

Yagiz Yasaroglu
TUBITAK BILTEN
November 20, 2002

--

This file ("MpegFile.cpp") can be used, copied, modified, 
merged, published, and/or have copies distributed for 
academic or research purposes without restriction under the 
following conditions:

1. The above header and this permission notice shall be 
included in all copies or substantial portions of 
MpegFile.cpp.

2. The software is provided "as is", without warranty of any 
kind, express or implied, including but not limited to the 
warranties of merchantability, fitness for a particular 
purpose and noninfringement. In no event shall the author(s) 
or TUBITAK BILTEN be liable for any claim, damages or 
liability, whether in an action of contract, tort or otherwise, 
arising from, out of or in connection with MpegFile.cpp
or the use or other dealings in MpegFile.cpp.

DirectShow is a trademark of Microsoft.

All other trademarks are properties of their respective
owners.

**************************************************************/

// Replace the following header (stdafx.h)  
// with Windows standard headers if not 
// using pre-compiled headers.
#include "stdafx.h"

#include "MpegFile.h"

//-------------------------------------------------------------
//-- class CMpegFile -------------------------------------
//-------------------------------------------------------------

CMpegFile::CMpegFile()
{
	width = 0;
	height = 0;
	frameCount = 0;
	framesPerSecond = 0;

	fileName = NULL;
}

CMpegFile::CMpegFile(const CMpegFile & source)
{
	frameCount = source.frameCount;
	framesPerSecond = source.framesPerSecond;
	height = source.height;
	width = source.width;

	SetFileName(source.fileName);
}

CMpegFile & CMpegFile::operator = (const CMpegFile & source)
{
	SetFileName(source.fileName);
	frameCount = source.frameCount;
	framesPerSecond = source.framesPerSecond;
	height = source.height;
	width = source.width;

	return *this;
}

CMpegFile::~CMpegFile()
{
	if (fileName)
		delete [] fileName;
}

void CMpegFile::SetFileName (const char * filename)
{
	if (fileName)
		delete [] fileName;

	fileName = new char[strlen(filename) + 1];
	strcpy(fileName, filename);
}

char * CMpegFile::GetFileName()
{
	return fileName;
}



