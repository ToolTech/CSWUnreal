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
// File			: gzMatrix.h
// Module		: gzBase
// Description	: Class definition of Matrix utilites.
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.200
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
// AMO	981104	Created file 	
// AMO	180919	Rework with templates to handle mix of multiple types
//
//******************************************************************************



//******************************************************************************
//
// Notes:	Never change the size of these classes as they are serialized binary
//			in many implementations. Keep the size 1:1
//
//
//******************************************************************************

#ifndef __GZ_MATRIX_H__
#define __GZ_MATRIX_H__

#include "gzBasicTypes.h"
#include "gzBase.h"
#include "gzXYZ.h"
#include "gzArithmetic.h"

/*!	\file
	\brief Matrix and Vector management utilites

	Most basic vector and matrix operations can be found in this class. The implementation
	checks the system for accellerated features like MMX,SIMD or 3DNow etc. to enhance performance
*/

// ******************** class definitions ***************************************

template <class T> class  gzVec3_; // forward

//******************************************************************************
// Class	: gzVec2_<T>
//									
// Purpose  : 2 dim vector template 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981128	Created 
// AMO	180215	Changed to template version	(2.9.1)
//									
//******************************************************************************
template <class T> class  gzVec2_
{
public:

	gzVec2_() {}		// Default empty constructor

	gzVec2_(const T& _v1, const T& _v2) :v1(_v1), v2(_v2) {}

	template <class Y> explicit operator gzVec2_<Y>() const { return gzVec2_<Y>((Y)v1, (Y)v2); }

	template <class Y>  explicit operator gzVec3_<Y>() const { return gzVec3_<Y>((Y)v1, (Y)v2, 1); }

	template <class Y> gzVec2_<T>& operator=(const gzVec2_<Y>& copy) { v1 = copy.v1; v2 = copy.v2; return *this; }

	gzVoid set(const T& _v1, const T& _v2) { v1 = _v1; v2 = _v2; }

	T length() const
	{
		return gzSqrt<T>(v1 * v1 + v2 * v2);
	}

	template <class Y> T dot(const gzVec2_<Y>& vector) const
	{
		return (T)(v1 * vector.v1 + v2 * vector.v2);
	}

	T lengthSq2() const
	{
		return v1 * v1 + v2 * v2;
	}

	gzVec2_ unit() const
	{
		T len(length());

		if (len)
		{
			T invlen(1 / len);
			return gzVec2_(v1 * invlen, v2 * invlen);
		}
		else
			return gzVec2_(0, 0);
	}

	gzVec2_ abs() const
	{
		return gzVec2_(gzAbs(v1), gzAbs(v2));
	}

	gzVoid normalize()
	{
		T len(length());
		if (!len)
			return;

		T invlen(1 / len);

		v1 = v1 * invlen;
		v2 = v2 * invlen;
	}

	gzVec2_ operator-() const noexcept(TRUE)
	{
		return gzVec2_(-v1, -v2);
	}

	template <class Y> gzBool operator==(const gzVec2_<Y>& right) const
	{
		if (gzAbs<T>(v1 - right.v1) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v2 - right.v2) > gzAritmetic_<T>::epsilon())
			return FALSE;
		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzVec2_<Y>& right) const
	{
		return !operator==(right);
	}

	template <class Y> gzVec2_& operator+=(const gzVec2_<Y>& vector)
	{
		v1 += vector.v1;
		v2 += vector.v2;
		return *this;
	}

	template <class Y> gzVec2_& operator-=(const gzVec2_<Y>& vector)
	{
		v1 += vector.v1;
		v2 += vector.v2;
		return *this;
	}

	gzVec2_& operator *= (const T& val)
	{
		v1 *= val;
		v2 *= val;
		return *this;
	}

	gzVec2_	operator * (const T& val) const
	{
		return gzVec2_(v1 * val, v2 * val);
	}

	gzVec2_	operator / (const T& val) const
	{
		T inv = 1 / val;

		return gzVec2_(v1 * inv, v2 * inv);
	}

	template <class Y> gzVec2_ operator - (const gzVec2_<Y>& vector_b) const
	{
		return gzVec2_(v1 - vector_b.v1, v2 - vector_b.v2);
	}

	template <class Y> gzVec2_ operator + (const gzVec2_<Y>& vector_b) const
	{
		return gzVec2_(v1 + vector_b.v1, v2 + vector_b.v2);
	}

	gzString asString(const gzString& format = "{%lf,%lf}") const
	{
		gzString result;
		return result.format(format, v1, v2);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v1)) + (*((gzUInt32*)gzPtr2Val(&v2)) << 1);
	}

public:

	union
	{
		struct
		{
			T v1, v2;
		};
		struct
		{
			T x, y;
		};
		struct
		{
			T s, t;
		};
		struct
		{
			T u, v;
		};
	};
};

template <class T, class Y> inline gzVec2_<T> operator * (const Y& val, const gzVec2_<T>& vector)
{
	return gzVec2_<T>((T)val * vector.v1, (T)val * vector.v2);
}

typedef gzVec2_<gzFloat>	gzVec2;
typedef gzVec2_<gzDouble>	gzVec2D;

template <class T>  class gzVec4_;	// Forward

//******************************************************************************
// Class	: gzVec3_<T>
//									
// Purpose  : 3 dim vector template 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180215	Created									(2.9.1)
//									
//******************************************************************************
template <class T>  class gzVec3_
{
public:

	gzVec3_() {}	// Default empty constructor

	gzVec3_(const T& _v1, const T& _v2, const T& _v3) : v1(_v1), v2(_v2), v3(_v3) {}

	gzVec3_(gzXYZ<T> xyz) : v1(xyz.x), v2(xyz.y), v3(xyz.z) {}

	template <class Y>  gzVec3_(const gzVec2_<Y>& copy, const T& val) : v1(copy.v1), v2(copy.v2), v3(val) {}

	template <class Y>  explicit operator gzVec3_<Y>() const { return gzVec3_<Y>((Y)v1, (Y)v2, (Y)v3); }

	template <class Y>  explicit operator gzVec4_<Y>() const { return gzVec4_<Y>((Y)v1, (Y)v2, (Y)v3, 1); }

	template <class Y> gzVec3_<T>& operator=(const gzVec3_<Y>& copy) { v1 = copy.v1; v2 = copy.v2; v3 = copy.v3; return *this; }

	gzVec3_(const T& heading, const T& pitch)
	{
		v1 = (T)(-sin<T>(heading * GZ_DEG2RAD) * cos<T>(pitch * GZ_DEG2RAD));
		v2 = (T)(sin<T>(pitch * GZ_DEG2RAD));
		v3 = (T)(-cos<T>(heading * GZ_DEG2RAD) * cos<T>(pitch * GZ_DEG2RAD));
	}


	gzVoid set(const T& _v1, const T& _v2, const T& _v3) { v1 = _v1; v2 = _v2; v3 = _v3; }

	template <class Y> T dot(const gzVec3_<Y>& vector) const
	{
		return (T)(x * vector.x + y * vector.y + z * vector.z);
	}

	template <class Y> gzVec3_ cross(const gzVec3_<Y>& vector) const noexcept(TRUE)
	{
		return gzVec3_((T)(y * vector.z - z * vector.y), (T)(z * vector.x - x * vector.z), (T)(x * vector.y - y * vector.x));
	}

	gzVec2_<T> trunc()
	{
		return gzVec2_<T>(v1, v2);
	}


	T length() const
	{
		return gzSqrt<T>(x * x + y * y + z * z);
	}

	T lengthSq2() const
	{
		return x * x + y * y + z * z;
	}


	gzVec3_ unit() const
	{
		T len(length());

		if (len)
		{
			T invlen(1 / len);
			return gzVec3_(v1 * invlen, v2 * invlen, v3 * invlen);
		}
		else
			return gzVec3_(0, 0, 0);
	}

	gzVec3_ abs() const
	{
		return gzVec3_(gzAbs(v1), gzAbs(v2), gzAbs(v3));
	}

	gzVec3_ clamped(T itemValue) const
	{
		return gzVec3_(gzMax(gzMin(v1, itemValue), -itemValue), gzMax(gzMin(v2, itemValue), -itemValue), gzMax(gzMin(v3, itemValue), -itemValue));
	}

	T maxVal() const
	{
		return gzMax(v1, gzMax(v2, v3));
	}

	gzVoid normalize()
	{
		T len(length());

		if (!len)
			return;

		T invlen(1 / len);

		v1 = v1 * invlen;
		v2 = v2 * invlen;
		v3 = v3 * invlen;
	}

	gzVoid unify()
	{
		if (!v3)
			return;

		T invlen(1 / v3);

		v1 = v1 * invlen;
		v2 = v2 * invlen;
		v3 = 1;
	}

	operator gzVec2_<T>() const
	{
		if (v3 == (T)1)
			return gzVec2_<T>(v1, v2);

		T inv3 = 1 / v3;
		return gzVec2_<T>(v1 * inv3, v2 * inv3);
	}


	template <class Y> gzBool operator==(const gzVec3_<Y>& right) const
	{
		if (gzAbs<T>(v1 - right.v1) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v2 - right.v2) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v3 - right.v3) > gzAritmetic_<T>::epsilon())
			return FALSE;

		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzVec3_<Y>& right) const
	{
		return !operator==(right);
	}

	gzVec3_ operator-() const noexcept(TRUE)
	{
		return gzVec3_(-v1, -v2, -v3);
	}

	template <class Y> gzVec3_& operator+=(const gzVec3_<Y>& vector) noexcept(TRUE)
	{
		v1 += vector.v1;
		v2 += vector.v2;
		v3 += vector.v3;
		return *this;
	}

	template <class Y> gzVec3_& operator-=(const gzVec3_<Y>& vector) noexcept(TRUE)
	{
		v1 -= vector.v1;
		v2 -= vector.v2;
		v3 -= vector.v3;
		return *this;
	}

	template <class Y> gzVec3_	operator * (const Y& val) const noexcept(TRUE)
	{
		return gzVec3_((T)(v1 * val), (T)(v2 * val), (T)(v3 * val));
	}

	gzVec3_& operator *= (const T& val) noexcept(TRUE)
	{
		v1 *= val;
		v2 *= val;
		v3 *= val;
		return *this;
	}

	gzVec3_	operator / (const T& val) const noexcept(TRUE)
	{
		T invlen(1 / val);
		return gzVec3_(v1 * invlen, v2 * invlen, v3 * invlen);
	}


	template <class Y> gzVec3_ operator - (const gzVec3_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec3_(v1 - vector_b.v1, v2 - vector_b.v2, v3 - vector_b.v3);
	}

	template <class Y> gzVec3_ operator + (const gzVec3_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec3_(v1 + vector_b.v1, v2 + vector_b.v2, v3 + vector_b.v3);
	}

	gzString asString(const gzString& format = "{%lf,%lf,%lf}") const
	{
		gzString result;
		return result.format(format, v1, v2, v3);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v1)) + (*((gzUInt32*)gzPtr2Val(&v2)) << 1) + (*((gzUInt32*)gzPtr2Val(&v3)) << 2);
	}

	gzVec3_ orthogonal(const gzVec3_& base) const noexcept(TRUE)
	{
		return ((*this) - this->dot(base) * base).unit();
	}

	gzXYZ<T> xyz()	const
	{
		return gzXYZ<T>(v1, v2, v3);
	}

	union
	{
		struct
		{
			T v1, v2, v3;
		};
		struct
		{
			T x, y, z;
		};
		struct
		{
			T r, g, b;
		};
		struct
		{
			T heading, pitch, roll;
		};
	};
};

template <class T, class Y> inline gzVec3_<T> operator * (const Y& val, const gzVec3_<T>& vector)
{
	return gzVec3_<T>((T)val * vector.v1, (T)val * vector.v2, (T)val * vector.v3);
}

typedef gzVec3_<gzFloat>	gzVec3;
typedef gzVec3_<gzDouble>	gzVec3D;

//******************************************************************************
// Class	: gzVec4_<T>
//									
// Purpose  : 4 dim vector template 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180215	Created									(2.9.1)
//									
//******************************************************************************
template <class T>  class gzVec4_
{
public:

	gzVec4_() {}	// Default empty constructor

	gzVec4_(const T& _v1, const T& _v2, const T& _v3, const T& _v4) : v1(_v1), v2(_v2), v3(_v3), v4(_v4) {}

	template <class Y> gzVec4_(const gzVec3_<Y>& copy, const T& val) : v1(copy.v1), v2(copy.v2), v3(copy.v3), v4(val) {}

	template <class Y> explicit operator gzVec4_<Y>() const { return gzVec4_<Y>((Y)v1, (Y)v2, (Y)v3, (Y)v4); }

	template <class Y> gzVec4_<T>& operator=(const gzVec4_<Y>& copy) { v1 = copy.v1; v2 = copy.v2; v3 = copy.v3; v4 = copy.v4; return *this; }


	gzVoid set(const T& _v1, const T& _v2, const T& _v3, const T& _v4) { v1 = _v1; v2 = _v2; v3 = _v3; v4 = _v4; }

	template <class Y> T dot(const gzVec4_<Y>& vector) const
	{
		return (T)(v1 * vector.v1 + v2 * vector.v2 + v3 * vector.v3 + v4 * vector.v4);
	}

	T length() const
	{
		return gzSqrt<T>(v1 * v1 + v2 * v2 + v3 * v3 + v4 * v4);
	}

	T lengthSq2() const
	{
		return v1 * v1 + v2 * v2 + v3 * v3 + v4 * v4;
	}

	gzVec3_<T> trunc()
	{
		return gzVec3_<T>(v1, v2, v3);
	}


	gzVec4_ unit() const
	{
		T len(length());

		if (len)
		{
			T invlen(1 / len);
			return gzVec4_(v1 * invlen, v2 * invlen, v3 * invlen, v4 * invlen);
		}
		else
			return gzVec4_(0, 0, 0, 0);
	}

	gzVec4_ abs() const
	{
		return gzVec4_(gzAbs(v1), gzAbs(v2), gzAbs(v3), gzAbs(v4));
	}

	gzVoid normalize()
	{
		T len(length());

		if (!len)
			return;

		T invlen(1 / len);

		v1 = v1 * invlen;
		v2 = v2 * invlen;
		v3 = v3 * invlen;
		v4 = v4 * invlen;
	}

	gzVec3_<T> xyz() const
	{
		return gzVec3_<T>(v1, v2, v3);
	}

	operator gzVec3_<T>() const
	{
		if (v4 == (T)1)
			return gzVec3_<T>(v1, v2, v3);

		T inv4 = 1 / v4;
		return gzVec3_<T>(v1 * inv4, v2 * inv4, v3 * inv4);
	}

	template <class Y> gzBool operator==(const gzVec4_<Y>& right) const
	{
		if (gzAbs<T>(v1 - right.v1) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v2 - right.v2) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v3 - right.v3) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v4 - right.v4) > gzAritmetic_<T>::epsilon())
			return FALSE;
		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzVec4_<Y>& right) const
	{
		return !operator==(right);
	}

	gzVec4_ operator-() const noexcept(TRUE)
	{
		return gzVec4_(-v1, -v2, -v3, -v4);
	}

	template <class Y>  gzVec4_& operator+=(const gzVec4_<Y>& vector) noexcept(TRUE)
	{
		v1 += vector.v1;
		v2 += vector.v2;
		v3 += vector.v3;
		v4 += vector.v4;
		return *this;
	}

	template <class Y>  gzVec4_& operator-=(const gzVec4_<Y>& vector) noexcept(TRUE)
	{
		v1 -= vector.v1;
		v2 -= vector.v2;
		v3 -= vector.v3;
		v4 -= vector.v4;
		return *this;
	}

	gzVec4_	operator * (const T& val) const noexcept(TRUE)
	{
		return gzVec4_(v1 * val, v2 * val, v3 * val, v4 * val);
	}

	gzVec4_& operator *= (const T& val) noexcept(TRUE)
	{
		v1 *= val;
		v2 *= val;
		v3 *= val;
		v4 *= val;
		return *this;
	}

	gzVec4_	operator / (const T& val) const noexcept(TRUE)
	{
		T invlen(1 / val);
		return gzVec4_(v1 * invlen, v2 * invlen, v3 * invlen, v4 * invlen);
	}


	template <class Y> gzVec4_ operator - (const gzVec4_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec4_(v1 - vector_b.v1, v2 - vector_b.v2, v3 - vector_b.v3, v4 - vector_b.v4);
	}

	template <class Y> gzVec4_ operator + (const gzVec4_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec4_(v1 + vector_b.v1, v2 + vector_b.v2, v3 + vector_b.v3, v4 + vector_b.v4);
	}

	// Homogenic

	template <class Y> gzVec3_<T> operator - (const gzVec3_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec3_<T>(v1 / v4 - vector_b.v1, v2 / v4 - vector_b.v2, v3 / v4 - vector_b.v3);
	}

	template <class Y> gzVec3_<T> operator + (const gzVec3_<Y>& vector_b) const noexcept(TRUE)
	{
		return gzVec3_<T>(v1 / v4 + vector_b.v1, v2 / v4 + vector_b.v2, v3 / v4 + vector_b.v3);
	}

	gzString asString(const gzString& format = "{%lf,%lf,%lf,%lf}") const
	{
		gzString result;
		return result.format(format, v1, v2, v3, v4);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v1)) + (*((gzUInt32*)gzPtr2Val(&v2)) << 1) + (*((gzUInt32*)gzPtr2Val(&v3)) << 2) + (*((gzUInt32*)gzPtr2Val(&v4)) << 3);
	}

	union
	{
		struct
		{
			T v1, v2, v3, v4;
		};
		struct
		{
			T x, y, z, w;
		};
		struct
		{
			T r, g, b, a;
		};
	};
};

template <class T> inline gzVec4_<T> operator * (const T& val, const gzVec4_<T>& vector)
{
	return gzVec4_<T>(val * vector.v1, val * vector.v2, val * vector.v3, val * vector.v4);
}

typedef gzVec4_<gzFloat>	gzVec4;
typedef gzVec4_<gzDouble>	gzVec4D;



//******************************************************************************
// Class	: -
//									
// Purpose  : - 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981128	Created 
//									
//******************************************************************************	
template <class T>  class gzMatrix2_
{
public:

	gzMatrix2_() {}	// Default empty constructor

	gzMatrix2_(const gzVec2_<T>& col_1, const gzVec2_<T>& col_2) : v11(col_1.v1), v12(col_2.v1), v21(col_1.v2), v22(col_2.v2) {}

	template <class Y> explicit operator gzMatrix2_<Y>() const { return gzMatrix2_<Y>(gzVec2_<Y>((Y)v11, (Y)v21), gzVec2_<Y>((Y)v12, (Y)v22)); }

	template <class Y> gzMatrix2_<T>& operator=(const gzMatrix2_<Y>& copy)
	{
		v11 = copy.v11;
		v12 = copy.v12;
		v21 = copy.v21;
		v22 = copy.v22;
		return *this;
	}


	gzVoid set(const gzVec2_<T>& col_1, const gzVec2_<T>& col_2) { v11 = col_1.v1; v12 = col_2.v1; v21 = col_1.v2; v22 = col_2.v2; }

	gzVec2_<T> col(gzUInt32 column)
	{
		switch (column)
		{
			case 0:
				return gzVec2_<T>(v11, v21);

			case 1:
				return gzVec2_<T>(v12, v22);

			default:
				throwFatalTemplateError("col() arg out of range");
		}
		return gzVec2_<T>();
	}

	gzVec2_<T> row(gzUInt32 row)
	{
		switch (row)
		{
			case 0:
				return gzVec2_<T>(v11, v12);

			case 1:
				return gzVec2_<T>(v21, v22);

			default:
				throwFatalTemplateError("row() arg out of range");
		}
		return gzVec2_<T>();
	}

	T determinant() const
	{
		return v11 * v22 - v12 * 21;
	}

	gzBool isIdentity() const
	{
		return	(v11 == 1) && (v22 == 1) && (v12 == 0) && (v21 == 0);
	}

	gzMatrix2_<T>& identity()
	{
		v11 = v22 = 1;

		v12 = v21 = 0;

		return *this;
	}

	static gzMatrix2_ identityMatrix()
	{
		return gzMatrix2_<T>(gzVec2_<T>(1, 0), gzVec2_<T>(0, 1));
	}

	static gzMatrix2_ scaleMatrix(const T& s1, const T& s2)
	{
		return gzMatrix2_<T>(gzVec2_<T>(s1, 0), gzVec2_<T>(0, s2));
	}

	template <class Y> gzBool inverse(gzMatrix2_<Y>& pivot) const
	{
		// Calculate the inverse for a 2x2 matrix

		T det = determinant();

		if (det == 0)
			return FALSE;

		det = 1 / det;

		pivot.v11 = v22 * det;
		pivot.v12 = -v12 * det;

		pivot.v21 = -v21 * det;
		pivot.v22 = v11 * det;

		return TRUE;
	}

	gzMatrix2_ unit() const
	{
		T len(determinant());

		if (len)
		{
			T invlen(1 / len);
			return gzMatrix2_<T>(gzVec2_<T>(v11 * invlen, v21 * invlen), gzVec2_<T>(v12 * invlen, v22 * invlen));
		}
		else
			return gzMatrix2_<T>(gzVec2_<T>(0, 0), gzVec2_<T>(0, 0));
	}

	gzMatrix2_ abs() const
	{
		return gzMatrix2_<T>(gzVec2_<T>(gzAbs(v11), gzAbs(v21)), gzVec2_<T>(gzAbs(v12), gzAbs(v22)));
	}

	gzVoid normalize()
	{
		T len(determinant());

		if (!len)
			return;

		T invlen(1 / len);

		v11 = v12 * invlen;
		v12 = v12 * invlen;
		v21 = v21 * invlen;
		v22 = v22 * invlen;
	}

	template <class Y> gzBool operator==(const gzMatrix2_<Y>& right) const
	{
		if (gzAbs<T>(v11 - right.v11) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v12 - right.v12) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v21 - right.v21) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v22 - right.v22) > gzAritmetic_<T>::epsilon())
			return FALSE;
		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzMatrix2_<Y>& right) const
	{
		return !operator==(right);
	}

	gzMatrix2_ operator-() noexcept(TRUE)
	{
		return gzMatrix2_<T>(gzVec2_<T>(-v11, -v21), gzVec2_<T>(-v12, -v22));
	}

	template <class Y> gzMatrix2_& operator+=(const gzMatrix2_<Y>& mat) noexcept(TRUE)
	{
		v11 += mat.v11;
		v12 += mat.v12;
		v21 += mat.v21;
		v22 += mat.v22;
		return *this;
	}

	template <class Y> gzMatrix2_& operator-=(const gzMatrix2_<Y>& mat) noexcept(TRUE)
	{
		v11 -= mat.v11;
		v12 -= mat.v12;
		v21 -= mat.v21;
		v22 -= mat.v22;
		return *this;
	}

	gzMatrix2_	operator * (const T& val) const noexcept(TRUE)
	{
		return gzMatrix2_<T>(gzVec2_<T>(v11 * val, v21 * val), gzVec2_<T>(v12 * val, v22 * val));
	}

	gzMatrix2_& operator *= (const T& val) noexcept(TRUE)
	{
		v11 *= val;
		v12 *= val;
		v21 *= val;
		v22 *= val;
		return *this;
	}

	gzMatrix2_	operator / (const T& val) const noexcept(TRUE)
	{
		T invlen(1 / val);
		return gzMatrix2_<T>(gzVec2_<T>(v11 * invlen, v21 * invlen), gzVec2_<T>(v12 * invlen, v22 * invlen));
	}


	template <class Y> gzMatrix2_ operator - (const gzMatrix2_<Y>& mat) const noexcept(TRUE)
	{
		return gzMatrix2_<T>(gzVec2_<T>(v11 - mat.v11, v21 - mat.v21), gzVec2_<T>(v12 - mat.v12, v22 - mat.v22));
	}

	template <class Y> gzMatrix2_ operator + (const gzMatrix2_<Y>& mat) const noexcept(TRUE)
	{
		return gzMatrix2_<T>(gzVec2_<T>(v11 + mat.v11, v21 + mat.v21), gzVec2_<T>(v12 + mat.v12, v22 + mat.v22));
	}

	template <class Y> gzMatrix2_ operator * (const gzMatrix2_<Y>& mat) const noexcept(TRUE)
	{
		gzMatrix2_ res;

		res.v11 = v11 * mat.v11 + v12 * mat.v21;
		res.v12 = v11 * mat.v12 + v12 * mat.v22;

		res.v22 = v21 * mat.v12 + v22 * mat.v22;
		res.v21 = v21 * mat.v11 + v22 * mat.v21;

		return res;
	}

	template <class Y> gzVec2_<T> operator * (const gzVec2_<Y>& vec) const noexcept(TRUE)
	{
		gzVec2_<T> res;

		res.v1 = v11 * vec.v1 + v12 * vec.v2;
		res.v2 = v21 * vec.v1 + v22 * vec.v2;

		return res;
	}

	gzString asString(const gzString& format = "[[%lf,%lf][%lf,%lf]]") const
	{
		gzString result;
		return result.format(format, v11, v12, v21, v22);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v11)) + (*((gzUInt32*)gzPtr2Val(&v12)) << 1) + (*((gzUInt32*)gzPtr2Val(&v21)) << 2) + (*((gzUInt32*)gzPtr2Val(&v22)) << 3);
	}

	// Columnwize storage

	T v11, v21;
	T v12, v22;
};

template <class T> inline gzMatrix2_<T> operator * (const T& val, const gzMatrix2_<T>& mat)
{
	return gzMatrix2_<T>(gzVec2_<T>(val * mat.v11, val * mat.v21), gzVec2_<T>(val * mat.v12, val * mat.v22));
}

typedef gzMatrix2_<gzFloat>		gzMatrix2;
typedef gzMatrix2_<gzDouble>	gzMatrix2D;

template <class T> class gzQuaternion_;


//******************************************************************************
// Class	: -
//									
// Purpose  : - 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981128	Created 
//									
//******************************************************************************
template <class T>  class gzMatrix3_
{
public:

	gzMatrix3_() {}	// Default empty constructor

	gzMatrix3_(const gzVec3_<T>& col_1, const gzVec3_<T>& col_2, const gzVec3_<T>& col_3) : v11(col_1.v1), v21(col_1.v2), v31(col_1.v3), v12(col_2.v1), v22(col_2.v2), v32(col_2.v3), v13(col_3.v1), v23(col_3.v2), v33(col_3.v3) {}

	template <class Y> explicit operator gzMatrix3_<Y>() const { return gzMatrix3_<Y>(gzVec3_<Y>((Y)v11, (Y)v21, (Y)v31), gzVec3_<Y>((Y)v12, (Y)v22, (Y)v32), gzVec3_<Y>((Y)v13, (Y)v23, (Y)v33)); }

	template <class Y> gzMatrix3_<T>& operator=(const gzMatrix3_<Y>& copy)
	{
		v11 = copy.v11; v12 = copy.v12;	v13 = copy.v13;
		v21 = copy.v21; v22 = copy.v22;	v23 = copy.v23;
		v31 = copy.v31;	v32 = copy.v32;	v33 = copy.v33;
		return *this;
	}


	gzVoid set(const gzVec3_<T>& col_1, const gzVec3_<T>& col_2, const gzVec3_<T>& col_3) { v11 = col_1.v1; v12 = col_2.v1; v13 = col_3.v1; v21 = col_1.v2; v22 = col_2.v2; v23 = col_3.v2; v31 = col_1.v3; v32 = col_2.v3; v33 = col_3.v3; }

	gzVec3_<T> col(gzUInt32 column)
	{
		switch (column)
		{
			case 0:
				return gzVec3_<T>(v11, v21, v31);

			case 1:
				return gzVec3_<T>(v12, v22, v32);

			case 2:
				return gzVec3_<T>(v13, v23, v33);

			default:
				throwFatalTemplateError("col() arg out of range");
		}
		return gzVec3_<T>();
	}

	gzVec3_<T> row(gzUInt32 row)
	{
		switch (row)
		{
			case 0:
				return gzVec3_<T>(v11, v12, v13);

			case 1:
				return gzVec3_<T>(v21, v22, v23);

			case 2:
				return gzVec3_<T>(v31, v32, v33);

			default:
				throwFatalTemplateError("row() arg out of range");
		}

		return gzVec3_<T>();
	}

	T sum()
	{
		return	v11 + v12 + v13 +
			v21 + v22 + v23 +
			v31 + v32 + v33;
	}

	T determinant() const
	{
		return v11 * (v22 * v33 - v32 * v23) - v21 * (v12 * v33 - v32 * v13) + v31 * (v12 * v23 - v22 * v13);
	}

	template <class Y> gzBool inverse(gzMatrix3_<Y>& pivot) const
	{
		// Calculate the inverse for a 3x3 matrix

		T det = v11 * (v22 * v33 - v32 * v23) - v21 * (v12 * v33 - v32 * v13) + v31 * (v12 * v23 - v22 * v13);

		if (det == 0)
			return FALSE;

		det = 1 / det;

		pivot.v11 = -(v23 * v32 - v22 * v33) * det;
		pivot.v12 = -(v12 * v33 - v13 * v32) * det;
		pivot.v13 = (v12 * v23 - v13 * v22) * det;

		pivot.v21 = (v23 * v31 - v21 * v33) * det;
		pivot.v22 = -(v13 * v31 - v11 * v33) * det;
		pivot.v23 = -(v11 * v23 - v13 * v21) * det;

		pivot.v31 = -(v22 * v31 - v21 * v32) * det;
		pivot.v32 = (v12 * v31 - v11 * v32) * det;
		pivot.v33 = (v11 * v22 - v12 * v21) * det;

		return TRUE;
	}

	gzMatrix3_ unit() const
	{
		T len(determinant());

		if (len)
		{
			T invlen(1 / len);
			return gzMatrix3_<T>(gzVec3_<T>(v11 * invlen, v21 * invlen, v31 * invlen), gzVec3_<T>(v12 * invlen, v22 * invlen, v32 * invlen), gzVec3_<T>(v13 * invlen, v23 * invlen, v33 * invlen));
		}
		else
			return  gzMatrix3_<T>(gzVec3_<T>(0, 0, 0), gzVec3_<T>(0, 0, 0), gzVec3_<T>(0, 0, 0));
	}

	gzMatrix3_ abs() const
	{
		return gzMatrix3_<T>(gzVec3_<T>(gzAbs(v11), gzAbs(v21), gzAbs(v31)), gzVec3_<T>(gzAbs(v12), gzAbs(v22), gzAbs(v32)), gzVec3_<T>(gzAbs(v13), gzAbs(v23), gzAbs(v33)));
	}

	gzMatrix3_ transpose() const
	{
		return gzMatrix3_<T>(gzVec3_<T>(v11, v12, v13), gzVec3_<T>(v21, v22, v23), gzVec3_<T>(v31, v32, v33));
	}

	gzVoid normalize()
	{
		T len(determinant());

		if (!len)
			return;

		T invlen(1 / len);

		v11 = v12 * invlen;
		v12 = v12 * invlen;
		v13 = v13 * invlen;
		v21 = v22 * invlen;
		v22 = v22 * invlen;
		v23 = v23 * invlen;
		v31 = v32 * invlen;
		v32 = v32 * invlen;
		v33 = v33 * invlen;
	}

	template <class Y> gzBool operator==(const gzMatrix3_<Y>& right) const
	{
		if (gzAbs<T>(v11 - right.v11) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v12 - right.v12) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v13 - right.v13) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v21 - right.v21) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v22 - right.v22) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v23 - right.v23) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v31 - right.v31) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v32 - right.v32) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v33 - right.v33) > gzAritmetic_<T>::epsilon())
			return FALSE;
		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzMatrix3_<Y>& right) const
	{
		return !operator==(right);
	}

	gzMatrix3_ operator-() noexcept(TRUE)
	{
		return gzMatrix3_<T>(gzVec3_<T>(-v11, -v21, -v31), gzVec3_<T>(-v12, -v22, -v32), gzVec3_<T>(-v13, -v23, -v33));
	}

	template <class Y> gzMatrix3_& operator+=(const gzMatrix3_<Y>& mat) noexcept(TRUE)
	{
		v11 += mat.v11;
		v12 += mat.v12;
		v13 += mat.v13;
		v21 += mat.v21;
		v22 += mat.v22;
		v23 += mat.v23;
		v31 += mat.v31;
		v32 += mat.v32;
		v33 += mat.v33;

		return *this;
	}

	template <class Y> gzMatrix3_& operator-=(const gzMatrix3_<Y>& mat) noexcept(TRUE)
	{
		v11 -= mat.v11;
		v12 -= mat.v12;
		v13 -= mat.v13;
		v21 -= mat.v21;
		v22 -= mat.v22;
		v23 -= mat.v23;
		v31 -= mat.v31;
		v32 -= mat.v32;
		v33 -= mat.v33;

		return *this;
	}

	gzMatrix3_	operator * (const T& val) const noexcept(TRUE)
	{
		return gzMatrix3_<T>(gzVec3_<T>(val * v11, val * v21, val * v31), gzVec3_<T>(val * v12, val * v22, val * v32), gzVec3_<T>(val * v13, val * v23, val * v33));
	}

	gzMatrix3_& operator *= (const T& val) noexcept(TRUE)
	{
		v11 *= val;
		v12 *= val;
		v13 *= val;
		v21 *= val;
		v22 *= val;
		v23 *= val;
		v31 *= val;
		v32 *= val;
		v33 *= val;

		return *this;
	}

	gzMatrix3_	operator / (const T& val) const noexcept(TRUE)
	{
		T invlen(1 / val);
		return gzMatrix3_<T>(gzVec3_<T>(v11 * invlen, v21 * invlen, v31 * invlen), gzVec3_<T>(v12 * invlen, v22 * invlen, v32 * invlen), gzVec3_<T>(v13 * invlen, v23 * invlen, v33 * invlen));
	}


	template <class Y> gzMatrix3_ operator - (const gzMatrix3_<Y>& mat) const noexcept(TRUE)
	{
		return gzMatrix3_<T>(gzVec3_<T>(v11 - mat.v11, v21 - mat.v21, v31 - mat.v31), gzVec3_<T>(v12 - mat.v12, v22 - mat.v22, v32 - mat.v32), gzVec3_<T>(v13 - mat.v13, v23 - mat.v23, v33 - mat.v33));
	}

	template <class Y> gzMatrix3_ operator + (const gzMatrix3_<Y>& mat) const noexcept(TRUE)
	{
		return gzMatrix3_<T>(gzVec3_<T>(v11 + mat.v11, v21 + mat.v21, v31 + mat.v31), gzVec3_<T>(v12 + mat.v12, v22 + mat.v22, v32 + mat.v32), gzVec3_<T>(v13 + mat.v13, v23 + mat.v23, v33 + mat.v33));
	}

	template <class Y> gzMatrix3_ operator * (const gzMatrix3_<Y>& mat) const noexcept(TRUE)
	{
		gzMatrix3_ res;

		res.v11 = v11 * mat.v11 + v12 * mat.v21 + v13 * mat.v31;
		res.v12 = v11 * mat.v12 + v12 * mat.v22 + v13 * mat.v32;
		res.v13 = v11 * mat.v13 + v12 * mat.v23 + v13 * mat.v33;

		res.v23 = v21 * mat.v13 + v22 * mat.v23 + v23 * mat.v33;
		res.v22 = v21 * mat.v12 + v22 * mat.v22 + v23 * mat.v32;
		res.v21 = v21 * mat.v11 + v22 * mat.v21 + v23 * mat.v31;

		res.v31 = v31 * mat.v11 + v32 * mat.v21 + v33 * mat.v31;
		res.v32 = v31 * mat.v12 + v32 * mat.v22 + v33 * mat.v32;
		res.v33 = v31 * mat.v13 + v32 * mat.v23 + v33 * mat.v33;

		return res;
	}

	template <class Y> gzVec3_<T> operator * (const gzVec3_<Y>& vec) const noexcept(TRUE)
	{
		gzVec3_<T> res;

		res.v1 = v11 * vec.v1 + v12 * vec.v2 + v13 * vec.v3;		// This will give precision warnings when used if precision is decreased
		res.v2 = v21 * vec.v1 + v22 * vec.v2 + v23 * vec.v3;
		res.v3 = v31 * vec.v1 + v32 * vec.v2 + v33 * vec.v3;

		return res;
	}

	gzString asString(const gzString& format = "[[%lf,%lf,%lf][%lf,%lf,%lf][%lf,%lf,%lf]]") const
	{
		gzString result;
		return result.format(format, v11, v12, v13, v21, v22, v23, v31, v32, v33);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v11)) + (*((gzUInt32*)gzPtr2Val(&v22)) << 1) + (*((gzUInt32*)gzPtr2Val(&v23)) << 2) + (*((gzUInt32*)gzPtr2Val(&v33)) << 3);
	}

	gzBool decompose_euler_yxz(T& h, T& p, T& r)	const
	{
		// Z forward
		// Y up
		// X left
		// Clockwize rotations

		if (determinant() < 0)	// Mirrored
			return FALSE;

		gzVec3_<T> dir = gzVec3_<T>(v13, v23, v33);	// dir^ vector direction (Z)

		if (dir.lengthSq2() == 0.0)
			return FALSE;

		dir.normalize();

		gzVec3_<T> up = gzVec3_<T>(v12, v22, v32);	// up^ vector (Y)

		up.normalize();

		p = (T)asin(-dir.y);		// neg Y component of dir^ is the pitch


		if (gzAbs(dir.y) == 1)	// looking up or down, pitch +-90
		{
			h = (T)atan2(-dir.y * up.x, -dir.y * up.z);
			r = 0;					// Let the roll be zero
		}
		else
		{
			h = (T)atan2(dir.x, dir.z);
			r = (T)atan2(up.z * dir.x - dir.z * up.x, up.y);
		}

		return TRUE;
	}

	gzBool decompose_euler_zxy(T& h, T& p, T& r) const
	{
		if (determinant() < 0)	// Mirrored
			return FALSE;

		gzVec3_<T> dir = gzVec3_<T>(v12, v22, v32);	// dir^ vector direction (Y)

		if (dir.lengthSq2() == 0.0)
			return FALSE;

		dir.normalize();

		gzVec3_<T> up = gzVec3_<T>(v13, v23, v33);	// up^ vector (Z)

		up.normalize();

		p = (T)asin(dir.z);		// Z component of dir^ is the pitch


		if (gzAbs(dir.z) == 1)	// looking up or down, pitch +-90
		{
			h = (T)atan2(dir.z * up.x, -dir.z * up.y);
			r = 0;					// Let the roll be zero
		}
		else
		{
			h = (T)atan2(-dir.x, dir.y);
			r = (T)atan2(-up.y * dir.x + dir.y * up.x, up.z);
		}

		return TRUE;
	}

	gzBool decompose_euler_xyz(T& h, T& p, T& r) const
	{
		if (determinant() < 0)	// Mirrored
			return FALSE;

		gzVec3_<T> dir = gzVec3_<T>(v13, v23, v33);	// dir^ vector direction (Z)

		if (dir.lengthSq2() == 0.0)
			return FALSE;

		dir.normalize();

		gzVec3_<T> up = gzVec3_<T>(v11, v21, v31);	// up^ vector (X)

		up.normalize();

		p = (T)asin(dir.x);		// UP component of dir^ is the pitch


		if (gzAbs(dir.x) == 1)	// UP component of dir^ is +-1 looking up or down, pitch +-90
		{
			h = (T)atan2(dir.x * up.y, -dir.x * up.z);
			r = 0;					// Let the roll be zero
		}
		else
		{
			h = (T)atan2(-dir.y, dir.z);
			r = (T)atan2(-up.z * dir.y + dir.z * up.y, up.x);
		}

		return TRUE;
	}

	gzQuaternion_<T>  quaternion() const
	{
		T d0 = v11;
		T d1 = v22;
		T d2 = v33;

		T P1 = 1 + d0 + d1 + d2;
		T P2 = 1 + d0 - d1 - d2;
		T P3 = 1 - d0 + d1 - d2;
		T P4 = 1 - d0 - d1 + d2;

		T q1, q2, q3, q4;

		if (P1 > P2)
		{
			if (P1 > P3)
			{
				if (P1 > P4)
				{
					q1 = gzSqrt(P1) / 2;
					q2 = (v32 - v23) / (4 * q1);
					q3 = (v13 - v31) / (4 * q1);
					q4 = (v21 - v12) / (4 * q1);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
			else
			{
				if (P3 > P4)
				{
					q3 = gzSqrt(P3) / 2;
					q1 = (v13 - v31) / (4 * q3);
					q2 = (v21 + v12) / (4 * q3);
					q4 = (v32 + v23) / (4 * q3);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
		}
		else
		{
			if (P2 > P3)
			{
				if (P2 > P4)
				{
					q2 = gzSqrt(P2) / 2;
					q1 = (v32 - v23) / (4 * q2);
					q3 = (v21 + v12) / (4 * q2);
					q4 = (v13 + v31) / (4 * q2);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
			else
			{
				if (P3 > P4)
				{
					q3 = gzSqrt(P3) / 2;
					q1 = (v13 - v31) / (4 * q3);
					q2 = (v21 + v12) / (4 * q3);
					q4 = (v32 + v23) / (4 * q3);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
		}

		if (q1 < 0)
		{
			q1 = -q1;
			q2 = -q2;
			q3 = -q3;
			q4 = -q4;
		}

		return gzQuaternion_<T>(q1, q2, q3, q4);
	}

	static gzMatrix3_ euler_xyz(const T& x_rot, const T& y_rot = 0, const T& z_rot = 0)
	{
		T y_s(sin(y_rot)), y_c(cos(y_rot));
		T x_s(sin(x_rot)), x_c(cos(x_rot));
		T z_s(sin(z_rot)), z_c(cos(z_rot));

		gzMatrix3_<T> mat;

		mat.v11 = y_c * z_c;
		mat.v12 = -y_c * z_s;
		mat.v13 = y_s;
		mat.v21 = x_c * z_s + z_c * x_s * y_s;
		mat.v22 = x_c * z_c - x_s * y_s * z_s;
		mat.v23 = -y_c * x_s;
		mat.v31 = x_s * z_s - x_c * z_c * y_s;
		mat.v32 = z_c * x_s + x_c * y_s * z_s;
		mat.v33 = x_c * y_c;


		return mat;
	}

	static gzMatrix3_ euler_yxz(const T& y_rot, const T& x_rot = 0, const T& z_rot = 0)
	{
		T y_s(sin(y_rot)), y_c(cos(y_rot));
		T x_s(sin(x_rot)), x_c(cos(x_rot));
		T z_s(sin(z_rot)), z_c(cos(z_rot));

		gzMatrix3_<T> mat;

		mat.v11 = x_s * y_s * z_s + y_c * z_c;
		mat.v12 = x_s * y_s * z_c - y_c * z_s;
		mat.v13 = x_c * y_s;
		mat.v21 = z_s * x_c;
		mat.v22 = z_c * x_c;
		mat.v23 = -x_s;
		mat.v31 = x_s * y_c * z_s - y_s * z_c;
		mat.v32 = x_s * y_c * z_c + y_s * z_s;
		mat.v33 = x_c * y_c;


		return mat;
	}

	static gzMatrix3_ euler_zxy(const T& z_rot, const T& x_rot = 0, const T& y_rot = 0)
	{
		T y_s(sin(y_rot)), y_c(cos(y_rot));
		T x_s(sin(x_rot)), x_c(cos(x_rot));
		T z_s(sin(z_rot)), z_c(cos(z_rot));

		gzMatrix3_<T> mat;

		mat.v11 = -x_s * y_s * z_s + y_c * z_c;
		mat.v12 = -z_s * x_c;
		mat.v13 = x_s * y_c * z_s + y_s * z_c;
		mat.v21 = x_s * y_s * z_c + y_c * z_s;
		mat.v22 = z_c * x_c;
		mat.v23 = -x_s * y_c * z_c + y_s * z_s;
		mat.v31 = -x_c * y_s;
		mat.v32 = x_s;
		mat.v33 = x_c * y_c;


		return mat;
	}

	gzBool isIdentity() const
	{
		return	(v11 == 1) && (v22 == 1) && (v33 == 1) &&
			(v12 == 0) && (v13 == 0) &&
			(v21 == 0) && (v23 == 0) &&
			(v31 == 0) && (v32 == 0);
	}

	gzMatrix3_<T>& identity()
	{
		v11 = v22 = v33 = 1;

		v12 = v13 = v21 = v23 = v31 = v32 = 0;

		return *this;
	}

	static gzMatrix3_ identityMatrix()
	{
		return gzMatrix3_<T>(gzVec3_<T>(1, 0, 0), gzVec3_<T>(0, 1, 0), gzVec3_<T>(0, 0, 1));
	}

	static gzMatrix3_ scaleMatrix(const T& s1, const T& s2, const T& s3)
	{
		return gzMatrix3_<T>(gzVec3_<T>(s1, 0, 0), gzVec3_<T>(0, s2, 0), gzVec3_<T>(0, 0, s3));
	}

	// Columnwize storage

	T v11, v21, v31;
	T v12, v22, v32;
	T v13, v23, v33;
};

template <class T> inline gzMatrix3_<T> operator * (const T& val, const gzMatrix3_<T>& mat)
{
	return gzMatrix3_<T>(gzVec3_<T>(val * mat.v11, val * mat.v21, val * mat.v31), gzVec3_<T>(val * mat.v12, val * mat.v22, val * mat.v32), gzVec3_<T>(val * mat.v13, val * mat.v23, val * mat.v33));
}

typedef gzMatrix3_<gzFloat>		gzMatrix3;
typedef gzMatrix3_<gzDouble>	gzMatrix3D;

// ------- Vector and Matrix Constants -----------------------------------------------------------

enum GZ_MATRIX3_IND { GZ3_V11, GZ3_V21, GZ3_V31, GZ3_V12, GZ3_V22, GZ3_V32, GZ3_V13, GZ3_V23, GZ3_V33 };
enum GZ_MATRIX4_IND { GZ4_V11, GZ4_V21, GZ4_V31, GZ4_V41, GZ4_V12, GZ4_V22, GZ4_V32, GZ4_V42, GZ4_V13, GZ4_V23, GZ4_V33, GZ4_V43, GZ4_V14, GZ4_V24, GZ4_V34, GZ4_V44 };

const gzVec2 GZ_ZERO_VEC2 = gzVec2(0, 0);
const gzVec3 GZ_ZERO_VEC3 = gzVec3(0, 0, 0);
const gzVec4 GZ_ZERO_VEC4 = gzVec4(0, 0, 0, 0);

const gzVec2D GZ_ZERO_VEC2D = gzVec2D(0, 0);
const gzVec3D GZ_ZERO_VEC3D = gzVec3D(0, 0, 0);
const gzVec4D GZ_ZERO_VEC4D = gzVec4D(0, 0, 0, 0);

const gzVec2 GZ_ONE_VEC2 = gzVec2(1, 1);
const gzVec3 GZ_ONE_VEC3 = gzVec3(1, 1, 1);
const gzVec4 GZ_ONE_VEC4 = gzVec4(1, 1, 1, 1);

const gzVec3 GZ_X_VEC3 = gzVec3(1, 0, 0);
const gzVec3 GZ_Y_VEC3 = gzVec3(0, 1, 0);
const gzVec3 GZ_Z_VEC3 = gzVec3(0, 0, 1);

const gzVec4 GZ_X_VEC4 = gzVec4(1, 0, 0, 0);
const gzVec4 GZ_Y_VEC4 = gzVec4(0, 1, 0, 0);
const gzVec4 GZ_Z_VEC4 = gzVec4(0, 0, 1, 0);
const gzVec4 GZ_W_VEC4 = gzVec4(0, 0, 0, 1);


//******************************************************************************
// Class	: gzMatrix4_
//									
// Purpose  : template class for 4x4 matrixes 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180918	Created 
//									
//******************************************************************************
template <class T>  class gzMatrix4_
{
public:

	gzMatrix4_() {}	// Default empty constructor

	gzMatrix4_(const gzVec4_<T>& col_1, const gzVec4_<T>& col_2, const gzVec4_<T>& col_3, const gzVec4_<T>& col_4) : v11(col_1.v1), v21(col_1.v2), v31(col_1.v3), v41(col_1.v4), v12(col_2.v1), v22(col_2.v2), v32(col_2.v3), v42(col_2.v4), v13(col_3.v1), v23(col_3.v2), v33(col_3.v3), v43(col_3.v4), v14(col_4.v1), v24(col_4.v2), v34(col_4.v3), v44(col_4.v4) {}

	gzMatrix4_(const gzVec3_<T>& col_1, const gzVec3_<T>& col_2, const gzVec3_<T>& col_3) : v11(col_1.v1), v21(col_1.v2), v31(col_1.v3), v41(0), v12(col_2.v1), v22(col_2.v2), v32(col_2.v3), v42(0), v13(col_3.v1), v23(col_3.v2), v33(col_3.v3), v43(0), v14(0), v24(0), v34(0), v44(1) {}

	template <class Y> explicit operator gzMatrix4_<Y>() const { return gzMatrix4_<Y>(gzVec4_<Y>((Y)v11, (Y)v21, (Y)v31, (Y)v41), gzVec4_<Y>((Y)v12, (Y)v22, (Y)v32, (Y)v42), gzVec4_<Y>((Y)v13, (Y)v23, (Y)v33, (Y)v43), gzVec4_<Y>((Y)v14, (Y)v24, (Y)v34, (Y)v44)); }

	template <class Y> gzMatrix4_(const gzMatrix3_<Y>& matrix)
	{
		v11 = matrix.v11;
		v21 = matrix.v21;
		v31 = matrix.v31;
		v41 = 0;

		v12 = matrix.v12;
		v22 = matrix.v22;
		v32 = matrix.v32;
		v42 = 0;

		v13 = matrix.v13;
		v23 = matrix.v23;
		v33 = matrix.v33;
		v43 = 0;

		v14 = 0;
		v24 = 0;
		v34 = 0;
		v44 = 1;
	}

	template <class Y> gzMatrix4_<T>& operator=(const gzMatrix4_<Y>& copy)
	{
		v11 = (T)copy.v11;	v12 = (T)copy.v12;	v13 = (T)copy.v13;	v14 = (T)copy.v14;
		v21 = (T)copy.v21;	v22 = (T)copy.v22;	v23 = (T)copy.v23;	v24 = (T)copy.v24;
		v31 = (T)copy.v31;	v32 = (T)copy.v32;	v33 = (T)copy.v33;	v34 = (T)copy.v34;
		v41 = (T)copy.v41;	v42 = (T)copy.v42;	v43 = (T)copy.v43;	v44 = (T)copy.v44;
		return *this;
	}


	gzVoid set(const gzVec4_<T>& col_1, const gzVec4_<T>& col_2, const gzVec4_<T>& col_3, const gzVec4_<T>& col_4) { v11 = col_1.v1; v12 = col_2.v1; v13 = col_3.v1; v14 = col_4.v1; v21 = col_1.v2; v22 = col_2.v2; v23 = col_3.v2; v24 = col_4.v2; v31 = col_1.v3; v32 = col_2.v3; v33 = col_3.v3; v34 = col_4.v3; v41 = col_1.v4; v42 = col_2.v4; v43 = col_3.v4; v44 = col_4.v4; }

	gzVoid  setRow(gzInt32 row, const gzVec4_<T>& vec)
	{
		switch (row)
		{
			case 0:
				v11 = vec.v1;
				v12 = vec.v2;
				v13 = vec.v3;
				v14 = vec.v4;
				break;

			case 1:
				v21 = vec.v1;
				v22 = vec.v2;
				v23 = vec.v3;
				v24 = vec.v4;
				break;

			case 2:
				v31 = vec.v1;
				v32 = vec.v2;
				v33 = vec.v3;
				v34 = vec.v4;
				break;

			case 3:
				v41 = vec.v1;
				v42 = vec.v2;
				v43 = vec.v3;
				v44 = vec.v4;
				break;
		}
	}

	gzVoid setCol(gzInt32 col, const gzVec4_<T>& vec)
	{
		switch (col)
		{
			case 0:
				v11 = vec.v1;
				v21 = vec.v2;
				v31 = vec.v3;
				v41 = vec.v4;
				break;

			case 1:
				v12 = vec.v1;
				v22 = vec.v2;
				v32 = vec.v3;
				v42 = vec.v4;
				break;

			case 2:
				v13 = vec.v1;
				v23 = vec.v2;
				v33 = vec.v3;
				v43 = vec.v4;
				break;

			case 3:
				v14 = vec.v1;
				v24 = vec.v2;
				v34 = vec.v3;
				v44 = vec.v4;
				break;

		}
	}

	gzVoid setRow(gzInt32 row, const gzVec3_<T>& vec)
	{
		switch (row)
		{
			case 0:
				v11 = vec.v1;
				v12 = vec.v2;
				v13 = vec.v3;
				v14 = 0;
				break;

			case 1:
				v21 = vec.v1;
				v22 = vec.v2;
				v23 = vec.v3;
				v24 = 0;
				break;

			case 2:
				v31 = vec.v1;
				v32 = vec.v2;
				v33 = vec.v3;
				v34 = 0;
				break;

			case 3:
				v41 = vec.v1;
				v42 = vec.v2;
				v43 = vec.v3;
				v44 = 1;
				break;
		}
	}

	gzVoid setCol(gzInt32 col, const gzVec3_<T>& vec)
	{
		switch (col)
		{
			case 0:
				v11 = vec.v1;
				v21 = vec.v2;
				v31 = vec.v3;
				v41 = 0;
				break;

			case 1:
				v12 = vec.v1;
				v22 = vec.v2;
				v32 = vec.v3;
				v42 = 0;
				break;

			case 2:
				v13 = vec.v1;
				v23 = vec.v2;
				v33 = vec.v3;
				v43 = 0;
				break;

			case 3:
				v14 = vec.v1;
				v24 = vec.v2;
				v34 = vec.v3;
				v44 = 1;
				break;
		}
	}

	gzVec4_<T> col(gzUInt32 column)
	{
		switch (column)
		{
			case 0:
				return gzVec4_<T>(v11, v21, v31, v41);

			case 1:
				return gzVec4_<T>(v12, v22, v32, v42);

			case 2:
				return gzVec4_<T>(v13, v23, v33, v43);

			case 3:
				return gzVec4_<T>(v14, v24, v34, v44);

			default:
				throwFatalTemplateError("col() arg out of range");
		}

		return gzVec4_<T>();
	}

	gzVec4_<T> row(gzUInt32 row)
	{
		switch (row)
		{
			case 0:
				return gzVec4_<T>(v11, v12, v13, v14);

			case 1:
				return gzVec4_<T>(v21, v22, v23, v24);

			case 2:
				return gzVec4_<T>(v31, v32, v33, v34);

			case 3:
				return gzVec4_<T>(v41, v42, v43, v44);

			default:
				throwFatalTemplateError("row() arg out of range");
		}

		return gzVec4_<T>();
	}

	T determinant() const
	{
		return v11 * (v22 * (v33 * v44 - v34 * v43) - v32 * (v23 * v44 - v24 * v43) + v42 * (v23 * v34 - v24 * v33))
			- v21 * (v12 * (v33 * v44 - v34 * v43) - v32 * (v13 * v44 - v14 * v43) + v42 * (v13 * v34 - v14 * v33))
			+ v31 * (v12 * (v23 * v44 - v24 * v43) - v22 * (v13 * v44 - v14 * v43) + v42 * (v13 * v24 - v14 * v23))
			- v41 * (v12 * (v23 * v34 - v24 * v33) - v22 * (v13 * v34 - v14 * v33) + v32 * (v13 * v24 - v14 * v23));
	}

	gzBool isIdentity() const
	{
		return	(v11 == 1) && (v22 == 1) && (v33 == 1) && (v44 == 1) &&
			(v12 == 0) && (v13 == 0) && (v14 == 0) &&
			(v21 == 0) && (v23 == 0) && (v24 == 0) &&
			(v31 == 0) && (v32 == 0) && (v34 == 0) &&
			(v41 == 0) && (v42 == 0) && (v43 == 0);
	}

	gzMatrix4_<T>& identity()
	{
		v11 = v22 = v33 = v44 = 1;

		v12 = v13 = v14 = v21 = v23 = v24 = v31 = v32 = v34 = v41 = v42 = v43 = 0;

		return *this;
	}

	static gzMatrix4_ identityMatrix()
	{
		return gzMatrix4_<T>(gzVec4_<T>(1, 0, 0, 0), gzVec4_<T>(0, 1, 0, 0), gzVec4_<T>(0, 0, 1, 0), gzVec4_<T>(0, 0, 0, 1));
	}

	static gzMatrix4_ scaleMatrix(const T& s1, const T& s2, const T& s3, const T& s4)
	{
		return gzMatrix4_<T>(gzVec4_<T>(s1, 0, 0, 0), gzVec4_<T>(0, s2, 0, 0), gzVec4_<T>(0, 0, s3, 0), gzVec4_<T>(0, 0, 0, s4));
	}

	static gzMatrix4_ translateMatrix(const T& x, const T& y, const T& z)
	{
		return gzMatrix4_<T>(gzVec4_<T>(1, 0, 0, 0), gzVec4_<T>(0, 1, 0, 0), gzVec4_<T>(0, 0, 1, 0), gzVec4_<T>(x, y, z, 1));
	}


	gzVec3_<T> scale() const
	{
		return gzVec3_<T>(gzSqrt<T>(v11 * v11 + v21 * v21 + v31 * v31), gzSqrt<T>(v12 * v12 + v22 * v22 + v32 * v32), gzSqrt<T>(v13 * v13 + v23 * v23 + v33 * v33));
	}

	gzQuaternion_<T>  quaternion() const
	{
		T d0 = v11;
		T d1 = v22;
		T d2 = v33;

		T P1 = 1 + d0 + d1 + d2;
		T P2 = 1 + d0 - d1 - d2;
		T P3 = 1 - d0 + d1 - d2;
		T P4 = 1 - d0 - d1 + d2;

		T q1, q2, q3, q4;

		if (P1 > P2)
		{
			if (P1 > P3)
			{
				if (P1 > P4)
				{
					q1 = gzSqrt(P1) / 2;
					q2 = (v32 - v23) / (4 * q1);
					q3 = (v13 - v31) / (4 * q1);
					q4 = (v21 - v12) / (4 * q1);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
			else
			{
				if (P3 > P4)
				{
					q3 = gzSqrt(P3) / 2;
					q1 = (v13 - v31) / (4 * q3);
					q2 = (v21 + v12) / (4 * q3);
					q4 = (v32 + v23) / (4 * q3);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
		}
		else
		{
			if (P2 > P3)
			{
				if (P2 > P4)
				{
					q2 = gzSqrt(P2) / 2;
					q1 = (v32 - v23) / (4 * q2);
					q3 = (v21 + v12) / (4 * q2);
					q4 = (v13 + v31) / (4 * q2);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
			else
			{
				if (P3 > P4)
				{
					q3 = gzSqrt(P3) / 2;
					q1 = (v13 - v31) / (4 * q3);
					q2 = (v21 + v12) / (4 * q3);
					q4 = (v32 + v23) / (4 * q3);
				}
				else
				{
					q4 = gzSqrt(P4) / 2;
					q1 = (v21 - v12) / (4 * q4);
					q2 = (v13 + v31) / (4 * q4);
					q3 = (v32 + v23) / (4 * q4);
				}
			}
		}

		if (q1 < 0)
		{
			q1 = -q1;
			q2 = -q2;
			q3 = -q3;
			q4 = -q4;
		}

		return gzQuaternion_<T>(q1, q2, q3, q4);
	}


	template <class Y> gzBool inverse(gzMatrix4_<Y>& pivot) const
	{
		// Calculate the inverse as fast as possible by a 4x4 matrix
		// Invented by Anders Modén

		// layout	v11 v12 v13 v14
		//			v21 v22 v23 v24
		//			v31 v32 v33 v34
		//			v41 v42 v43 v44


		const Y v3344(v33 * v44 - v43 * v34);
		const Y v2344(v23 * v44 - v43 * v24);
		const Y v2334(v23 * v34 - v33 * v24);
		const Y v3244(v32 * v44 - v42 * v34);
		const Y v2244(v22 * v44 - v42 * v24);
		const Y v2234(v22 * v34 - v32 * v24);
		const Y v3243(v32 * v43 - v42 * v33);
		const Y v2243(v22 * v43 - v42 * v23);
		const Y v2233(v22 * v33 - v32 * v23);

		pivot.v11 = v22 * v3344 - v32 * v2344 + v42 * v2334;
		pivot.v21 = -v21 * v3344 + v31 * v2344 - v41 * v2334;
		pivot.v31 = v21 * v3244 - v31 * v2244 + v41 * v2234;
		pivot.v41 = -v21 * v3243 + v31 * v2243 - v41 * v2233;

		const Y v1344(v13 * v44 - v43 * v14);
		const Y v1334(v13 * v34 - v33 * v14);
		const Y v1244(v12 * v44 - v42 * v14);
		const Y v1234(v12 * v34 - v32 * v14);
		const Y v1243(v12 * v43 - v42 * v13);
		const Y v1233(v12 * v33 - v32 * v13);
		const Y v1324(v13 * v24 - v23 * v14);
		const Y v1224(v12 * v24 - v22 * v14);
		const Y v1223(v12 * v23 - v22 * v13);

		pivot.v12 = -v12 * v3344 + v32 * v1344 - v42 * v1334;
		pivot.v22 = v11 * v3344 - v31 * v1344 + v41 * v1334;
		pivot.v32 = -v11 * v3244 + v31 * v1244 - v41 * v1234;
		pivot.v42 = v11 * v3243 - v31 * v1243 + v41 * v1233;

		pivot.v13 = v12 * v2344 - v22 * v1344 + v42 * v1324;
		pivot.v23 = -v11 * v2344 + v21 * v1344 - v41 * v1324;
		pivot.v33 = v11 * v2244 - v21 * v1244 + v41 * v1224;
		pivot.v43 = -v11 * v2243 + v21 * v1243 - v41 * v1223;

		pivot.v14 = -v12 * v2334 + v22 * v1334 - v32 * v1324;
		pivot.v24 = v11 * v2334 - v21 * v1334 + v31 * v1324;
		pivot.v34 = -v11 * v2234 + v21 * v1234 - v31 * v1224;
		pivot.v44 = v11 * v2233 - v21 * v1233 + v31 * v1223;


		Y det(v11 * pivot.v11 + v21 * pivot.v12 + v31 * pivot.v13 + v41 * pivot.v14);

		if (det == 0)
			return FALSE;

		det = GZ_FLOAT_ONE / det;

		pivot.v11 *= det;
		pivot.v12 *= det;
		pivot.v13 *= det;
		pivot.v14 *= det;

		pivot.v21 *= det;
		pivot.v22 *= det;
		pivot.v23 *= det;
		pivot.v24 *= det;

		pivot.v31 *= det;
		pivot.v32 *= det;
		pivot.v33 *= det;
		pivot.v34 *= det;

		pivot.v41 *= det;
		pivot.v42 *= det;
		pivot.v43 *= det;
		pivot.v44 *= det;

		return TRUE;
	}

	gzMatrix4_ unit() const
	{
		T len(determinant());

		if (len != 0)
		{
			T invlen(1 / len);
			return gzMatrix4_<T>(gzVec4_<T>(v11 * invlen, v21 * invlen, v31 * invlen, v41 * invlen), gzVec4_<T>(v12 * invlen, v22 * invlen, v32 * invlen, v42 * invlen), gzVec4_<T>(v13 * invlen, v23 * invlen, v33 * invlen, v43 * invlen), gzVec4_<T>(v14 * invlen, v24 * invlen, v34 * invlen, v44 * invlen));
		}
		else
			return  gzMatrix4_<T>(gzVec4_<T>(0, 0, 0, 0), gzVec4_<T>(0, 0, 0, 0), gzVec4_<T>(0, 0, 0, 0), gzVec4_<T>(0, 0, 0, 0));
	}

	gzMatrix4_ abs() const
	{
		return gzMatrix4_<T>(gzVec4_<T>(gzAbs(v11), gzAbs(v21), gzAbs(v31), gzAbs(v41)), gzVec4_<T>(gzAbs(v12), gzAbs(v22), gzAbs(v32), gzAbs(v42)), gzVec4_<T>(gzAbs(v13), gzAbs(v23), gzAbs(v33), gzAbs(v43)), gzVec4_<T>(gzAbs(v14), gzAbs(v24), gzAbs(v34), gzAbs(v44)));
	}

	gzMatrix4_ transpose() const
	{
		return gzMatrix4_<T>(gzVec4_<T>(v11, v12, v13, v14), gzVec4_<T>(v21, v22, v23, v24), gzVec4_<T>(v31, v32, v33, v34), gzVec4_<T>(v41, v42, v43, v44));
	}

	gzVoid normalize()
	{
		T len(determinant());

		if (!len)
			return;

		T invlen(1 / len);

		v11 = v11 * invlen;
		v12 = v12 * invlen;
		v13 = v13 * invlen;
		v14 = v14 * invlen;
		v21 = v21 * invlen;
		v22 = v22 * invlen;
		v23 = v23 * invlen;
		v24 = v24 * invlen;
		v31 = v31 * invlen;
		v32 = v32 * invlen;
		v33 = v33 * invlen;
		v34 = v34 * invlen;
		v41 = v41 * invlen;
		v42 = v42 * invlen;
		v43 = v43 * invlen;
		v44 = v44 * invlen;
	}

	template <class Y> gzBool operator==(const gzMatrix4_<Y>& right) const
	{
		if (gzAbs<T>(v11 - right.v11) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v12 - right.v12) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v13 - right.v13) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v14 - right.v14) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v21 - right.v21) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v22 - right.v22) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v23 - right.v23) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v24 - right.v24) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v31 - right.v31) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v32 - right.v32) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v33 - right.v33) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v34 - right.v34) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v41 - right.v41) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v42 - right.v42) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v43 - right.v43) > gzAritmetic_<T>::epsilon())
			return FALSE;
		if (gzAbs<T>(v44 - right.v44) > gzAritmetic_<T>::epsilon())
			return FALSE;
		return TRUE;
	}

	template <class Y> gzBool operator!=(const gzMatrix4_<Y>& right) const
	{
		return !operator==(right);
	}

	gzMatrix4_ operator-() noexcept(TRUE)
	{
		return gzMatrix4_<T>(
			gzVec4_<T>(-v11, -v21, -v31, -v41),
			gzVec4_<T>(-v12, -v22, -v32, -v42),
			gzVec4_<T>(-v13, -v23, -v33, -v43),
			gzVec4_<T>(-v14, -v24, -v34, -v44));
	}

	template <class Y> gzMatrix4_& operator+=(const gzMatrix4_<Y>& mat) noexcept(TRUE)
	{
		v11 += mat.v11;	v12 += mat.v12;	v13 += mat.v13;	v14 += mat.v14;
		v21 += mat.v21;	v22 += mat.v22;	v23 += mat.v23; v24 += mat.v24;
		v31 += mat.v31;	v32 += mat.v32;	v33 += mat.v33; v34 += mat.v34;
		v41 += mat.v41;	v42 += mat.v42;	v43 += mat.v43; v44 += mat.v44;

		return *this;
	}

	template <class Y> gzMatrix4_& operator-=(const gzMatrix4_<Y>& mat) noexcept(TRUE)
	{
		v11 -= mat.v11;	v12 -= mat.v12;	v13 -= mat.v13;	v14 -= mat.v14;
		v21 -= mat.v21;	v22 -= mat.v22;	v23 -= mat.v23; v24 -= mat.v24;
		v31 -= mat.v31;	v32 -= mat.v32;	v33 -= mat.v33; v34 -= mat.v34;
		v41 -= mat.v41;	v42 -= mat.v42;	v43 -= mat.v43; v44 -= mat.v44;

		return *this;
	}

	gzMatrix4_ operator * (const T& val) const noexcept(TRUE)
	{
		return gzMatrix4_<T>(
			gzVec4_<T>(val * v11, val * v21, val * v31, val * v41),
			gzVec4_<T>(val * v12, val * v22, val * v32, val * v42),
			gzVec4_<T>(val * v13, val * v23, val * v33, val * v43),
			gzVec4_<T>(val * v14, val * v24, val * v34, val * v44));
	}

	gzMatrix4_& operator *= (const T& val) noexcept(TRUE)
	{
		v11 *= val;	v12 *= val;	v13 *= val; v14 *= val;
		v21 *= val;	v22 *= val;	v23 *= val; v24 *= val;
		v31 *= val;	v32 *= val;	v33 *= val; v34 *= val;
		v41 *= val;	v42 *= val;	v43 *= val; v44 *= val;

		return *this;
	}

	gzMatrix4_	operator / (const T& val) const noexcept(TRUE)
	{
		T invlen(1 / val);
		return gzMatrix4_<T>(
			gzVec4_<T>(v11 * invlen, v21 * invlen, v31 * invlen, v41 * invlen),
			gzVec4_<T>(v12 * invlen, v22 * invlen, v32 * invlen, v42 * invlen),
			gzVec4_<T>(v13 * invlen, v23 * invlen, v33 * invlen, v43 * invlen),
			gzVec4_<T>(v14 * invlen, v24 * invlen, v34 * invlen, v44 * invlen));
	}


	template <class Y> gzMatrix4_ operator - (const gzMatrix4_<Y>& mat) const noexcept(TRUE)
	{
		gzMatrix4_<T> res;

		res.v11 = v11 - mat.v11;
		res.v12 = v12 - mat.v12;
		res.v13 = v13 - mat.v13;
		res.v14 = v14 - mat.v14;

		res.v21 = v21 - mat.v21;
		res.v22 = v22 - mat.v22;
		res.v23 = v23 - mat.v23;
		res.v24 = v24 - mat.v24;

		res.v31 = v31 - mat.v31;
		res.v32 = v32 - mat.v32;
		res.v33 = v33 - mat.v33;
		res.v34 = v34 - mat.v34;

		res.v41 = v41 - mat.v41;
		res.v42 = v42 - mat.v42;
		res.v43 = v43 - mat.v43;
		res.v44 = v44 - mat.v44;

		return res;
	}

	template <class Y> gzMatrix4_ operator + (const gzMatrix4_<Y>& mat) const noexcept(TRUE)
	{
		gzMatrix4_<T> res;

		res.v11 = v11 + mat.v11;
		res.v12 = v12 + mat.v12;
		res.v13 = v13 + mat.v13;
		res.v14 = v14 + mat.v14;

		res.v21 = v21 + mat.v21;
		res.v22 = v22 + mat.v22;
		res.v23 = v23 + mat.v23;
		res.v24 = v24 + mat.v24;

		res.v31 = v31 + mat.v31;
		res.v32 = v32 + mat.v32;
		res.v33 = v33 + mat.v33;
		res.v34 = v34 + mat.v34;

		res.v41 = v41 + mat.v41;
		res.v42 = v42 + mat.v42;
		res.v43 = v43 + mat.v43;
		res.v44 = v44 + mat.v44;

		return res;
	}

	template <class Y> gzMatrix4_ operator * (const gzMatrix4_<Y>& mat) const noexcept(TRUE)
	{
		gzMatrix4_<T> res;

		res.v11 = v11 * mat.v11 + v12 * mat.v21 + v13 * mat.v31 + v14 * mat.v41;
		res.v12 = v11 * mat.v12 + v12 * mat.v22 + v13 * mat.v32 + v14 * mat.v42;
		res.v13 = v11 * mat.v13 + v12 * mat.v23 + v13 * mat.v33 + v14 * mat.v43;
		res.v14 = v11 * mat.v14 + v12 * mat.v24 + v13 * mat.v34 + v14 * mat.v44;

		res.v24 = v21 * mat.v14 + v22 * mat.v24 + v23 * mat.v34 + v24 * mat.v44;
		res.v23 = v21 * mat.v13 + v22 * mat.v23 + v23 * mat.v33 + v24 * mat.v43;
		res.v22 = v21 * mat.v12 + v22 * mat.v22 + v23 * mat.v32 + v24 * mat.v42;
		res.v21 = v21 * mat.v11 + v22 * mat.v21 + v23 * mat.v31 + v24 * mat.v41;

		res.v31 = v31 * mat.v11 + v32 * mat.v21 + v33 * mat.v31 + v34 * mat.v41;
		res.v32 = v31 * mat.v12 + v32 * mat.v22 + v33 * mat.v32 + v34 * mat.v42;
		res.v33 = v31 * mat.v13 + v32 * mat.v23 + v33 * mat.v33 + v34 * mat.v43;
		res.v34 = v31 * mat.v14 + v32 * mat.v24 + v33 * mat.v34 + v34 * mat.v44;

		res.v44 = v41 * mat.v14 + v42 * mat.v24 + v43 * mat.v34 + v44 * mat.v44;
		res.v43 = v41 * mat.v13 + v42 * mat.v23 + v43 * mat.v33 + v44 * mat.v43;
		res.v42 = v41 * mat.v12 + v42 * mat.v22 + v43 * mat.v32 + v44 * mat.v42;
		res.v41 = v41 * mat.v11 + v42 * mat.v21 + v43 * mat.v31 + v44 * mat.v41;

		return res;
	}

	template <class Y> gzVec4_<T> operator * (const gzVec4_<Y>& vec) const noexcept(TRUE)
	{
		gzVec4_<T> res;

		res.v1 = v11 * vec.v1 + v12 * vec.v2 + v13 * vec.v3 + v14 * vec.v4;
		res.v2 = v21 * vec.v1 + v22 * vec.v2 + v23 * vec.v3 + v24 * vec.v4;
		res.v3 = v31 * vec.v1 + v32 * vec.v2 + v33 * vec.v3 + v34 * vec.v4;
		res.v4 = v41 * vec.v1 + v42 * vec.v2 + v43 * vec.v3 + v44 * vec.v4;

		return res;
	}

	template <class Y> gzVec4_<T> operator * (const gzVec3_<Y>& vec) const noexcept(TRUE)
	{
		gzVec4_<T> res;

		res.v1 = v11 * vec.v1 + v12 * vec.v2 + v13 * vec.v3 + v14;
		res.v2 = v23 * vec.v3 + v22 * vec.v2 + v21 * vec.v1 + v24;
		res.v3 = v33 * vec.v3 + v32 * vec.v2 + v31 * vec.v1 + v34;
		res.v4 = v41 * vec.v1 + v42 * vec.v2 + v43 * vec.v3 + v44;

		return res;
	}

	gzString asString(const gzString& format = "[[%lf,%lf,%lf,%lf][%lf,%lf,%lf,%lf][%lf,%lf,%lf,%lf][%lf,%lf,%lf,%lf]]") const
	{
		gzString result;
		return result.format(format, v11, v12, v13, v14, v21, v22, v23, v24, v31, v32, v33, v34, v41, v42, v43, v44);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&v11)) + (*((gzUInt32*)gzPtr2Val(&v22)) << 1) + (*((gzUInt32*)gzPtr2Val(&v33)) << 2) + (*((gzUInt32*)gzPtr2Val(&v44)) << 3);
	}

	T sum()
	{
		return	v11 + v12 + v13 + v14 +
			v21 + v22 + v23 + v24 +
			v31 + v32 + v33 + v34 +
			v41 + v42 + v43 + v44;
	}


	static gzMatrix4_ euler_yxz(const T& y_rot, const T& x_rot, const T& z_rot, gzVec3_<T> translation = gzVec3_<T>(0, 0, 0))
	{
		T y_s(sin(y_rot)), y_c(cos(y_rot));
		T x_s(sin(x_rot)), x_c(cos(x_rot));
		T z_s(sin(z_rot)), z_c(cos(z_rot));

		gzMatrix4_<T> mat;

		mat.v11 = x_s * y_s * z_s + y_c * z_c;
		mat.v12 = x_s * y_s * z_c - y_c * z_s;
		mat.v13 = x_c * y_s;
		mat.v14 = translation.x;
		mat.v21 = z_s * x_c;
		mat.v22 = z_c * x_c;
		mat.v23 = -x_s;
		mat.v24 = translation.y;
		mat.v31 = x_s * y_c * z_s - y_s * z_c;
		mat.v32 = x_s * y_c * z_c + y_s * z_s;
		mat.v33 = x_c * y_c;
		mat.v34 = translation.z;
		mat.v41 = 0;
		mat.v42 = 0;
		mat.v43 = 0;
		mat.v44 = 1;


		return mat;
	}

	static gzMatrix4_ euler_zxy(const T& z_rot, const T& x_rot, const T& y_rot, gzVec3_<T> translation = gzVec3_<T>(0, 0, 0))
	{
		T y_s(sin(y_rot)), y_c(cos(y_rot));
		T x_s(sin(x_rot)), x_c(cos(x_rot));
		T z_s(sin(z_rot)), z_c(cos(z_rot));

		gzMatrix4_<T> mat;

		mat.v11 = -x_s * y_s * z_s + y_c * z_c;
		mat.v12 = -z_s * x_c;
		mat.v13 = x_s * y_c * z_s + y_s * z_c;
		mat.v14 = translation.x;
		mat.v21 = x_s * y_s * z_c + y_c * z_s;
		mat.v22 = z_c * x_c;
		mat.v23 = -x_s * y_c * z_c + y_s * z_s;
		mat.v24 = translation.y;
		mat.v31 = -x_c * y_s;
		mat.v32 = x_s;
		mat.v33 = x_c * y_c;
		mat.v34 = translation.z;
		mat.v41 = 0;
		mat.v42 = 0;
		mat.v43 = 0;
		mat.v44 = 1;


		return mat;
	}

	// Columnwize storage

	T v11, v21, v31, v41;
	T v12, v22, v32, v42;
	T v13, v23, v33, v43;
	T v14, v24, v34, v44;
};

template <class T> inline gzMatrix4_<T> operator * (const T& val, const gzMatrix4_<T>& mat)
{
	gzMatrix4_<T> res;

	res.v11 = val * mat.v11;
	res.v12 = val * mat.v12;
	res.v13 = val * mat.v13;
	res.v14 = val * mat.v14;

	res.v21 = val * mat.v21;
	res.v22 = val * mat.v22;
	res.v23 = val * mat.v23;
	res.v24 = val * mat.v24;

	res.v31 = val * mat.v31;
	res.v32 = val * mat.v32;
	res.v33 = val * mat.v33;
	res.v34 = val * mat.v34;

	res.v41 = val * mat.v41;
	res.v42 = val * mat.v42;
	res.v43 = val * mat.v43;
	res.v44 = val * mat.v44;

	return res;
}

typedef gzMatrix4_<gzFloat>		gzMatrix4;
typedef gzMatrix4_<gzDouble>	gzMatrix4D;





template <class T, class Y> inline gzVec4_<T> operator * (const gzVec4_<T>& vec, const gzMatrix4_<Y>& mat)
{
	gzVec4_<T> res;

	res.v1 = mat.v11 * vec.v1 + mat.v21 * vec.v2 + mat.v31 * vec.v3 + mat.v41 * vec.v4;
	res.v2 = mat.v12 * vec.v1 + mat.v22 * vec.v2 + mat.v32 * vec.v3 + mat.v42 * vec.v4;
	res.v3 = mat.v13 * vec.v1 + mat.v23 * vec.v2 + mat.v33 * vec.v3 + mat.v43 * vec.v4;
	res.v4 = mat.v14 * vec.v1 + mat.v24 * vec.v2 + mat.v34 * vec.v3 + mat.v44 * vec.v4;

	return res;
}


//******************************************************************************
// Class	: gzQuaternion_
//									
// Purpose  : template class for Quaternions 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	191105	Created  (2.10.4)
//									
//******************************************************************************
template <class T> class gzQuaternion_
{
public:

	// Default to unit quat
	gzQuaternion_(const T& _w = 1, const T& _x = 0, const T& _y = 0, const T& _z = 0) :w(_w), x(_x), y(_y), z(_z) {}

	gzQuaternion_(const gzVec4_<T>& vec) :w(vec.w), x(vec.x), y(vec.y), z(vec.z) {}

	template <class Y> explicit operator gzQuaternion_<Y>() const { return gzQuaternion_<Y>((Y)w, (Y)x, (Y)y, (Y)z); }

	template <class Y> gzQuaternion_<T>& operator=(const gzQuaternion_<Y>& copy) { w = copy.w; x = copy.x; y = copy.y; z = copy.z; return *this; }

	// rotation angle is double arg , rot angle=arg*2 
	gzQuaternion_(const T& arg, const gzVec3_<T>& n, const T& norm = 1)
	{
		T len = n.length();

		if (!len)
			len = 1;

		T s = norm * sin(arg);

		w = norm * cos(arg);

		x = n.x * s / len;
		y = n.y * s / len;
		z = n.z * s / len;
	}

	gzBool operator==(const gzQuaternion_<T>& right)		const
	{
		return (w == right.w) && (x == right.x) && (y == right.y) && (z == right.z);
	}

	gzBool operator!=(const gzQuaternion_<T>& right)		const
	{
		return (w != right.w) || (x != right.x) || (y != right.y) || (z != right.z);
	}

	gzQuaternion_<T> operator *(const gzQuaternion_<T>& B)	const
	{
		return gzQuaternion_<T>(w * B.w - x * B.x - y * B.y - z * B.z,
			w * B.x + x * B.w + y * B.z - z * B.y,
			w * B.y - x * B.z + y * B.w + z * B.x,
			w * B.z + x * B.y - y * B.x + z * B.w);
	}

	gzQuaternion_<T> operator +(const gzQuaternion_<T>& B)	const
	{
		return gzQuaternion_<T>(w + B.w, x + B.x, y + B.y, z + B.z);
	}

	gzQuaternion_<T> operator -(const gzQuaternion_<T>& B)	const
	{
		return gzQuaternion_<T>(w - B.w, x - B.x, y - B.y, z - B.z);
	}

	gzQuaternion_<T> operator *(const T& val)				const
	{
		return gzQuaternion_<T>(w * val, x * val, y * val, z * val);
	}

	gzQuaternion_<T> operator /(const T& val)				const
	{
		return gzQuaternion_<T>(w / val, x / val, y / val, z / val);
	}

	gzVec3_<T> operator *(const gzVec3_<T>& vec)			const
	{
		return rotationMatrix() * vec;
	}

	gzQuaternion_<T>	conj()								const
	{
		return gzQuaternion_<T>(w, -x, -y, -z);
	}

	gzQuaternion_<T>	unit()								const
	{
		T l = norm();

		return gzQuaternion_<T>(w / l, x / l, y / l, z / l);
	}

	gzQuaternion_<T>	recip()								const
	{
		T l2 = normSq2();

		return gzQuaternion_<T>(w / l2, -x / l2, -y / l2, -z / l2);
	}

	gzQuaternion_<T>	pow(const T& val)					const
	{
		return gzQuaternion_<T>(arg() * val, vec(), (T)::pow(norm(), val));
	}

	gzQuaternion_<T>	exp()								const
	{
		T vnorm = gzSqrt(gzSq2(x) + gzSq2(y) + gzSq2(z));

		T vfactor = sin(vnorm) / vnorm;

		return gzQuaternion_<T>(exp(w) * cos(vnorm), x * vfactor, y * vfactor, z * vfactor);
	}

	gzQuaternion_<T>	ln()								const
	{
		T vnorm = gzSqrt(gzSq2(x) + gzSq2(y) + gzSq2(z));

		T qlen = norm();

		T vfactor = acos(w / qlen) / vnorm;

		return gzQuaternion_(log(qlen), x * vfactor, y * vfactor, z * vfactor);
	}

	gzQuaternion_<T>	slerp(const gzQuaternion_<T>& B, const T& val) const
	{
		return operator * ((recip() * B).pow(val));
	}

	gzVec3_<T>	vec()							const
	{
		T mag = gzSqrt(gzSq2(x) + gzSq2(y) + gzSq2(z));

		if (mag > 0)
			return gzVec3_<T>(x, y, z) / mag;
		else
			return gzVec3_<T>(0, 0, 0);
	}

	gzVec3_<T>	xyz()							const
	{
		return gzVec3_<T>(x, y, z);
	}

	gzVec4_<T>	xyzw()							const
	{
		return gzVec4_<T>(x, y, z, w);
	}

	T arg()										const
	{
		return (T)acos(w / norm());
	}

	T norm()									const
	{
		return gzSqrt(gzSq2(w) + gzSq2(x) + gzSq2(y) + gzSq2(z));
	}

	T normSq2()									const
	{
		return gzSq2(w) + gzSq2(x) + gzSq2(y) + gzSq2(z);
	}

	T dist(const gzQuaternion_<T>& right)		const
	{
		return gzSqrt(gzSq2(w - right.w) + gzSq2(x - right.x) + gzSq2(y - right.y) + gzSq2(z - right.z));
	}

	gzMatrix3_<T>	rotationMatrix()			const
	{
		return gzMatrix3_<T>(gzVec3_<T>(w * w + x * x - y * y - z * z, 2 * (x * y + w * z), 2 * (x * z - w * y)),
			gzVec3_<T>(2 * (x * y - w * z), w * w - x * x + y * y - z * z, 2 * (y * z + w * x)),
			gzVec3_<T>(2 * (x * z + w * y), 2 * (y * z - w * x), w * w - x * x - y * y + z * z));
	}

	gzVoid	normalize()
	{
		T f(1 - (w * w + x * x + y * y + z * z - 1) / 2);

		if (f < 0.999 || f>1.001)
			f = 1 / norm();

		w *= f;
		x *= f;
		y *= f;
		z *= f;
	}

	gzVec3_<T> rate(const T& dT = (T)1, const gzQuaternion_<T>& from = gzQuaternion_<T>()) const
	{
		return (operator-(from) * 2 / dT * from.conj()).xyz();
	}

	gzString asString(const gzString& format = "{%lf,%lf,%lf,%lf}") const
	{
		gzString result;
		return result.format(format, w, x, y, z);
	}

	gzUInt32	hash()	const
	{
		return *((gzUInt32*)gzPtr2Val(&w)) + (*((gzUInt32*)gzPtr2Val(&x)) << 1) + (*((gzUInt32*)gzPtr2Val(&y)) << 2) + (*((gzUInt32*)gzPtr2Val(&z)) << 3);
	}

	static gzQuaternion_<T>	rotation(const gzVec3_<T>& from, const gzVec3_<T>& to)
	{
		gzVec3_<T> cross = from.cross(to);

		gzQuaternion_<T> quat(gzSqrt<T>(from.lengthSq2() * to.lengthSq2()) + from.dot(to), cross.x, cross.y, cross.z);

		quat.normalize();

		return quat;
	}

	static gzQuaternion_<T>	from_euler_yxz(const T& heading = 0, const T& pitch = 0, const T& roll = 0)
	{
		return gzMatrix3_<T>::euler_yxz(heading, pitch, roll).quaternion();
	}

	static gzQuaternion_<T>	from_euler_zxy(const T& heading = 0, const T& pitch = 0, const T& roll = 0)
	{
		return gzMatrix3_<T>::euler_zxy(heading, pitch, roll).quaternion();
	}

	static gzQuaternion_<T>	from_euler_xyz(const T& heading = 0, const T& pitch = 0, const T& roll = 0)
	{
		return gzMatrix3_<T>::euler_xyz(heading, pitch, roll).quaternion();
	}

	gzVoid	decompose_euler_yxz(T& heading, T& pitch, T& roll) const
	{
		rotationMatrix().decompose_euler_yxz(heading, pitch, roll);
	}

	gzVoid	decompose_euler_zxy(T& heading, T& pitch, T& roll) const
	{
		rotationMatrix().decompose_euler_zxy(heading, pitch, roll);
	}

	gzVoid	decompose_euler_xyz(T& heading, T& pitch, T& roll) const
	{
		rotationMatrix().decompose_euler_xyz(heading, pitch, roll);
	}


	T w, x, y, z;
};



typedef gzQuaternion_<gzFloat>	gzQuaternion;
typedef gzQuaternion_<gzDouble>	gzQuaternionD;

// Quat Consts ------------------

const gzQuaternion GZ_ZERO_QUAT = gzQuaternion(0, 0, 0, 0);

// -------------------------------------- Misc ----------------------------------------------------

GZ_BASE_EXPORT gzVec3  multiply(const gzMatrix4& mat, const gzVec3& vec); //!< default w=1, cast to gzVec3
GZ_BASE_EXPORT gzVec3D multiply(const gzMatrix4& mat, const gzVec3D& vec); //!< default w=1, cast to gzVec3D
GZ_BASE_EXPORT gzVec3  multiply(const gzMatrix4& mat, const gzVec3& vec, const gzFloat& w); //!< default w=1, cast to gzVec3
GZ_BASE_EXPORT gzVec3  normweight(const gzMatrix4& mat, const gzVec3& vec, const gzFloat& w = GZ_FLOAT_ONE); //!< default w=1, cast to gzVec3

// Utilities -----------------------------------------------------------

//! Returns a unit gzMatrix4 instance
GZ_BASE_EXPORT const gzMatrix4& gzGetUnitMatrix() noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetVectorRotation(const gzMatrix4& mat, gzVec3& vec, gzFloat& angle, const gzVec3& base = GZ_ONE_VEC3) noexcept(TRUE);
GZ_BASE_EXPORT gzVoid gzGetTranslationMatrix(gzMatrix4& matrix, gzFloat dx, gzFloat dy, gzFloat dz) noexcept(TRUE);
GZ_BASE_EXPORT gzVoid gzGetTranslationMatrix(gzMatrix4& matrix, const gzVec3& translation) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetScaleMatrix(gzMatrix4& matrix, gzFloat dx, gzFloat dy, gzFloat dz) noexcept(TRUE);
GZ_BASE_EXPORT gzVoid gzGetScaleMatrix(gzMatrix4& matrix, const gzVec3& scale) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetBaseMatrix(gzMatrix4& matrix, const gzVec3& base) noexcept(TRUE);
GZ_BASE_EXPORT gzVoid gzGetBaseMatrix(gzMatrix4& matrix, const gzVec3& x_base, const gzVec3& y_base) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetRotationMatrix(gzMatrix4& matrix, const gzVec3& base, gzFloat angle)noexcept(TRUE);
GZ_BASE_EXPORT gzVoid gzGetRotationMatrix(gzMatrix4& matrix, gzFloat heading, gzFloat pitch, gzFloat roll) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetHPR(const gzMatrix4& matrix, gzFloat& heading, gzFloat& pitch, gzFloat& roll) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetRotationMatrix(gzMatrix4& matrix, const gzVec3& orientation) noexcept(TRUE);

GZ_BASE_EXPORT gzVoid gzGetBiasMatrix(gzMatrix4& matrix, gzFloat x_factor = 1.0f, gzFloat x_offset = 0.0f,
	gzFloat y_factor = 1.0f, gzFloat y_offset = 0.0f,
	gzFloat z_factor = 1.0f, gzFloat z_offset = 0.0f);

GZ_BASE_EXPORT gzBool gzIsPureTranslation(const gzMatrix4& matrix, gzVec3& translation);

GZ_BASE_EXPORT inline gzFloat gzGetNormDot(const gzVec3& a, const gzVec3& b, const gzVec3& c, const gzVec3& dir) noexcept(TRUE)
{
	gzFloat x1(b.v1 - a.v1);
	gzFloat y1(c.v1 - a.v1);

	gzFloat x2(b.v2 - a.v2);
	gzFloat y2(c.v2 - a.v2);

	gzFloat x3(b.v3 - a.v3);
	gzFloat y3(c.v3 - a.v3);

	return (x2 * y3 - x3 * y2) * dir.v1 + (x3 * y1 - x1 * y3) * dir.v2 + (x1 * y2 - x2 * y1) * dir.v3;
}


GZ_BASE_EXPORT inline gzVoid getExtendedVector(gzVec3& dest, const gzVec3& from, const gzVec3& to, const gzFloat& lengthSq2) noexcept(TRUE)
{
	dest.v1 = (to.v1 - from.v1) * lengthSq2 + to.v1;
	dest.v2 = (to.v2 - from.v2) * lengthSq2 + to.v2;
	dest.v3 = (to.v3 - from.v3) * lengthSq2 + to.v3;
}


//--------------------------------- Template Specifics ------------------------------------------------------

// -------------------------------- copyInstances -----------------------------------------------------------

template <> inline gzVoid copyInstances(gzVec2* to, gzVec2* from, gzUInt32 count, gzBool /*clearSource*/)
{
	memmove(to, from, count * sizeof(gzVec2));
}

template <> inline gzVoid copyInstances(gzVec3* to, gzVec3* from, gzUInt32 count, gzBool /*clearSource*/)
{
	memmove(to, from, count * sizeof(gzVec3));
}

template <> inline gzVoid copyInstances(gzVec4* to, gzVec4* from, gzUInt32 count, gzBool /*clearSource*/)
{
	memmove(to, from, count * sizeof(gzVec4));
}

// ---------------------------- End of template specifics ---------------------------------------------------


#endif // __GZ_MATRIX_H__
