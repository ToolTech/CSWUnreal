//******************************************************************************
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
// File			: gzArithmetic.h
// Module		: gzBase
// Description	: Class definition of Atrimetics used.
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.224
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
// AMO	180919	Created file 	
//
//******************************************************************************

#ifndef __GZ_ARITHMETIC_H__
#define __GZ_ARITHMETIC_H__

#include "gzBasicTypes.h"

/*!	\file 
	\brief Arithmetic utilites 

	Used Arithmetic is double and float
*/

// Forward prototyp
GZ_BASE_EXPORT gzVoid throwFatalTemplateError(const char* string);

// ******************** class definitions ***************************************

template <class T> class  gzAritmetic_
{
public:

	static T epsilon();
	static T maxval();
	static T minval();
};

// -------------------------- gzFloat ------------------------------------------

typedef gzAritmetic_<gzFloat>	gzAritmetic;

template <> inline gzFloat gzAritmetic::epsilon()
{
	return	20 * FLT_EPSILON;		// Relative precision
}

template <> inline gzFloat gzAritmetic::maxval()
{
	return	FLT_MAX;
}

template <> inline gzFloat gzAritmetic::minval()
{
	return	FLT_MIN;
}

// ------------------------ gzDouble ------------------------------------------

typedef gzAritmetic_<gzDouble>	gzAritmeticD;

template <> inline gzDouble gzAritmeticD::epsilon()
{
	return	20 * DBL_EPSILON;		// Relative precision
}

template <> inline gzDouble gzAritmeticD::maxval()
{
	return	DBL_MAX;
}

template <> inline gzDouble gzAritmeticD::minval()
{
	return	DBL_MIN;
}

// --------- Common used math functions -----------------

// ---------------------- sin ---------------------------

template <class T> inline T sin(const T& value)
{
	return ::sin(value);
}

template <> inline gzDouble sin(const gzDouble& value)
{
	return ::sin(value);
}

template <> inline gzFloat sin(const gzFloat& value)
{
	return ::sinf(value);
}

// ---------------------- cos ---------------------------

template <class T> inline T cos(const T& value)
{
	return ::cos(value);
}

template <> inline gzDouble cos(const gzDouble& value)
{
	return ::cos(value);
}

template <> inline gzFloat cos(const gzFloat& value)
{
	return ::cosf(value);
}

// ---------------------- tan ---------------------------

template <class T> inline T tan(const T& value)
{
	return ::tan(value);
}

template <> inline gzDouble tan(const gzDouble& value)
{
	return ::tan(value);
}

template <> inline gzFloat tan(const gzFloat& value)
{
	return ::tanf(value);
}

// ---------------------- atan2 ---------------------------

template <class T> inline T atan2(const T& y, const T& x)
{
	return ::atan2(y,x);
}

template <> inline gzDouble atan2(const gzDouble& y, const gzDouble& x)
{
	return ::atan2(y,x);
}

template <> inline gzFloat atan2(const gzFloat& y, const gzFloat& x)
{
	return ::atan2f(y,x);
}

// ---------------------- gzAbs ---------------------------

template <class T> inline T gzAbs(const T& value)
{
	return (value >= 0) ? value : -value;
}

// Branchless abs value

template <> inline gzFloat gzAbs(const gzFloat& val)
{

#if defined WIN32 && !defined WIN64 && !defined GZ_WIN64

	gzFloat output;

	__asm
	{
		mov         eax, val
		mov			eax, [eax]
		and eax, 7FFFFFFFh
		mov			output, eax
	}

	return (output);

#else
		
	union
	{
		gzInt32	l;
		gzFloat f;
	} u;

	u.f = val;
	u.l &= 0x7FFFFFFF;

	return u.f;

#endif

}

template <> inline gzDouble gzAbs(const gzDouble& val)
{
#if defined WIN32 && !defined WIN64  && !defined GZ_WIN64

	gzDouble output;

	__asm
	{
		mov         eax, val
		fld			qword ptr[eax]
		fabs
		fstp		output
	}
	return (output);

#else

	union
	{
		gzInt64	ll;
		gzDouble	d;
	} u;

	u.d = val;
	u.ll &= LLU(0x7FFFFFFFFFFFFFFF);

	return u.d;

#endif

}

// ---------------------- gzSqrt ---------------------------

template <class T> inline T gzSqrt(const T& a)
{
	return ::sqrt(a);
}

template <> inline gzFloat gzSqrt(const gzFloat& a)
{
	if (a < 0)
		throwFatalTemplateError("sqrt on negative number");

	return sqrtf(a);
}

template <> inline gzUInt32 gzSqrt(const gzUInt32& a)
{
	return (gzUInt32)sqrtf((gzFloat)a);
}

template <> inline gzDouble gzSqrt(const gzDouble& a)
{
	if (a < 0)
		throwFatalTemplateError("sqrt on negative number");

	return sqrt(a);
}

// ---------------------- gzSq2 ---------------------------

template <class T> inline T gzSq2(const T& a)
{
	return a * a;
}

// ---------------------- gzLog2 ---------------------------

template <class T> inline T gzLog2(const T& a)
{
	return log2(a);
}

template <> inline gzFloat gzLog2(const gzFloat& a)
{
	return log2f(a);
}

template <> inline gzUInt64 gzLog2(const gzUInt64& a)
{
	gzUInt64  k(0);
	gzUInt64 val(a);

	if (val > 0xFFFFFFFFull) { val >>= 32; k = 32; }
	if (val > 0x0000FFFFull) { val >>= 16; k |= 16;}
	if (val > 0x000000FFull) { val >>= 8;  k |= 8; }
	if (val > 0x0000000Full) { val >>= 4;  k |= 4; }
	if (val > 0x00000003ull) { val >>= 2;  k |= 2; }
	k |= (val & 2) >> 1;
	return k;
}

template <> inline gzUInt32 gzLog2(const gzUInt32& a)
{
	gzUInt32  k(0);
	gzUInt32 val(a);

	if (val > 0x0000FFFFu) { val >>= 16; k = 16; }
	if (val > 0x000000FFu) { val >>= 8;  k |= 8; }
	if (val > 0x0000000Fu) { val >>= 4;  k |= 4; }
	if (val > 0x00000003u) { val >>= 2;  k |= 2; }
	k |= (val & 2) >> 1;
	return k;
}


// -------------------- gzRound ------------------------
// maps to round function
// Round nearest away from zero

template <class T> inline T gzRound(const T& val)
{
	return (T)round(val);
}

template <> inline float gzRound(const float& x)
{
	union
	{
		float f;
		unsigned int w;
	} val;

	val.f = x;

	int sm_exp(((val.w & 0x7f800000) >> 23) - 127);

	if (sm_exp < 23)
	{
		if (sm_exp < 0)
		{
			val.w &= 0x80000000;
			if (sm_exp == -1)
				/*  +1.0 or -1.0. */
				val.w |= (127u << 23);
		}
		else
		{
			unsigned int exponent_mask(0x007fffff >> sm_exp);
			if ((val.w & exponent_mask) == 0)
				/* integral value. */
				return x;

			val.w += 0x00400000 >> sm_exp;
			val.w &= ~exponent_mask;
		}
	}
	else
	{
		if (sm_exp == 128)
			/* NaN or infinite. */
			return x + x;
		else
			return x;
	}
	return val.f;
}

template <> inline double gzRound(const double& x)
{
	union
	{
		double d;
		struct
		{
			unsigned long int lsw;
			unsigned long int msw;
		};

	} val;

	/*if (gzBigEndian())
		gzSwap(val.lsw, val.msw);*/

	val.msw = 0;
	val.lsw = 0;
	val.d = x;

	int sm_exp = (((val.msw & 0x7ff00000) >> 20) - 1023);

	if (sm_exp < 20)
	{
		if (sm_exp < 0)
		{
			val.msw &= 0x80000000;

			if (sm_exp == -1)
				/* +1.0 or -1.0. */
				val.msw |= (1023u << 20);
			val.lsw = 0;
		}
		else
		{
			unsigned int exponent_mask(0x000fffff >> sm_exp);
			if ((val.msw & exponent_mask) == 0 && val.lsw == 0)
				/* integral value. */
				return x;

			val.msw += 0x00080000 >> sm_exp;
			val.msw &= ~exponent_mask;
			val.lsw = 0;
		}
	}
	else if (sm_exp > 51)
	{
		if (sm_exp == 1024)
			/* NaN or infinite. */
			return x + x;
		else
			return x;
	}
	else
	{
		unsigned int exponent_mask(0xffffffff >> (sm_exp - 20));

		if ((val.lsw & exponent_mask) == 0)
			/* integral value. */
			return x;

		unsigned int tmp(val.lsw + (1 << (51 - sm_exp)));
		if (tmp < val.lsw)
			val.msw += 1;

		val.lsw = tmp;
		val.lsw &= ~exponent_mask;
	}

	/*if (gzBigEndian())
		gzSwap(val.lsw, val.msw);*/

	return val.d;
}

template <> inline long double gzRound(const long double& val)
{
	return roundl(val);
}


#endif // __GZ_ARITHMETIC_H__
