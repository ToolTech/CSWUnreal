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
// File			: gzGooble.h
// Module		: gzBase
// Description	: Class definition of XX bit floating point type
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.211
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
// AMO	211005	Created file 	                                (2.11.39)
// AMO	230119	Added trigonometric functions					(2.12.47)
//
//******************************************************************************
#ifndef __GZ_GOOBLE_H__
#define __GZ_GOOBLE_H__

#include "gzTemplates.h"
#include "gzSerialize.h"

typedef gzQWA_UByte						MantissaItem;				// Store mantissa data as Quad Word Aligned bytes
typedef gzDynamicArray<MantissaItem>	Mantissa;					// mantissa is a dynamic allocated storage

const gzUInt32	GZ_GOOBLE_DEFAULT_PRECISION_SLOTS = 8;				// approx 16 decimals accuracy (8 bytes)
const gzBool	GZ_GOOBLE_DEFAULT_THROW_INEXACT_RESULT = FALSE;		// dont throw inexact result exception by default

class gzGooble : public gzSerializeData
{
public:

	// ---- constructors ---------------

	GZ_BASE_EXPORT gzGooble();						// Default value zero

	GZ_BASE_EXPORT gzGooble(const gzDouble& val);
	GZ_BASE_EXPORT gzGooble(const gzUInt64& val);
	GZ_BASE_EXPORT gzGooble(const gzInt64& val);
	GZ_BASE_EXPORT gzGooble(const gzInt32& val);
	GZ_BASE_EXPORT gzGooble(const gzUInt32& val);

	// Exponent constructor
	GZ_BASE_EXPORT gzGooble(const gzDouble& val,const gzInt32& exponent);

	GZ_BASE_EXPORT gzGooble(const gzString& val);

	// --- cast ------------------------

	GZ_BASE_EXPORT operator gzDouble () const;
	GZ_BASE_EXPORT operator gzUInt64 () const;
	GZ_BASE_EXPORT operator gzInt64 () const;
	GZ_BASE_EXPORT operator gzUInt32 () const;
	GZ_BASE_EXPORT operator gzInt32 () const;

	GZ_BASE_EXPORT gzDouble toDouble() const;
	GZ_BASE_EXPORT gzUInt64 toUInt64() const;
	GZ_BASE_EXPORT gzInt64  toInt64() const;
	GZ_BASE_EXPORT gzUInt32 toUInt32() const;
	GZ_BASE_EXPORT gzInt32	toInt32() const;

	// ---- compare ---------

	GZ_BASE_EXPORT gzBool operator == (const gzGooble& right) const;
	GZ_BASE_EXPORT gzBool operator != (const gzGooble& right) const;

	// ---- Arithmetic ---------

	GZ_BASE_EXPORT gzGooble operator *(const gzGooble& right) const;
	GZ_BASE_EXPORT gzGooble operator /(const gzGooble& right) const;
	GZ_BASE_EXPORT gzGooble operator +(const gzGooble& right) const;
	GZ_BASE_EXPORT gzGooble operator -(const gzGooble& right) const;

	GZ_BASE_EXPORT gzGooble operator %(const gzGooble& right) const;

	GZ_BASE_EXPORT gzGooble operator -() const;

	// --- gzInt32 right--

	GZ_BASE_EXPORT gzGooble operator *(const gzInt32& right) const;
	GZ_BASE_EXPORT gzGooble operator /(const gzInt32& right) const;
	GZ_BASE_EXPORT gzGooble operator +(const gzInt32& right) const;
	GZ_BASE_EXPORT gzGooble operator -(const gzInt32& right) const;

	GZ_BASE_EXPORT gzGooble operator %(const gzInt32& right) const;

	// ------------------ Bitwise ------------------------

	GZ_BASE_EXPORT gzGooble operator ~() const;

	GZ_BASE_EXPORT gzBool operator >(const gzGooble& right) const;
	GZ_BASE_EXPORT gzBool operator <(const gzGooble& right) const;

	GZ_BASE_EXPORT gzBool operator >=(const gzGooble& right) const;
	GZ_BASE_EXPORT gzBool operator <=(const gzGooble& right) const;


	// ---- values -------------

	GZ_BASE_EXPORT gzGooble abs() const;							// Get absolute value
	GZ_BASE_EXPORT gzGooble trunc(const gzInt32 &slot=0) const;		// Get truncated integer or at slot (left part xxx) xxx.yyyy
	GZ_BASE_EXPORT gzGooble frac() const;							// Get fraction of value	(right part 0.yyyy) xxx.yyyy
	GZ_BASE_EXPORT gzGooble sign() const;							// Get sign +1 or -1 of value

	GZ_BASE_EXPORT gzGooble truncValid(const gzUInt32& extra=0) const;		// Get truncated integer with valid digits

	GZ_BASE_EXPORT gzGooble shifted(const gzInt32& steps) const;

	GZ_BASE_EXPORT gzBool rational(gzGooble& numerator, gzGooble& denominator, gzUInt32 iterations=10) const;	// returns TRUE if exact

	GZ_BASE_EXPORT gzGooble div(const gzGooble &right, gzGooble &R) const;		// Integer division and Rest

	GZ_BASE_EXPORT gzGooble gcd(const gzGooble& right) const;		// greatest common divisor

	// ---- standard math ------
	
	GZ_BASE_EXPORT gzGooble pow(const gzGooble &pow) const;			// x^pow

	GZ_BASE_EXPORT gzGooble pow_i(const gzInt32 &pow) const;		// x^pow
	GZ_BASE_EXPORT gzGooble root_i(const gzInt32 &pow) const;		// x^(1/pow)
	GZ_BASE_EXPORT gzGooble introot_i(const gzInt32& pow) const;	// integer= x^(1/pow)

	GZ_BASE_EXPORT gzGooble powmod_i(const gzGooble& pow,const gzGooble mod) const;	// x^(pow) % mod

	// ---- bit operations on instance -----

	GZ_BASE_EXPORT gzVoid shift(const gzInt32 &steps);

	GZ_BASE_EXPORT gzInt32 bitmax() const;
	GZ_BASE_EXPORT gzInt32 bitmin() const;
	GZ_BASE_EXPORT gzInt32 slotSize() const;						//Number of 8 bit slots in mantissa

	GZ_BASE_EXPORT gzInt32 evenbits(gzUInt32 minslot=0) const;
	GZ_BASE_EXPORT gzInt32 oddbits(gzUInt32 minslot = 0) const;
	GZ_BASE_EXPORT gzInt32 bitdiff(gzUInt32 minslot = 0) const;


	GZ_BASE_EXPORT gzVoid invert();

	GZ_BASE_EXPORT gzVoid increment();
	GZ_BASE_EXPORT gzVoid decrement();

	GZ_BASE_EXPORT gzInt32 compare(const gzGooble& right,gzInt8 &difference ) const;

	GZ_BASE_EXPORT gzGooble round() const;

	// --- Utilities -----------

	GZ_BASE_EXPORT gzVoid pack(gzBool changeExponent=FALSE);
	GZ_BASE_EXPORT gzVoid one();
	GZ_BASE_EXPORT gzVoid zero();
	GZ_BASE_EXPORT gzVoid neg();

	GZ_BASE_EXPORT gzUInt32 toAscii(gzSerializeAdapter* adapter, gzUInt32 base = 10, gzBool progress = FALSE) const;

	GZ_BASE_EXPORT gzString asString(gzUInt32 base = 10) const;

	GZ_BASE_EXPORT gzInt8 lastIntegerDigit() const;

	GZ_BASE_EXPORT gzUInt32 getValueSlots(const gzInt32& slot);

	// ---- Types --------------

	GZ_BASE_EXPORT gzBool isInteger() const;
	GZ_BASE_EXPORT gzBool isNull() const;
	GZ_BASE_EXPORT gzBool isOne() const;
	GZ_BASE_EXPORT gzBool isNeg() const;
	GZ_BASE_EXPORT gzBool isEven() const;

	GZ_BASE_EXPORT gzBool isDiv3() const;
	GZ_BASE_EXPORT gzBool isDiv5() const;

	
	// ---- Serialize ----------

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = NULL) const override;

	// ---- Properties ---------

	//! Max number of digits in division result
	GZ_STATIC_PROPERTY_EXPORT(gzUInt32, PrecisionSlots, GZ_BASE_EXPORT);	// 1 slot = 8 bits
	GZ_STATIC_PROPERTY_EXPORT(gzBool, ThrowInexactResult, GZ_BASE_EXPORT);

	// -------- Static constructs ----------

	GZ_BASE_EXPORT static gzGooble pow10_i(const gzInt32& pow10);					// 10^pow10
	GZ_BASE_EXPORT static gzGooble pow2_i(const gzInt32& pow2);						// 2^pow2

	GZ_BASE_EXPORT static gzGooble pow(const gzGooble &x,const gzGooble &y);		// x^y
	GZ_BASE_EXPORT static gzGooble pow_i(const gzGooble& x, const gzInt32& pow);	// x^pow

	GZ_BASE_EXPORT static gzGooble root_i(const gzGooble& x, const gzInt32& pow);	// x^(1/pow)
	GZ_BASE_EXPORT static gzGooble introot_i(const gzGooble& x,const gzInt32& pow);	// integer= x^(1/pow)

	GZ_BASE_EXPORT static gzGooble fact(const gzInt32& fac);						// x!

	GZ_BASE_EXPORT static gzGooble exp(const gzGooble &x);							// e^x
	GZ_BASE_EXPORT static gzGooble ln(const gzGooble &x);							// ln(x)

	GZ_BASE_EXPORT static gzGooble sin(const gzGooble& x);							// sin(x)
	GZ_BASE_EXPORT static gzGooble cos(const gzGooble& x);							// cos(x)
	GZ_BASE_EXPORT static gzGooble tan(const gzGooble& x);							// tan(x)

	GZ_BASE_EXPORT static gzGooble arcsin(const gzGooble& x);						// arcsin(x)
	GZ_BASE_EXPORT static gzGooble arccos(const gzGooble& x);						// arccos(x)
	GZ_BASE_EXPORT static gzGooble arctan(const gzGooble& x);						// arctan(x)

	GZ_BASE_EXPORT static gzGooble pi();											// PI with required precision

	GZ_BASE_EXPORT static gzGooble fromAscii(gzSerializeAdapter *adapter,gzUInt32 base=10);

	GZ_BASE_EXPORT static gzUInt32 setDecimalPrecision(gzUInt32 digits);

	// ----------------------- Private : Expert use ---------------------------------------

	GZ_BASE_EXPORT gzVoid init();

	// Allowed to be accessed

	gzBool		m_signed;
	gzInt32		m_exponent;

	Mantissa	m_mantissa;
};


// ----------- Pre defined constants -----------

const gzGooble GZ_G_256			= gzGooble(256);
const gzGooble GZ_G_10			= gzGooble(10);
const gzGooble GZ_G_9			= gzGooble(9);
const gzGooble GZ_G_8			= gzGooble(8);
const gzGooble GZ_G_7			= gzGooble(7);
const gzGooble GZ_G_6			= gzGooble(6);
const gzGooble GZ_G_5			= gzGooble(5);
const gzGooble GZ_G_4			= gzGooble(4);
const gzGooble GZ_G_3			= gzGooble(3); 
const gzGooble GZ_G_2			= gzGooble(2);
const gzGooble GZ_G_ONE			= gzGooble(1);
const gzGooble GZ_G_ZERO		= gzGooble();
const gzGooble GZ_G_MINUS_ONE	= gzGooble(-1);

// ----------- External operators --------------

GZ_BASE_EXPORT gzGooble operator*(const gzInt32& left, const gzGooble& right);
GZ_BASE_EXPORT gzGooble operator*(const gzFloat& left, const gzGooble& right);
GZ_BASE_EXPORT gzGooble operator*(const gzDouble& left, const gzGooble& right);

GZ_BASE_EXPORT gzGooble operator/(const gzInt32& left, const gzGooble& right);
GZ_BASE_EXPORT gzGooble operator/(const gzFloat& left, const gzGooble& right);
GZ_BASE_EXPORT gzGooble operator/(const gzDouble& left, const gzGooble& right);

#endif //__GZ_GOOBLE_H__

