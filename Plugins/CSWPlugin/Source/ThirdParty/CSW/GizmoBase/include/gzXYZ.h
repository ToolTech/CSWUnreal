// *****************************************************************************
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
// File			: gzXYZ.h
// Module		: gzXYZ
// Description	: Class definition of XYZ templates
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.201
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020322	Created file 
//
// ******************************************************************************

#ifndef __GZ_XYZ_H__
#define __GZ_XYZ_H__

/*!	\file 
	\brief Templates for spatial data management

*/

#include "gzBasicTypes.h"

//******************************************************************************
// Class	: gzXY
//									
// Purpose  : Returns (x,y) pair of T
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020322	Created 
//									
//******************************************************************************
template <class T> class gzXY 
{
public:

	gzXY(T _x=0,T _y=0):x(_x),y(_y)		{};

	gzXY <T> operator *(const T &right)			const { return gzXY<T>(x*right,y*right); }

	gzXY <T> operator /(const T &right)			const { return gzXY<T>(x/right,y/right); }

	gzXY <T> operator +(const gzXY<T> &right)	const { return gzXY<T>(x+right.x,y+right.y); }

	gzXY <T> operator -(const gzXY<T> &right)	const { return gzXY<T>(x-right.x,y-right.y); }

	gzBool operator==(const gzXY<T> &right)		const { return (x==right.x)&&(y==right.y); }

	gzBool operator!=(const gzXY<T> &right)		const { return (x!=right.x)||(y!=right.y); }

	// Left without implementation so you need to imp if used for special class
	gzUInt32 hash() const;	

	// Public values

	T x,y;
};

// Some common pairs

typedef gzXY<gzUInt32>	gzUInt32XY;
typedef gzXY<gzInt32>	gzInt32XY;
typedef gzXY<gzFloat>	gzFloatXY;
typedef gzXY<gzDouble>	gzDoubleXY;
typedef gzXY<gzUInt16>	gzUInt16XY;
typedef gzXY<gzInt16>	gzInt16XY;
typedef gzXY<gzUInt8>	gzUInt8XY;
typedef gzXY<gzInt8>	gzInt8XY;

// Some HASH XY functions

template <> inline gzUInt32 gzXY<gzUInt32>::hash() const
{
	return (x<<8)+y;
}

template <> inline gzUInt32 gzXY<gzInt32>::hash() const
{
	return (x<<8)+y;
}

template <> inline gzUInt32 gzXY<gzFloat>::hash() const
{
	union
	{
		gzFloat f;
		gzUInt32 i;
	} conv;

	conv.f=x;
	gzUInt32 xi=conv.i;

	conv.f=y;
	gzUInt32 yi=conv.i;

	return (xi<<1)+yi;
}



//******************************************************************************
// Class	: gzXYZ
//									
// Purpose  : Returns (x,y,z) pair of T
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	020322	Created 
//									
//******************************************************************************
template <class T> class gzXYZ 
{
public:

	gzXYZ(T _x=0,T _y=0,T _z=0):x(_x),y(_y),z(_z)		{};

	gzXYZ <T> operator *(const T &right)		const	{ return gzXYZ<T>(x*right,y*right,z*right); }

	gzXYZ <T> operator /(const T &right)		const	{ return gzXYZ<T>(x/right,y/right,z/right); }

	gzXYZ <T> operator +(const gzXYZ<T> &right) const	{ return gzXYZ<T>(x+right.x,y+right.y,z+right.z); }

	gzXYZ <T> operator -(const gzXYZ<T> &right)	const	{ return gzXYZ<T>(x-right.x,y-right.y,z-right.z); }

	gzBool operator==(const gzXYZ<T> &right)	const	{ return (x==right.x) && (y==right.y) && (z==right.z); }

	gzBool operator!=(const gzXYZ<T> &right)	const	{ return (x!=right.x) || (y!=right.y) || (z!=right.z); }

	// Left without implementation so you need to imp if used for special class
	gzUInt32 hash() const;	

	// Public values

	T x,y,z;
};

template <> inline gzUInt32 gzXYZ<gzUInt32>::hash() const
{
	return (x << 8) + (y<<16) + z;
}

template <> inline gzUInt32 gzXYZ<gzInt32>::hash() const
{
	return (((gzUInt32)x) << 8) + (((gzUInt32)y) << 16) + ((gzUInt32)z);
}


// Some common pairs

typedef gzXYZ<gzUInt32>	gzUInt32XYZ;
typedef gzXYZ<gzInt32>	gzInt32XYZ;
typedef gzXYZ<gzFloat>	gzFloatXYZ;
typedef gzXYZ<gzDouble>	gzDoubleXYZ;
typedef gzXYZ<gzUInt16>	gzUInt16XYZ;
typedef gzXYZ<gzInt16>	gzInt16XYZ;
typedef gzXYZ<gzUInt8>	gzUInt8XYZ;
typedef gzXYZ<gzInt8>	gzInt8XYZ;



#endif // __GZ_XYZ_H__
