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
// File			: gzCoordinateBase.h
// Module		: gzCoordinate
// Description	: Management of the math library
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.220
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	180215	Created file								(2.9.1)
//
//******************************************************************************
#ifndef __GZ_COORDINATE_BASE_H__
#define __GZ_COORDINATE_BASE_H__

/*!	\file 
	\brief Management of the math library

*/

#include "gzBaseLibrary.h"
#include "gzMatrix.h"

// ----------------------------- Export Definitions -----------------------------------

#ifdef GZ_WINDOWS
	#ifndef GZ_STATIC			// Default to use all Gizmo3D dlls
		#define GZ_COORDINATE_DLL
	#endif
#endif // GZ_WINDOWS

#ifdef GZ_COORDINATE_DLL		// gzCoordinate.dll
	#ifdef GZCOORDINATE_EXPORTS
		#define GZ_COORDINATE_EXPORT	__declspec(dllexport)
	#else
		#define GZ_COORDINATE_EXPORT	__declspec(dllimport)
	#endif
#else
	#define GZ_COORDINATE_EXPORT
#endif

const class gzString LIBNAME_COORDINATE="gzCoordinate";

#endif // __GZ_COORDINATE_BASE_H__

