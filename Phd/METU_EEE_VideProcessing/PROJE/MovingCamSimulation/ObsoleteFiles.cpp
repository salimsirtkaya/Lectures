#include "stdafx.h"
#include ".\obsoletefiles.h"

CMaskRegioner::CMaskRegioner(void)
{
}

CMaskRegioner::~CMaskRegioner(void)
{
	TRegionMap::iterator	it = m_regionMap.begin();

	while (m_regionMap.end() != it)
	{
		delete it->second;
		it->second = NULL;
		it++;
	}
}

void CMaskRegioner::FormRegions(CString maskFileName)
// extracts planes from an image mask file name which defines distinct plane regions 
// using distint intensity levels
// Arguments:
//		o	maskFileName	:gray-scale image file, each intensity level defines a 
//							distinct plane.
{
	BYTE			key;
	GraphicsPath	gp;
	unsigned int	lineStart;
	Color			clr;

	Bitmap maskBmp(maskFileName.AllocSysString());
	
	for(unsigned int row = 0; row < maskBmp.GetHeight(); row ++)
	{
		maskBmp.GetPixel(0, row, &clr);
		key = clr.GetBlue();
		lineStart = 0;

		for(unsigned int col = 1; col < maskBmp.GetWidth(); col ++)
		{
			BYTE	newKey; 
			TRegionMap::iterator	it;

			maskBmp.GetPixel(col, row, &clr);
			newKey = clr.GetBlue();
			CRgn r;
		
			if (key != newKey)
			{
				it = m_regionMap.find(key);
				if (it == m_regionMap.end())
				{
					int* tt = new int;
				//	Region* r = new(&gp);
//					TRegionMap::value_type vt(key, r);
	//				m_regionMap.insert(vt);
				}
				gp.AddLine((int)lineStart, row, col-1, row);
				m_regionMap[key]->Union(&gp);

				gp.Reset();
				lineStart = col;
			}
		}
		gp.AddLine((int)lineStart, row, col-1, row);
		m_regionMap[key]->Union(&gp);

		gp.Reset();
		lineStart = col;
	}


}