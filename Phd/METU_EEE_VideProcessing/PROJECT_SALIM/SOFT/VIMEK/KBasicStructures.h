// KBasicStructures.h: interface for the KBasicStructures class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KBASICSTRUCTURES_H__6BB0E354_6313_421E_A682_CFCF087DA907__INCLUDED_)
#define AFX_KBASICSTRUCTURES_H__6BB0E354_6313_421E_A682_CFCF087DA907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "matlab.hpp"
#include <vector>

#define PI 3.14159265358979

class KBasicStructures  
{
public:

	class dPoint2D
	{
	public:
		dPoint2D(double dx=0 , double dy=0 ); 
		double x;
		double y;
	};
	class dPoint3D
	{

	public:
		dPoint3D(double dx=0 , double dy=0, double dz = 0 ); 
		double x;
		double y;
		double z;
	};

	class node 
	{
	public:
		node();

		int index1;
		int index2;
	
		double value;
		double str_value;
	};

	class correspondencePair 
	{
	public:
		correspondencePair();

		dPoint2D p1;
		dPoint2D p2;
	};
	
	class correspondenceTriplet 
	{
	public:
		correspondenceTriplet();
		dPoint2D p1;
		dPoint2D p2;
		dPoint2D p3;
	};

	class projectionPair
	{
	public:
		projectionPair();
		dPoint2D p2D;
		dPoint3D p3D;
	};
};


typedef KBasicStructures::node node;
typedef KBasicStructures::dPoint2D dPoint2D;
typedef KBasicStructures::dPoint3D dPoint3D;
typedef KBasicStructures::correspondencePair correspondencePair;
typedef KBasicStructures::correspondenceTriplet correspondenceTriplet;

typedef std::vector<  double  > Dynamic1D;
typedef std::vector<Dynamic1D*> DynMatrix;

typedef std::vector<double*		              > Dynamic1Dp;
typedef std::vector<KBasicStructures::dPoint2D> Dynamic2D;
typedef std::vector<KBasicStructures::dPoint3D> Dynamic3D;

typedef std::vector< node  > DynamicList;

typedef std::vector<KBasicStructures::correspondencePair   > DynamicPair;
typedef std::vector<KBasicStructures::correspondenceTriplet> DynamicTriplet;

typedef std::vector<KBasicStructures::projectionPair> DynamicProjPair;


typedef DynamicPair::iterator DynamicPairIterator;

#endif // !defined(AFX_KBASICSTRUCTURES_H__6BB0E354_6313_421E_A682_CFCF087DA907__INCLUDED_)

