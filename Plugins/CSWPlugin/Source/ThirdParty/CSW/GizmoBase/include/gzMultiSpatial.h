//*****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzMultiSpatial.h
// Module		: gzBase
// Description	: Class definition of multi dim spatial data storage templates
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.200
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	100408	Created file 	
//
//******************************************************************************
#ifndef __GZ_MULTI_SPATIAL_H__
#define __GZ_MULTI_SPATIAL_H__

/*!	\file 
	\brief Templates for spatial data management. Pat Pending..

*/

#include "gzBasicTypes.h"

#define DEFAULT_VALUETYPE	gzFloat
#define DEFAULT_DIVS		2

// Forward decl
template <class T,gzUInt32 SIZE,class VALUETYPE=DEFAULT_VALUETYPE,gzUInt32 DIVS=DEFAULT_DIVS> class gzMultiSpatialIterator;

//******************************************************************************
// Class	: gzSpatialCoordinate
//									
// Purpose  : Template for feature data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050222	Created 
//									
//******************************************************************************
template <gzUInt32 SIZE,class VALUETYPE=DEFAULT_VALUETYPE,gzUInt32 DIVS=DEFAULT_DIVS> class gzSpatialCoordinate
{
public:

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>(const VALUETYPE *list=nullptr);
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>(const VALUETYPE &value);
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>(const gzArray<VALUETYPE> &array);

	// ---- Assignment ---------------------------

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &operator=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right);
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &operator=(const gzArray<VALUETYPE> &array);

	// ---- Methods ------------------------------

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> operator +(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> operator -(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> operator *(const VALUETYPE &right) const;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> operator /(const VALUETYPE &right) const;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> operator *(const gzUInt32 *right) const;

	VALUETYPE & operator[](gzUInt32 index);

	gzBool operator >=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	gzBool operator <=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	gzBool operator <(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	gzBool operator >(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;

	gzBool intersect(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &min,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &max) const;

	gzBool isZero() const;
	gzBool isOne() const;

	gzVoid setZeroTo(const VALUETYPE &value);

	VALUETYPE magDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;
	VALUETYPE sumDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &min,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &max) const;
	VALUETYPE sumDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const;


	// ---- Static Utilites ----------------------
	static gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> init(const VALUETYPE &value);
	static gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> minimum(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &a,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &b);
	static gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> maximum(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &a,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &b);
	static gzUInt32 mixIndex(gzUInt32 index);
	static gzUInt32 mixIndex(const gzUInt32 *index);
	static gzUInt32 size();
	static gzVoid calcIndex(gzUInt32 *index ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &pos ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &step);
	static gzBool compareIndex(gzUInt32 *index ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &pos ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &step);

	static gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>		ZERO;
	static gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>		ONE;

	VALUETYPE	value[SIZE];
	VALUETYPE	max,min;
};

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::gzSpatialCoordinate(const VALUETYPE &val)
{
	VALUETYPE *dest(value);

	gzUInt32 i(SIZE);

	while(i)
	{
		*dest=val;
		++dest;
		--i;
	}

	max=min=val;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::gzSpatialCoordinate(const gzArray<VALUETYPE> &array)
{
	operator=(array);
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::ZERO=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>((VALUETYPE)0);
template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::ONE=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>((VALUETYPE)1);

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::gzSpatialCoordinate(const VALUETYPE *list)
{
	if(list)
	{
		VALUETYPE *dest(value);
		const VALUETYPE *source(list);

		gzUInt32 i(SIZE);

		min=max=*source;

		while(i)
		{
			*dest=*source;

			if( *source>max )
				max=*source;

			if( *source<min )
				min=*source;

			++dest;
			++source;
			--i;
		}
	}
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right)
{
	VALUETYPE *dest(value);
	const VALUETYPE *source(right.value);

	gzUInt32 i(SIZE);

	min=right.min;
	max=right.max;

	while(i)
	{
		*dest=*source;
		++dest;
		++source;
		--i;
	}

	return *this;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator=(const gzArray<VALUETYPE> &array)
{
	VALUETYPE *dest(value);
	const VALUETYPE *source(((gzArray<VALUETYPE> &)array).getAddress());

	gzUInt32 i(SIZE),j;
	gzUInt32 steps(array.getSize()/SIZE);

	VALUETYPE sum;

	while(i)
	{
		sum=0;
		j=steps;

		while(j)
		{
			sum+=gzSq2<VALUETYPE>(*source);
			++source;
			--j;
		}

		sum=gzSqrt<VALUETYPE>(sum);

		*dest=sum;

		if(i==SIZE)
		{
			min=max=sum;
		}
		else
		{
			if( sum>max )
				max=sum;

			if( sum<min )
				min=sum;
		}

		++dest;
		--i;
	}

	return *this;
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline VALUETYPE gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::magDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	VALUETYPE dist(0);

	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		dist+=gzSq2(*l-*r);
		++l;
		++r;
		--i;
	}

	return dist;
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator +(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	if(right.isZero())
		return *this;

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	result.min=result.max=*l+*r;

	while(i)
	{
		*dest=*l+*r;

		if(*dest<result.min)
			result.min=*dest;
		else if(*dest>result.max)
			result.max=*dest;

		++l;
		++r;
		++dest;
		--i;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator -(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	if(right.isZero())
		return *this;

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	result.min=result.max=*l-*r;

	while(i)
	{
		*dest=*l-*r;
		
		if(*dest<result.min)
			result.min=*dest;
		else if(*dest>result.max)
			result.max=*dest;

		++l;
		++r;
		++dest;
		--i;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::isZero() const
{
	if(min!=0)
		return FALSE;

	if(max!=0)
		return FALSE;

	return TRUE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::isOne() const
{
	if(min!=1)
		return FALSE;

	if(max!=1)
		return FALSE;

	return TRUE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline VALUETYPE & gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator[](gzUInt32 index)
{
	if(index>=SIZE)
		throwFatalTemplateError("gzSpatialCoordinate::[] index out of bounds");

	return value[index];
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::intersect(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &minVal,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &maxVal) const
{
	if(max<minVal.min)		// All items in value are smaller than in min
		return FALSE;

	if(min>maxVal.max)		// All items in value are bigger than in max
		return FALSE;

	const VALUETYPE *l(value);
	const VALUETYPE *l_max(maxVal.value);
	const VALUETYPE *l_min(minVal.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*l<*l_min)
			return FALSE;

		if(*l>*l_max)
			return FALSE;

		++l;
		++l_max;
		++l_min;
		--i;
	}

	// All tests were positive, We have an intersection
	return TRUE;
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator >=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	// GTE in any item is true

	if(max<right.min)		// All items in value are smaller than in right
		return FALSE;

	if(max>=right.max)		// At least one item in value are bigger than right
		return TRUE;


	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*l>=*r)
			return TRUE;

		++l;
		++r;
		--i;
	}

	return FALSE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator <=(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	// LTE in any item is true

	if(min>right.max)		// All items in value are bigger than in right
		return FALSE;

	if(min<=right.min)		// at least one item in value are less than right
		return TRUE;


	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*l<=*r)
			return TRUE;

		++l;
		++r;
		--i;
	}

	return FALSE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator <(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	// LT in any item is true

	if(min>=right.max)		// All items in value are bigger or equal to right
		return FALSE;

	if(min<right.min)		// All items in value are less than right
		return TRUE;

	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*l<*r)
			return TRUE;

		++l;
		++r;
		--i;
	}

	return FALSE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator >(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	// GT in any item is true

	if(max<=right.min)		// All items in value are smaller or equal than in right
		return FALSE;

	if(max>right.max)		// All items in value are bigger than right
		return TRUE;

	const VALUETYPE *l(value);
	const VALUETYPE *r(right.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*l>*r)
			return TRUE;

		++l;
		++r;
		--i;
	}

	return FALSE;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator *(const VALUETYPE &right) const
{
	if(isZero())
		return *this;

	if(isOne())
	{
		if(right==0)
			return ZERO;
		else if (right==1)
			return ONE;
		else
			return gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>(right);
	}

	if(right==0)
		return ZERO;

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *left(value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		*dest=*left*right;

		++left;
		++dest;
		--i;
	}

	if(right>=0)
	{
		result.min=right*min;
		result.max=right*max;
	}
	else 
	{
		result.min=right*max;
		result.max=right*min;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator *(const gzUInt32 * right) const
{
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *l(value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	result.min=result.max=*l * *right;

	while(i)
	{
		*dest=*l * *right;

		if(*dest<result.min)
			result.min=*dest;
		else if(*dest>result.max)
			result.max=*dest;

		++l;
		++right;
		++dest;
		--i;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::operator /(const VALUETYPE &right) const
{
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	if(right)
	{
		const VALUETYPE *left(value);
		VALUETYPE *dest(result.value);

		gzUInt32 i(SIZE);
		
		VALUETYPE factor=1/right;

		if(factor!=0)
		{
			while(i)
			{
				*dest=*left*factor;
				++left;
				++dest;
				--i;
			}

			if(factor>0)
			{
				result.min=min*factor;
				result.max=min*factor;
			}
			else
			{
				result.max=min*factor;
				result.min=min*factor;
			}
		}
		else
		{
			while(i)
			{
				*dest=*left/right;
				++left;
				++dest;
				--i;
			}

			if(right>=0)
			{
				result.min=min/right;
				result.max=min/right;
			}
			else
			{
				result.max=min/right;
				result.min=min/right;
			}
		}
	}
	else
		throwFatalTemplateError("gzSpatialCoordinate::/ division by zero");

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::setZeroTo(const VALUETYPE &val)
{
	VALUETYPE *left(value);

	gzUInt32 i(SIZE);

	min=max=val;

	while(i)
	{
		if(!*left)
			*left=val;
		else
		{

			if(*left>max)
				max=*left;
			if(*left<min)
				min=*left;
		}

		++left;
		--i;
	}
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::init(const VALUETYPE &value)
{
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> feature;

	VALUETYPE *dest(feature.value);

	gzUInt32 i(SIZE);

	while(i)
	{
		*dest=value;
		++dest;
		--i;
	}

	feature.min=feature.max=value;

	return feature;
}

/*
template <> inline gzSpatialCoordinate<8,gzFloat> gzSpatialCoordinate<8,gzFloat>::init(const gzFloat &value)
{
	gzSpatialCoordinate<8,gzFloat> feature;

	if(value==0.0f)
		memset(feature.value,0,8*sizeof(gzFloat));
	else
	{
		gzFloat *dest(feature.value);

		gzUInt32 i(8);

		while(i)
		{
			*dest=value;
			++dest;
			--i;
		}
	}

	return feature;
}
*/

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::minimum(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &a,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &b)
{
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *left(a.value);
	const VALUETYPE *right(b.value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	result.min=result.max=gzMin(*left,*right);

	while(i)
	{
		*dest=gzMin(*left,*right); 

		if(*dest>result.max)
			result.max=*dest;

		if(*dest<result.min)
			result.min=*dest;

		++left;
		++right;
		++dest;
		--i;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline VALUETYPE gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::sumDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &_min,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &_max) const
{
	VALUETYPE sum(0);

	const VALUETYPE *p_min(_min.value);
	const VALUETYPE *p_max(_max.value);
	const VALUETYPE *p_pos(value);

	gzUInt32 i(SIZE);

	while(i)
	{
		if(*p_pos<*p_min)
			sum+=(*p_min-*p_pos);
		else if(*p_pos>*p_max)
			sum+=(*p_pos-*p_max);

		++p_pos;
		++p_min;
		++p_max;

		--i;
	}

	return sum;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline VALUETYPE gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::sumDistance(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &right) const
{
	VALUETYPE sum(0);

	const VALUETYPE *p_right(right.value);
	const VALUETYPE *p_pos(value);

	gzUInt32 i(SIZE);

	while(i)
	{
		sum+=gzAbs(*p_right-*p_pos);
		
		++p_pos;
		++p_right;

		--i;
	}

	return sum;
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::maximum(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &a,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &b)
{
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> result;

	const VALUETYPE *left(a.value);
	const VALUETYPE *right(b.value);
	VALUETYPE *dest(result.value);

	gzUInt32 i(SIZE);

	result.min=result.max=gzMax(*left,*right);

	while(i)
	{
		*dest=gzMax(*left,*right); 

		if(*dest>result.max)
			result.max=*dest;

		if(*dest<result.min)
			result.min=*dest;

		++left;
		++right;
		++dest;
		--i;
	}

	return result;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzUInt32 gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(gzUInt32 index)
{
	gzUInt32 mix(index);

	for(gzUInt32 i=0;i<SIZE-1;i++)
		mix=DIVS*mix+index;

	return mix;
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzUInt32 gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(const gzUInt32 * index)
{
	gzUInt32 mix(0);

	for(gzUInt32 i=0;i<SIZE;i++)
		mix=DIVS*mix+index[i];

	return mix;
}


template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzUInt32 gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::size()
{
	gzUInt32 result(DIVS);

	for(gzUInt32 i=0;i<SIZE-1;i++)
		result=result*DIVS;

	return result;
}

/*

// Add this kind of accel to your code

template <>  inline gzUInt32 gzSpatialCoordinate<13,gzDouble,2>::size()
{
	return 8192;
}

*/

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzVoid gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::calcIndex(gzUInt32 *index ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &pos ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &step)
{
	for(gzUInt32 i=0;i<SIZE;i++)
		index[i]=(gzUInt32)(pos.value[i]/step.value[i]);
}

template <gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS>  inline gzBool gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::compareIndex(gzUInt32 *index ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &pos ,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &step)
{
	for(gzUInt32 i=0;i<SIZE;i++)
	{
		if(index[i]!=(gzUInt32)(pos.value[i]/step.value[i]))
			return FALSE;
	}

	return TRUE;
}



//******************************************************************************
// Class	: gzMultiSpatial
//									
// Purpose  : Template for spatial located data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050222	Created 
//									
//******************************************************************************
template <class T,gzUInt32 SIZE,class VALUETYPE=DEFAULT_VALUETYPE,gzUInt32 DIVS=DEFAULT_DIVS> class gzMultiSpatial
{
public:

	gzMultiSpatial(	const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & position_1	= (VALUETYPE)0,
					const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & position_2	= (VALUETYPE)1,
					gzUInt32 splitItems=0,
					gzUInt32 minItemLevel=0,
					const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & minStepping = (VALUETYPE)0
					);

	~gzMultiSpatial();
    
    typedef  gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> Spatial;

	gzVoid		insert(const Spatial &position,const T &data,const Spatial &delta=Spatial::ZERO);

	gzBool		nearCandidate(const Spatial &position,T &data,Spatial *pos=nullptr,Spatial *delta=nullptr);

	gzUInt32	entries() const;

	gzUInt32	getMaxItemLevel() const;

	gzVoid		clear();

	gzVoid		clearData();

	gzVoid		setSplitItems(gzUInt32 items=0);

private:

	gzVoid		insert(gzUInt32 level,const Spatial &position,const T &data,const Spatial &delta);

	friend class gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>;
	//friend class gzMultiSpatialIntersectIterator<T,SIZE,VALUETYPE>;

	class _item;

	class _holder
	{
	public:

		_holder(const Spatial &min , const Spatial &max,_holder *parent):m_subspace(NULL),m_parent(parent),m_next(0),m_max(max),m_min(min)
		{
			m_itemList.reuseLinks(TRUE);
		}

		~_holder()
		{
			if(m_subspace)
			{
				for(gzUInt32 i=m_firstIndex;i<=m_lastIndex;i++)
					if(m_subspace[i])
						delete m_subspace[i];

				delete [] m_subspace;
			}

			m_itemList.clearAndDestroy();
		}

		gzVoid clearData()
		{
			if(m_subspace)
			{
				for(gzUInt32 i=m_firstIndex;i<=m_lastIndex;i++)
					if(m_subspace[i])
						m_subspace[i]->clearData();
			}

			m_itemList.clearAndDestroy();
		}

		gzVoid createSubspace()
		{
			if(!m_subspace)
			{
				gzUInt32 size=Spatial::size();
				m_firstIndex=m_lastIndex=0;
				m_subspace=new _holder *[size];
				memset(m_subspace,0,size*sizeof(_holder *));
			}
		}

		gzList<_item>								m_itemList;
		_holder **									m_subspace;
		_holder *									m_parent;
		gzUInt32									m_next;
		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>	m_max;
		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>	m_min;
		gzUInt32									m_firstIndex;
		gzUInt32									m_lastIndex;
	};

	class _item
	{
	public:

		T											m_data;
		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>	m_position;
		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>	m_delta;
		gzBool										m_gotDelta;
	};

	_holder *	m_space;

	Spatial		m_minPosition;

	Spatial		m_stepping;

	Spatial		m_minStepping;

	gzUInt32	m_splitItems;

	gzUInt32	m_minItemLevel;

	gzUInt32	m_entries;

	gzUInt32	m_maxItemLevel;

	gzUInt32	m_maxBucketCount;
};

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::nearCandidate(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &position,T &data,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *pos,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *delta)
{
	if(!m_entries)
		return FALSE;

	if(!m_space)			// Probably an error situation
		return FALSE;

	_holder *holder=m_space;

	gzUInt32 mixIndex;
	gzUInt32 index[SIZE];

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> stepping=m_stepping;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> minPosition=m_minPosition;

	gzBool cont(TRUE);

	gzList<_item>	items;

	while(TRUE)
	{
		// Add item from top list;

		items+=holder->m_itemList;

		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::calcIndex(index,position-minPosition,stepping);

		minPosition=minPosition+stepping*index;

		stepping=stepping/DIVS;

		mixIndex=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(index);

		if(holder->m_subspace)
			holder=holder->m_subspace[mixIndex];
		else
			cont=FALSE;

		if(!holder)
			cont=FALSE;

		if(!cont)
		{

			if(!items.entries())
				return FALSE;

			_item *bestItem(NULL),*item;

			VALUETYPE	bestDistance,dist;

			gzListIterator<_item>	iterator(items);

			while((item=iterator()))
			{
				if(!bestItem)
				{
					bestItem=item;
					bestDistance=item->m_position.magDistance(position);
				}
				else
				{
					dist=item->m_position.magDistance(position);

					if(dist<bestDistance)
					{
						bestItem=item;
						bestDistance=dist;
					}
				}
			}

			data=bestItem->m_data;

			if(pos)
				*pos=bestItem->m_position;

			if(delta)
				*delta=bestItem->m_delta;

			return TRUE;
		}
	}

	return FALSE;
}


template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::gzMultiSpatial(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& position_1 , const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& position_2,gzUInt32 splitItems,gzUInt32 minItemLevel,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> & minStepping)
{
	m_minPosition=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::minimum(position_1,position_2);

	m_stepping=(gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::maximum(position_1,position_2)-m_minPosition)/(VALUETYPE)DIVS;

	m_minStepping=minStepping;

	m_stepping.setZeroTo(1);

	m_splitItems=splitItems;

	m_space=nullptr;

	m_entries=0;

	m_minItemLevel=minItemLevel;

	m_maxItemLevel=0;

	m_maxBucketCount=0;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::setSplitItems(gzUInt32 items)
{
	m_splitItems=items;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::~gzMultiSpatial()
{
	if(m_space)
		delete m_space;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::clear()
{
	if(m_space)
		delete m_space;

	m_space=nullptr;
	m_entries=0;
	m_maxItemLevel=0;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid  gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::clearData()
{
	if(m_space)
		m_space->clearData();
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzUInt32 gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::entries() const
{
	return m_entries;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzUInt32 gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::getMaxItemLevel() const
{
	return m_maxItemLevel;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::insert(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &position,const T &data,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &delta)
{
	insert(0,position,data,delta);
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::insert(gzUInt32 level,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &position,const T &data,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> &delta)
{
	if(position+delta>=m_minPosition+m_stepping*(VALUETYPE)DIVS) // We are located outside max extent. Need to rebuild tree
	{
		_holder *old=m_space;

		gzUInt32 index=(DIVS-1)/2;

		gzUInt32 mixIndex=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(index);

		m_stepping=m_stepping*(VALUETYPE)DIVS;
		m_minPosition=m_minPosition-m_stepping*(VALUETYPE)index;

		m_space=new _holder(m_minPosition,m_minPosition+m_stepping*(VALUETYPE)DIVS,NULL);

		if(old)
		{
			m_space->createSubspace();
			m_space->m_subspace[mixIndex]=old;
			m_space->m_firstIndex=mixIndex;
			m_space->m_lastIndex=mixIndex;
			old->m_parent=m_space;
		}

		insert(level+1,position,data,delta);
		return;
	}

	if(	position-delta<m_minPosition)
	{
		_holder *old=m_space;
		gzUInt32 index=DIVS/2;
		gzUInt32 mixIndex=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(index);
		
		m_stepping=m_stepping*(VALUETYPE)DIVS;
		m_minPosition=m_minPosition-m_stepping*(VALUETYPE)index;

		m_space=new _holder(m_minPosition,m_minPosition+m_stepping*(VALUETYPE)DIVS,NULL);

		if(old)
		{
			m_space->createSubspace();
			m_space->m_subspace[mixIndex]=old;
			m_space->m_firstIndex=mixIndex;
			m_space->m_lastIndex=mixIndex;
			old->m_parent=m_space;
		}
	
		insert(level+1,position,data,delta);
		return;
	}
	

	gzUInt32 index[SIZE];

	if(!m_space)
		memset(index,0,SIZE*sizeof(gzUInt32));
	
	_holder *holder=m_space,*parent=nullptr;

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> stepping=m_stepping,nextStepping;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> minPosition=m_minPosition;

	while(holder)
	{
		++level;

		gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::calcIndex(index,position-delta-minPosition,stepping);

		if(!gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::compareIndex(index,position+delta-minPosition,stepping))
			break;

		if(((holder->m_itemList.entries()>m_splitItems)||(level<=m_minItemLevel)) && (stepping>m_minStepping))	// go to subchild
		{
			nextStepping=stepping/(VALUETYPE)DIVS;

			if(nextStepping.isZero())
				break;

			minPosition=minPosition+stepping*index;

			stepping=nextStepping;

			gzUInt32 mixIndex=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(index);

			if(!holder->m_subspace)
			{
				holder->createSubspace();
				holder->m_firstIndex=mixIndex;
				holder->m_lastIndex=mixIndex;
			}

			parent=holder;
			holder=holder->m_subspace[mixIndex];

			continue;
		}
		else
			break;
	}

	if(level>m_maxItemLevel)
		m_maxItemLevel=level;

	if(!holder)
	{
		gzUInt32 mixIndex=gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::mixIndex(index);

		holder=new _holder(minPosition,minPosition+stepping*(VALUETYPE)DIVS,parent);

		if(!parent)
			m_space=holder;
		else
		{
			if(parent->m_firstIndex>mixIndex)		// New Item ahead of first pos
			{
				holder->m_next=parent->m_firstIndex;
				parent->m_firstIndex=mixIndex;
			}
			else if(parent->m_lastIndex<mixIndex)	// New item after last pos
			{
				parent->m_subspace[parent->m_lastIndex]->m_next=mixIndex;
				parent->m_lastIndex=mixIndex;
			}
			else if(parent->m_firstIndex!=mixIndex)	// Item in between. Find prev possible item
			{
				gzUInt32 prev(0);
				gzUInt32 sub_index=parent->m_firstIndex;

				while(sub_index <mixIndex)
				{
					prev= sub_index;
					sub_index =parent->m_subspace[sub_index]->m_next;
				}

				holder->m_next=parent->m_subspace[prev]->m_next;
				parent->m_subspace[prev]->m_next=mixIndex;
			}

			parent->m_subspace[mixIndex]=holder;
		}
	}

	// Insert item

	_item *item=new _item;

	holder->m_itemList.insert(item);

	m_maxBucketCount=gzMax(m_maxBucketCount,holder->m_itemList.entries());

	item->m_data=data;
	item->m_position=position;
	item->m_delta=delta;
	item->m_gotDelta=delta > gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>::init(0);

	++m_entries;
}


//******************************************************************************
// Class	: gzMultiSpatialIterator
//									
// Purpose  : Box iterator for spatial located data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050222	Created 
//									
//******************************************************************************
template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> class gzMultiSpatialIterator
{
public:

	gzMultiSpatialIterator(gzMultiSpatial<T,SIZE,VALUETYPE,DIVS> &owner,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& position=0.0f , const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& delta=FLT_MAX);

	~gzMultiSpatialIterator();

	gzBool operator()(T &data,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *pos=nullptr,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *delta=nullptr);

	gzVoid remove();

	gzVoid setDelta(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& delta);

	gzVoid setMaxSum(const VALUETYPE &maxSum);

	gzVoid useMaxSum(gzBool on=FALSE);

private:

	gzMultiSpatial<T,SIZE,VALUETYPE,DIVS> &									m_owner;

	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>								m_position;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>								m_delta;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>								m_d_min;
	gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>								m_d_max;

	

	
	gzListIterator<typename gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::_item>	m_iterator;
	typename gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::_holder *				m_currentHolder;
	gzBool																	m_validIterator;
	VALUETYPE																m_max_sum;
	gzBool																	m_useMaxSum;

	
};

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::gzMultiSpatialIterator(gzMultiSpatial<T,SIZE,VALUETYPE,DIVS> &owner,const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& position , const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& delta)
		:m_owner(owner),
		m_position(position),
		m_delta(delta),
		m_d_min(position-delta),
		m_d_max(position+delta),
		m_iterator(NULL),
		m_currentHolder(m_owner.m_space),
		m_validIterator(FALSE),
		m_max_sum(0),
		m_useMaxSum(FALSE)
{
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::setDelta(const gzSpatialCoordinate<SIZE,VALUETYPE,DIVS>& delta)
{
	m_d_min=m_position-delta;
	m_d_max=m_position+delta;
	//m_validIterator=FALSE;	// Let it finnish without recalc iterator
}


template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::~gzMultiSpatialIterator()
{
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::setMaxSum(const VALUETYPE &maxSum)
{
	m_max_sum=maxSum;
	m_useMaxSum=TRUE;
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::useMaxSum(gzBool on)
{
	m_useMaxSum=on;
}


template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzVoid gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::remove()
{
	if(m_validIterator)
	{
		delete m_iterator.remove();
		--m_owner.m_entries;
	}
}

template <class T,gzUInt32 SIZE,class VALUETYPE,gzUInt32 DIVS> inline gzBool gzMultiSpatialIterator<T,SIZE,VALUETYPE,DIVS>::operator()(T &data,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *pos,gzSpatialCoordinate<SIZE,VALUETYPE,DIVS> *delta)
{
	if(!m_currentHolder)		// Assume a valid holder
		return FALSE;

	gzBool isValid;

	typename gzMultiSpatial<T,SIZE,VALUETYPE,DIVS>::_item *item;

	while(TRUE)
	{
		// Check to see if holder is valid first time

		if(!m_validIterator)
		{
			isValid=TRUE;

			if(!m_useMaxSum)
			{
				if( m_currentHolder->m_max		<= m_d_min ) // any item is left of us
					isValid=FALSE;
				else if( m_currentHolder->m_min >= m_d_max ) // any item is right of us
					isValid=FALSE;
			}
			else
			{
				if(m_position.sumDistance(m_currentHolder->m_min, m_currentHolder->m_max)>m_max_sum)
					isValid=FALSE;
			}

			if(!isValid)
			{
				// Go to next neighbour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						if(!m_useMaxSum)
						{
							if( m_currentHolder->m_max	<= m_d_min ) // any item is left of us
								continue;
						
							if( m_currentHolder->m_min	>= m_d_max ) // any item is right of us
								continue;
						}
						else
						{
							if(m_position.sumDistance(m_currentHolder->m_min, m_currentHolder->m_max)>m_max_sum)
								continue;
						}

						break;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}

			// Set up valid iterator for holder

			m_validIterator=TRUE;
			m_iterator.setList(m_currentHolder->m_itemList);
		}

		// Iterate over list for a valid holder

		item=m_iterator();

		if(!item)		// End of list
		{
			// Clean up
			m_validIterator=FALSE;

			// go to first sibling

			if(m_currentHolder->m_subspace)
			{
				// Select first child
				m_currentHolder=m_currentHolder->m_subspace[m_currentHolder->m_firstIndex];
			}
			else
			{
				// go to next neighour

				while(TRUE)
				{
					if(!m_currentHolder->m_parent)	// check if we hit top
					{
						return FALSE;
					}

					
					if(m_currentHolder->m_next)
					{
						m_currentHolder=m_currentHolder->m_parent->m_subspace[m_currentHolder->m_next];

						if(!m_useMaxSum)
						{
							if( m_currentHolder->m_max	<= m_d_min ) // any item is left of us
								continue;
						
							if( m_currentHolder->m_min	>= m_d_max ) // any item is right of us
								continue;
						}
						else
						{
							if(m_position.sumDistance(m_currentHolder->m_min, m_currentHolder->m_max)>m_max_sum)
								continue;
						}

						break;
					}

					// We have no neighbour; check parent neighbour
					m_currentHolder=m_currentHolder->m_parent;
				}

				// we have a new holder

				continue;
			}
		}
		else	// Check to se if valid
		{
			if(!m_useMaxSum)
			{
				if(item->m_gotDelta)
				{	
					if( !item->m_position.intersect(m_d_min-item->m_delta,m_d_max+item->m_delta) )
						continue;
				}
				else 
				{
					if( !item->m_position.intersect(m_d_min,m_d_max) )
						continue;
				}
			}
			else
			{
				if(m_position.sumDistance(item->m_position)>m_max_sum)
					continue;
			}



			// We have an intersection

			if(pos)
				*pos=item->m_position;

			if(delta)
				*delta=item->m_delta;

			data=item->m_data;

			return TRUE;
		}
	} 
}

#endif //__GZ_MULTI_SPATIAL_H__
