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
// File			: gzArgument.h
// Module		: gzBase
// Description	: Class definition of gzArgument
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
// AMO	980819	Created file 	
//
//******************************************************************************

#ifndef __GZ_ARGUMENT_H__
#define __GZ_ARGUMENT_H__

/*!	\file 
	\brief Argument class definition to avoid ... (ellipse args)

We want to avoid usage of eclipse arguments as using unlimited number of arguments on the stack can allow faulty calls

*/

class gzString; // Forward declaration

class  gzArgument	// Shall only be used as arguments as they refer to volatile values (non references values)
{
public:
	GZ_BASE_EXPORT gzArgument(const gzDouble	&value);
	GZ_BASE_EXPORT gzArgument(const gzByte		&value);
	GZ_BASE_EXPORT gzArgument(const gzUByte		&value);
	GZ_BASE_EXPORT gzArgument(const gzUInt16	&value);
	GZ_BASE_EXPORT gzArgument(const gzInt16		&value);
	GZ_BASE_EXPORT gzArgument(const gzUInt32	&value);
	GZ_BASE_EXPORT gzArgument(const gzInt32		&value);
	GZ_BASE_EXPORT gzArgument(const gzVoid		*value);
	GZ_BASE_EXPORT gzArgument(const gzInt64		&value);
	GZ_BASE_EXPORT gzArgument(const gzUInt64	&value);
	GZ_BASE_EXPORT gzArgument(const gzString	&value);

	//! Special platform build dependant
	GZ_BASE_EXPORT gzArgument(const unsigned long	&value);
	GZ_BASE_EXPORT gzArgument(const signed long		&value);

	GZ_BASE_EXPORT inline gzArgument() : m_type(GZ_ARG_VOID) { m_value.uvalue = 0; }

	GZ_BASE_EXPORT operator gzDouble	() const;
	GZ_BASE_EXPORT operator gzVoid *	() const;
	GZ_BASE_EXPORT gzInt64	getInt64	()	const;
	GZ_BASE_EXPORT gzUInt64	getUInt64	()	const;
	GZ_BASE_EXPORT gzString &	getString()	const;

	GZ_BASE_EXPORT gzBool isVoid()		const;
	GZ_BASE_EXPORT gzBool isDouble()	const;
	GZ_BASE_EXPORT gzBool isPointer()	const;
	GZ_BASE_EXPORT gzBool isInt64()	const;
	GZ_BASE_EXPORT gzBool isUInt64()	const;
	GZ_BASE_EXPORT gzBool isString()	const;

private:

	enum { GZ_ARG_VOID , GZ_ARG_DOUBLE , GZ_ARG_POINTER , GZ_ARG_INT64,GZ_ARG_UINT64,GZ_ARG_STRING};

	union values
	{
		gzDouble	dvalue;
		gzInt64		lvalue;
		gzUInt64	uvalue;
		gzString	*string;
	} m_value;

	gzUByte	 m_type;
};

#define ARG_DEF_DECL(n) const gzArgument &a##n=gzArgument()
#define ARG_DEF_DECL_E(n) const gzArgument & /*a##n*/=gzArgument()
#define ARG_DEF_BODY(n) const gzArgument &a##n

#define ARG_DECL_LIST	ARG_DEF_DECL(0) , \
						ARG_DEF_DECL(1) , \
						ARG_DEF_DECL(2) , \
						ARG_DEF_DECL(3) , \
						ARG_DEF_DECL(4) , \
						ARG_DEF_DECL(5) , \
						ARG_DEF_DECL(6) , \
						ARG_DEF_DECL(7) , \
						ARG_DEF_DECL(8) , \
						ARG_DEF_DECL(9) , \
						ARG_DEF_DECL(10) , \
						ARG_DEF_DECL(11) , \
						ARG_DEF_DECL(12) , \
						ARG_DEF_DECL(13) , \
						ARG_DEF_DECL(14) , \
						ARG_DEF_DECL(15) 

#define ARG_DECL_LIST_E	ARG_DEF_DECL_E(0) , \
						ARG_DEF_DECL_E(1) , \
						ARG_DEF_DECL_E(2) , \
						ARG_DEF_DECL_E(3) , \
						ARG_DEF_DECL_E(4) , \
						ARG_DEF_DECL_E(5) , \
						ARG_DEF_DECL_E(6) , \
						ARG_DEF_DECL_E(7) , \
						ARG_DEF_DECL_E(8) , \
						ARG_DEF_DECL_E(9) , \
						ARG_DEF_DECL_E(10) , \
						ARG_DEF_DECL_E(11) , \
						ARG_DEF_DECL_E(12) , \
						ARG_DEF_DECL_E(13) , \
						ARG_DEF_DECL_E(14) , \
						ARG_DEF_DECL_E(15) 

#define ARG_BODY_LIST	ARG_DEF_BODY(0) , \
						ARG_DEF_BODY(1) , \
						ARG_DEF_BODY(2) , \
						ARG_DEF_BODY(3) , \
						ARG_DEF_BODY(4) , \
						ARG_DEF_BODY(5) , \
						ARG_DEF_BODY(6) , \
						ARG_DEF_BODY(7) , \
						ARG_DEF_BODY(8) , \
						ARG_DEF_BODY(9) , \
						ARG_DEF_BODY(10) , \
						ARG_DEF_BODY(11) , \
						ARG_DEF_BODY(12) , \
						ARG_DEF_BODY(13) , \
						ARG_DEF_BODY(14) , \
						ARG_DEF_BODY(15) 

#define ARG_TRANSFER	a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15


#endif // __GZ_ARGUMENT_H__







