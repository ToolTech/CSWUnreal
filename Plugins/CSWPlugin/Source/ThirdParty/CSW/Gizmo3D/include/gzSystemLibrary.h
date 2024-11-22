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
// File			: gzSystemLibrary.h
// Module		: 
// Description	: Management of the system library
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.200
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
// AMO	030423	Created file 	
//
//******************************************************************************
#ifndef __GZ_SYSTEM_LIBRARY_H__
#define __GZ_SYSTEM_LIBRARY_H__

/*!	\file 
	\brief Management of the system library

*/

#include "gzBaseLibrary.h"

#include "gzWindow.h"
#include "gzApplication.h"
#include "gzGraphicsFormat.h"
#include "gzInput.h"
#include "gzViewController.h"
#include "gzWindowSync.h"

// -------------------------------------- Library version ---------------------------------------------------------------

GZ_SYSTEM_EXPORT gzVoid gzCheckLibraryVersion_system(gzInt32 major=GZ_VERSION_MAJ , gzInt32 minor=GZ_VERSION_MIN , gzInt32 dev=GZ_VERSION_DEV);

GZ_SYSTEM_EXPORT gzLibReference *gzGetLibReference_system();

// Define used library
#if !defined GZSYSTEM_EXPORTS && !defined GZ_IGNORE_LIBDEFS && defined GZ_WINDOWS
#pragma comment( lib, "gzSystem" GZ_LIB_EXT ".lib" )
#endif

#endif // __GZ_SYSTEM_LIBRARY_H__






