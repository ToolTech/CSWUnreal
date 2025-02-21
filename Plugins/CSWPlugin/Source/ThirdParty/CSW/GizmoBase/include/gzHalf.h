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
// File			: gzHalf.h
// Module		: gzBase
// Description	: Class definition of 16 bit floating point type
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.223
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
#ifndef __GZ_HALF_H__
#define __GZ_HALF_H__

#include "gzBasicTypes.h"

class GZ_BASE_EXPORT gzHalf
{
public:

    gzHalf ();			
    gzHalf (const gzFloat& f);

    operator	gzFloat () const;

    gzHalf		operator - () const;

    gzHalf &	operator = (const gzHalf&  h);
    gzHalf &	operator = (const gzFloat& f);

    gzHalf &	operator += (const gzHalf&  h);
    gzHalf &	operator += (const gzFloat& f);

    gzHalf &	operator -= (const gzHalf&  h);
    gzHalf &	operator -= (const gzFloat& f);

    gzHalf &	operator *= (const gzHalf&  h);
    gzHalf &	operator *= (const gzFloat& f);

    gzHalf &	operator /= (const gzHalf&  h);
    gzHalf &	operator /= (const gzFloat& f);


	gzHalf		round (gzUInt32 n)	const;

    gzBool		isFinite ()			const;
    gzBool		isNormalized ()		const;
    gzBool		isDenormalized ()	const;
    gzBool		isZero ()			const;
    gzBool		isNan ()			const;
    gzBool		isInfinity ()		const;
    gzBool		isNegative ()		const;


    static gzHalf	posInf ();
    static gzHalf	negInf ();
    static gzHalf	qNan ();
    static gzHalf	sNan ();

    gzUInt16	bits ()				const;
    void		setBits (gzUInt16 bits);

public:

    union uif
    {
		gzUInt32	i;
		gzFloat		f;
    };

private:
friend class LUTInitializer;

    gzUInt16	_h;	// internal val

    static gzInt16	convert (gzInt32 i);
    static gzFloat	overflow ();

	static uif		_floatLUT[1 << 16];
    static gzUInt16 _eLUT[1 << 9];
};



#define HALF_MIN		5.96046448e-08	// Smallest positive gzHalf
#define HALF_NRM_MIN	6.10351562e-05	// Smallest positive normalized gzHalf
#define HALF_MAX		65504.0			// Largest positive gzHalf
#define HALF_EPSILON	0.00097656		// Smallest positive e for which
										// gzHalf (1.0 + e) != gzHalf (1.0)
#define HALF_MANT_DIG	11				// Number of digits in mantissa
										// (significand + hidden leading 1)
#define HALF_DIG		2				// Number of base 10 digits that
										// can be represented without change
#define HALF_RADIX		2				// Base of the exponent
#define HALF_MIN_EXP	-13				// Minimum negative integer such that
										// HALF_RADIX raised to the power of
										// one less than that integer is a
										// normalized gzHalf
#define HALF_MAX_EXP	16				// Maximum positive integer such that
										// HALF_RADIX raised to the power of
										// one less than that integer is a
										// normalized gzHalf
#define HALF_MIN_10_EXP	-4				// Minimum positive integer such
										// that 10 raised to that power is
										// a normalized gzHalf
#define HALF_MAX_10_EXP	4				// Maximum positive integer such
										// that 10 raised to that power is
										// a normalized gzHalf

inline gzHalf::gzHalf ():_h(0)
{
}


inline gzHalf::gzHalf (const gzFloat& f)
{
    if (f == 0)
    {
		_h = 0;
    }
    else
    {
		uif x;

		x.f = f;

		gzInt32 e = (x.i >> 23) & 0x000001ff;

		e = _eLUT[e];

		if (e)
		{
			_h = (gzUInt16)(e + (((x.i & 0x007fffff) + 0x00001000) >> 13));
		}
		else
		{
		    _h = convert (x.i);
		}
    }
}

inline gzHalf::operator gzFloat () const
{
    return _floatLUT[_h].f;
}

inline gzHalf gzHalf::round (gzUInt32 n) const
{
    if (n >= 10)
		return *this;

    gzUInt16 s = _h & 0x8000;
    gzUInt16 e = _h & 0x7fff;

    e >>= 9 - n;
    e  += e & 1;
    e <<= 9 - n;

    if (e >= 0x7c00)
    {
		e = _h;
		e >>= 10 - n;
		e <<= 10 - n;
    }

    gzHalf h;
    h._h = s | e;

    return h;
}

inline gzHalf gzHalf::operator - () const
{
    gzHalf h;
    h._h = _h ^ 0x8000;
    return h;
}


inline gzHalf & gzHalf::operator = (const gzHalf& h)
{
    _h = h._h;
    return *this;
}

inline gzHalf &gzHalf::operator = (const gzFloat& f)
{
    *this = gzHalf (f);
    return *this;
}


inline gzHalf &gzHalf::operator += (const gzHalf& h)
{
    *this = gzHalf (gzFloat (*this) + gzFloat (h));
    return *this;
}

inline gzHalf &gzHalf::operator += (const gzFloat& f)
{
    *this = gzHalf (gzFloat (*this) + f);
    return *this;
}

inline gzHalf &gzHalf::operator -= (const gzHalf& h)
{
    *this = gzHalf (gzFloat (*this) - gzFloat (h));
    return *this;
}

inline gzHalf &gzHalf::operator -= (const gzFloat& f)
{
    *this = gzHalf (gzFloat (*this) - f);
    return *this;
}

inline gzHalf &gzHalf::operator *= (const gzHalf& h)
{
    *this = gzHalf (gzFloat (*this) * gzFloat (h));
    return *this;
}

inline gzHalf &gzHalf::operator *= (const gzFloat& f)
{
    *this = gzHalf (gzFloat (*this) * f);
    return *this;
}

inline gzHalf &gzHalf::operator /= (const gzHalf& h)
{
    *this = gzHalf (gzFloat (*this) / gzFloat (h));
    return *this;
}

inline gzHalf &gzHalf::operator /= (const gzFloat& f)
{
    *this = gzHalf (gzFloat (*this) / f);
    return *this;
}

inline gzBool gzHalf::isFinite () const
{
    gzUInt16 e = (_h >> 10) & 0x001f;
    return e < 31;
}

inline gzBool gzHalf::isNormalized () const
{
    gzUInt16 e = (_h >> 10) & 0x001f;
    return e > 0 && e < 31;
}

inline gzBool gzHalf::isDenormalized () const
{
    gzUInt16 e = (_h >> 10) & 0x001f;
    gzUInt16 m =  _h & 0x3ff;
    return e == 0 && m != 0;
}

inline gzBool gzHalf::isZero () const
{
    return (_h & 0x7fff) == 0;
}

inline gzBool gzHalf::isNan () const
{
    gzUInt16 e = (_h >> 10) & 0x001f;
    gzUInt16 m =  _h & 0x3ff;
    return e == 31 && m != 0;
}

inline gzBool gzHalf::isInfinity () const
{
    gzUInt16 e = (_h >> 10) & 0x001f;
    gzUInt16 m =  _h & 0x3ff;
    return e == 31 && m == 0;
}

inline gzBool gzHalf::isNegative () const
{
    return (_h & 0x8000) != 0;
}

inline gzHalf gzHalf::posInf ()
{
    gzHalf h;
    h._h = 0x7c00;
    return h;
}

inline gzHalf gzHalf::negInf ()
{
    gzHalf h;
    h._h = 0xfc00;
    return h;
}

inline gzHalf gzHalf::qNan ()
{
    gzHalf h;
    h._h = 0x7fff;
    return h;
}

inline gzHalf gzHalf::sNan ()
{
    gzHalf h;
    h._h = 0x7dff;
    return h;
}

inline gzUInt16 gzHalf::bits () const
{
    return _h;
}

inline void gzHalf::setBits (gzUInt16 bits)
{
    _h = bits;
}

#endif //__GZ_HALF_H__

