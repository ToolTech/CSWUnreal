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
// File			: gzUniqueStrings.h
// Module		: gzBase
// Description	: Class definition of all unique strings in GizmoBase
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
// AMO	180323	Created file
//
// ******************************************************************************

#ifndef __GZ_UNIQUE_STRINGS_H__
#define __GZ_UNIQUE_STRINGS_H__

#include "gzBase.h"

//----------------------- Unique ID definitions for gizmo dynamic type -----------------------

const gzUInt16 GZ_DYNAMIC_TYPE_STRING_UNIQUE_ID				= 1;
const gzUInt16 GZ_DYNAMIC_TYPE_VOID_UNIQUE_ID				= 2;
const gzUInt16 GZ_DYNAMIC_TYPE_NUMBER_UNIQUE_ID				= 3;
const gzUInt16 GZ_DYNAMIC_TYPE_POINTER_UNIQUE_ID			= 4;
const gzUInt16 GZ_DYNAMIC_TYPE_REFERENCE_UNIQUE_ID			= 5;
const gzUInt16 GZ_DYNAMIC_TYPE_ERROR_UNIQUE_ID				= 6;
const gzUInt16 GZ_DYNAMIC_TYPE_INT64_UNIQUE_ID				= 7;
const gzUInt16 GZ_DYNAMIC_TYPE_ARRAY_UNIQUE_ID				= 8;
const gzUInt16 GZ_DYNAMIC_TYPE_VEC2_UNIQUE_ID				= 9;
const gzUInt16 GZ_DYNAMIC_TYPE_VEC3_UNIQUE_ID				= 10;
const gzUInt16 GZ_DYNAMIC_TYPE_VEC4_UNIQUE_ID				= 11;
const gzUInt16 GZ_DYNAMIC_TYPE_CONTAINER_UNIQUE_ID			= 12;
const gzUInt16 GZ_DYNAMIC_TYPE_CHAIN_UNIQUE_ID				= 13;
const gzUInt16 GZ_DYNAMIC_ERROR_VALUE_NOT_SET_UNIQUE_ID		= 14;
const gzUInt16 GZ_DYNAMIC_ERROR_NOT_IMPLEMENTED_UNIQUE_ID	= 15;
const gzUInt16 GZ_DYNAMIC_ERROR_NO_ERROR_UNIQUE_ID			= 16;
const gzUInt16 GZ_DYNAMIC_ERROR_TEST_OK_UNIQUE_ID			= 17;
const gzUInt16 GZ_DYNAMIC_ERROR_TEST_FAIL_UNIQUE_ID			= 18;
const gzUInt16 GZ_DYNAMIC_TYPE_GUID_UNIQUE_ID				= 19;
const gzUInt16 GZ_DYNAMIC_TYPE_TIME_TAGGED_UNIQUE_ID		= 20;

// 28,29 are free
// 38,39 are free

const gzUInt16 GZ_DYNAMIC_TYPE_LATPOS_UNIQUE_ID				= 30;		// gzCoordinate
const gzUInt16 GZ_DYNAMIC_TYPE_CARTPOS_UNIQUE_ID			= 31;
const gzUInt16 GZ_DYNAMIC_TYPE_PROJPOS_UNIQUE_ID			= 32;
const gzUInt16 GZ_DYNAMIC_TYPE_UTMPOS_UNIQUE_ID				= 33;


const gzUInt16 GZ_DYNAMIC_TYPE_VEC2D_UNIQUE_ID				= 34;
const gzUInt16 GZ_DYNAMIC_TYPE_VEC3D_UNIQUE_ID				= 35;
const gzUInt16 GZ_DYNAMIC_TYPE_VEC4D_UNIQUE_ID				= 36;	
const gzUInt16 GZ_DYNAMIC_TYPE_QUAT_UNIQUE_ID				= 37;		// CURRENT LAST ID for base

// 01-27 is located in this file
// 30-33 is located in gzCoordinate::gzDynamicTypes.h
// 34-37 is located in this file as we needed more
// 40-74 is located in gzGraph::gzShader.h
// 75    is located in gzDistribution::gzDistDebug.h
// 76-86 is located in gzGraph::gzShader.h
// 90-95 is located in gzDistribution::gzDistBase.h


// Note! Unique ID are continued below ----------------------------

//----------------------- general dynamic type -------------------------------------

const gzString	GZ_DYNAMIC_TYPE_STRING		=gzUniqueString("str"	,GZ_DYNAMIC_TYPE_STRING_UNIQUE_ID);	// System defined strings
const gzString	GZ_DYNAMIC_TYPE_VOID		=gzUniqueString("void"	,GZ_DYNAMIC_TYPE_VOID_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_NUMBER		=gzUniqueString("num"	,GZ_DYNAMIC_TYPE_NUMBER_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_POINTER		=gzUniqueString("ptr"	,GZ_DYNAMIC_TYPE_POINTER_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_REFERENCE	=gzUniqueString("ref"	,GZ_DYNAMIC_TYPE_REFERENCE_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_ERROR		=gzUniqueString("error"	,GZ_DYNAMIC_TYPE_ERROR_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_INT64		=gzUniqueString("llnum"	,GZ_DYNAMIC_TYPE_INT64_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_ARRAY		=gzUniqueString("array"	,GZ_DYNAMIC_TYPE_ARRAY_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_VEC2		=gzUniqueString("vec2"	,GZ_DYNAMIC_TYPE_VEC2_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_VEC3		=gzUniqueString("vec3"	,GZ_DYNAMIC_TYPE_VEC3_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_VEC4		=gzUniqueString("vec4"	,GZ_DYNAMIC_TYPE_VEC4_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_CONTAINER	=gzUniqueString("cont"	,GZ_DYNAMIC_TYPE_CONTAINER_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_CHAIN		=gzUniqueString("chain"	,GZ_DYNAMIC_TYPE_CHAIN_UNIQUE_ID);	// Chain the command to a higher level of command
const gzString	GZ_DYNAMIC_TYPE_GUID		=gzUniqueString("guid"	,GZ_DYNAMIC_TYPE_GUID_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_TIME_TAGGED	=gzUniqueString("ttag"	,GZ_DYNAMIC_TYPE_TIME_TAGGED_UNIQUE_ID);

const gzString	GZ_DYNAMIC_TYPE_VEC2D		=gzUniqueString("vec2D"	,GZ_DYNAMIC_TYPE_VEC2D_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_VEC3D		=gzUniqueString("vec3D"	,GZ_DYNAMIC_TYPE_VEC3D_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_VEC4D		=gzUniqueString("vec4D"	,GZ_DYNAMIC_TYPE_VEC4D_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_QUAT		=gzUniqueString("quat"	,GZ_DYNAMIC_TYPE_QUAT_UNIQUE_ID);

//! Rule delimiter for EBNF rules
const gzString	GZ_RULE_DELIMITER		= gzUniqueString("::=",21);
const gzString	GZ_PUSH_TOKEN			= gzUniqueString("$",22);
const gzString	GZ_MISSING_IDENTIFIER	= gzUniqueString("Missing Identifier",23);

//! Unique ID for common array types

const gzString	GZ_DYNAMIC_TYPE_ARRAY_UBYTE	= gzUniqueString("UByteArray", 24);
const gzString	GZ_DYNAMIC_TYPE_ARRAY_FLOAT = gzUniqueString("FloatArray", 25);

//! Unique ID for common XY types

const gzString	GZ_DYNAMIC_TYPE_XY_FLOAT = gzUniqueString("FloatXY", 26);
const gzUInt16	GZ_DYNAMIC_ERROR_FAIL_UNIQUE_ID = 27;		

//! gzCoordinate strings
const gzString	GZ_DYNAMIC_TYPE_LATPOS	= gzUniqueString("LatPos", GZ_DYNAMIC_TYPE_LATPOS_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_CARTPOS = gzUniqueString("CartPos", GZ_DYNAMIC_TYPE_CARTPOS_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_PROJPOS = gzUniqueString("ProjPos", GZ_DYNAMIC_TYPE_PROJPOS_UNIQUE_ID);
const gzString	GZ_DYNAMIC_TYPE_UTMPOS	= gzUniqueString("UTMPos", GZ_DYNAMIC_TYPE_UTMPOS_UNIQUE_ID);

//------------------ gzDynamicTypeError standard values -----------------------

const gzString GZ_DYNAMIC_ERROR_VALUE_NOT_SET		= gzUniqueString("Value not set",	GZ_DYNAMIC_ERROR_VALUE_NOT_SET_UNIQUE_ID);
const gzString GZ_DYNAMIC_ERROR_NOT_IMPLEMENTED		= gzUniqueString("Not implemented", GZ_DYNAMIC_ERROR_NOT_IMPLEMENTED_UNIQUE_ID);
const gzString GZ_DYNAMIC_ERROR_NO_ERROR			= gzUniqueString("OK",				GZ_DYNAMIC_ERROR_NO_ERROR_UNIQUE_ID);
const gzString GZ_DYNAMIC_ERROR_FAIL				= gzUniqueString("FAIL",			GZ_DYNAMIC_ERROR_FAIL_UNIQUE_ID);
const gzString GZ_DYNAMIC_ERROR_TEST_OK				= gzUniqueString("Test OK",			GZ_DYNAMIC_ERROR_TEST_OK_UNIQUE_ID);
const gzString GZ_DYNAMIC_ERROR_TEST_FAIL			= gzUniqueString("Test FAIL",		GZ_DYNAMIC_ERROR_TEST_FAIL_UNIQUE_ID);


#endif // __GZ_UNIQUE_STRINGS_H__
