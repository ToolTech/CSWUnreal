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
// File			: gzFixed.h
// Module		: gzBase
// Description	: Class definition of Fixed 16.16 bit floating point type
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.306
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
// AMO	090401	Created file 	
//
//******************************************************************************
#ifndef __GZ_FIXED_H__
#define __GZ_FIXED_H__

#include "gzBasicTypes.h"

const gzFloat GZ_FIXED_DIV_FAC=1/65536.0f;
const gzFloat GZ_FIXED_MUL_FAC=65536.0f;

class GZ_BASE_EXPORT gzFixed
{
public:

    gzFixed ();			
    gzFixed (gzFloat f);
	explicit gzFixed (gzInt16 s);

    operator	gzFloat ()	const;

    gzFixed		operator - () const;

    gzFixed &	operator = (gzFixed  h);
	gzFixed &	operator = (gzInt16  s);
    gzFixed &	operator = (gzFloat f);

    gzFixed &	operator += (gzFixed  h);
	gzFixed &	operator += (gzInt16 s);
    gzFixed &	operator += (gzFloat f);

	gzFixed 	operator + (gzFixed  h);
	gzFixed 	operator + (gzInt16 s);
    gzFixed 	operator + (gzFloat f);

    gzFixed &	operator -= (gzFixed  h);
	gzFixed &	operator -= (gzInt16 s);
    gzFixed &	operator -= (gzFloat f);

    gzFixed 	operator - (gzFixed  h);
	gzFixed 	operator - (gzInt16 s);
    gzFixed 	operator - (gzFloat f);

	gzFixed &	operator *= (gzFixed  h);
	gzFixed &	operator *= (gzInt16 s);
    gzFixed &	operator *= (gzFloat f);

	gzFixed 	operator * (gzFixed  h);
	gzFixed 	operator * (gzInt16 s);
    gzFixed 	operator * (gzFloat f);

	gzFixed &	operator /= (gzFixed  h);
	gzFixed &	operator /= (gzInt16 s);
    gzFixed &	operator /= (gzFloat f);

	gzFixed 	operator / (gzFixed  h);
	gzFixed 	operator / (gzInt16 s);
    gzFixed 	operator / (gzFloat f);

    gzInt32	_h;		// internal val
};

inline gzFixed::gzFixed ()
{
}

inline gzFixed::gzFixed (gzFloat f)
{
	_h=(gzInt32)(GZ_FIXED_MUL_FAC*f);
}

inline gzFixed::gzFixed (gzInt16 s)
{
	_h=s<<16;
}

inline gzFixed::operator gzFloat () const
{
	return _h*GZ_FIXED_DIV_FAC;
}

inline gzFixed gzFixed::operator - () const
{
	gzFixed ret;
	ret._h=-_h;
	return ret;
}


inline gzFixed & gzFixed::operator = (gzFixed h)
{
	_h=h._h;
	return *this;
}

inline gzFixed &gzFixed::operator = (gzFloat f)
{
	_h=(gzInt32)(GZ_FIXED_MUL_FAC*f);
	return *this;
}

inline gzFixed &gzFixed::operator = (gzInt16 s)
{
	_h=s<<16;
	return *this;
}


inline gzFixed &gzFixed::operator += (gzFixed h)
{
	_h+=h._h;
	return *this;
}

inline gzFixed &gzFixed::operator += (gzFloat f)
{
	_h+=(gzInt32)(GZ_FIXED_MUL_FAC*f);
	return *this;
}

inline gzFixed &gzFixed::operator += (gzInt16 s)
{
	_h+=s<<16;
	return *this;
}

inline gzFixed gzFixed::operator + (gzFixed h)
{
	gzFixed ret;
	ret._h=_h+h._h;
	return ret;
}

inline gzFixed gzFixed::operator + (gzFloat f)
{
	gzFixed ret;
	ret._h=_h+(gzInt32)(GZ_FIXED_MUL_FAC*f);
	return ret;
}

inline gzFixed gzFixed::operator + (gzInt16 s)
{
	gzFixed ret;
	ret._h=_h+(s<<16);
	return ret;
}

inline gzFixed &gzFixed::operator -= (gzFixed h)
{
	_h-=h._h;
	return *this;
}

inline gzFixed &gzFixed::operator -= (gzFloat f)
{
	_h-=(gzInt32)(GZ_FIXED_MUL_FAC*f);
	return *this;
}

inline gzFixed &gzFixed::operator -= (gzInt16 s)
{
	_h-=s<<16;
	return *this;
}

inline gzFixed gzFixed::operator -(gzFixed h)
{
	gzFixed ret;
	ret._h=_h-h._h;
	return ret;
}

inline gzFixed gzFixed::operator -(gzFloat f)
{
	gzFixed ret;
	ret._h=_h-(gzInt32)(GZ_FIXED_MUL_FAC*f);
	return ret;
}

inline gzFixed gzFixed::operator -(gzInt16 s)
{
	gzFixed ret;
	ret._h=_h-(s<<16);
	return ret;
}

inline gzFixed &gzFixed::operator *= (gzFixed h)
{
	_h=(gzInt32)(((gzInt64)_h*h._h)>>16);
	return *this;
}

inline gzFixed &gzFixed::operator *= (gzFloat f)
{
	_h=(gzInt32)(_h*f);
	return *this;
}

inline gzFixed &gzFixed::operator *= (gzInt16 s)
{
	_h=_h*s;
	return *this;
}

inline gzFixed gzFixed::operator * (gzFixed h)
{
	gzFixed ret;
	ret._h=(gzInt32)(((gzInt64)_h*h._h)>>16);
	return ret;
}

inline gzFixed gzFixed::operator * (gzFloat f)
{
	gzFixed ret;
	ret._h=(gzInt32)(_h*f);
	return ret;
}

inline gzFixed gzFixed::operator * (gzInt16 s)
{
	gzFixed ret;
	ret._h=_h*s;
	return ret;
}

inline gzFixed &gzFixed::operator /= (gzFixed h)
{
	_h=(gzInt32)(((gzInt64)_h<<16)/h._h);
	return *this;
}

inline gzFixed &gzFixed::operator /= (gzFloat f)
{
	_h=(gzInt32)(_h/f);
	return *this;
}

inline gzFixed &gzFixed::operator /= (gzInt16 s)
{
	_h=_h/s;
	return *this;
}

inline gzFixed gzFixed::operator / (gzFixed h)
{
	gzFixed ret;
	ret._h=(gzInt32)(((gzInt64)_h<<16)/h._h);
	return ret;
}

inline gzFixed gzFixed::operator / (gzFloat f)
{
	gzFixed ret;
	ret._h=(gzInt32)(_h/(GZ_FIXED_MUL_FAC*f));
	return ret;
}

inline gzFixed gzFixed::operator / (gzInt16 s)
{
	gzFixed ret;
	ret._h=_h/s;
	return ret;
}

#endif //__GZ_FIXED_H__

