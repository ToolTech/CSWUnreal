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
// File			: cswCommon.h
// Module		: CSW
// Description	: Management of the common library parts
// Author		: Anders Modén		
// Product		: CSW 1.1.1
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240912	Created file 					(1.1.1)
//
//******************************************************************************
#pragma once

#include "gzBaseLibrary.h"			// Base functions
#include "gzGraphLibrary.h"			// Graph control

#define CSW_VERSION_STR	"1.1.1"
#define CSW_VERSION_MAJ	1
#define CSW_VERSION_MIN	1
#define CSW_VERSION_DEV	1

// ------------------------------ LIBREFS ------------------------------------------------

#ifndef CSW_LIBREF

#define CMV_LIBREF_DECL(x)		gzLibReference *csvGetLibReference_##x();
#define CMV_LIBREF_IMPL(x)		gzLibReference *csvGetLibReference_##x() { return gzGetLibReference(#x); }

#ifndef CSW_STATIC

#ifndef CSW_NOLIBREF

#define CSW_LIBREF_IMPL_CSW(x)	gzLibReference *cswGetLibReference_##x() { return gzGetLibReference(GZ_LIB_PREFIX "csw" # x); }

#else

#define CSW_LIBREF_IMPL_CSW(x)	gzLibReference *cswGetLibReference_##x() { return NULL; }

#endif	//CSW_NOLIBREF

#else

#define CSW_LIBREF_IMPL_CSW(x)	gzLibReference *cswGetLibReference_##x() { return NULL; }

#endif	//CSW_STATIC

#endif // CSW_LIBREF
