// Feature.h: interface for the CFeature class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURE_H__0078C956_3C72_4BA3_8AB9_DC47190A64A0__INCLUDED_)
#define AFX_FEATURE_H__0078C956_3C72_4BA3_8AB9_DC47190A64A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CFeature  
{
public:
	CFeature();
	virtual ~CFeature();
	float x;
	float y;
	float vx;
	float vy;
	int block_no;
};

class CBucket
{
public:
	CBucket();
	virtual ~CBucket();

	int size ;
	int index;
};

class CBlock
{
public:
	CBlock();
	virtual ~CBlock();

	double vx, vy;
	int x,y;
	int block_no;
};

#endif // !defined(AFX_FEATURE_H__0078C956_3C72_4BA3_8AB9_DC47190A64A0__INCLUDED_)
