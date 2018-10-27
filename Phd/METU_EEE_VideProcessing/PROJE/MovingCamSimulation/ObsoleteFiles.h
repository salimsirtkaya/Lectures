#pragma once
#pragma warning( disable : 4786 ) 

#include <map>



typedef std::map<BYTE, Region*> TRegionMap;

class CMaskRegioner
{
public:
	CMaskRegioner(void);
	~CMaskRegioner(void);
	void FormRegions(CString maskFileName);

private:
	TRegionMap	m_regionMap;	//key: intensity that masks the region, value: region
};

