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
// File			: gzDbLibrary.h
// Module		: 
// Description	: Management of the db library
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.231
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
#ifndef __GZ_DB_LIBRARY_H__
#define __GZ_DB_LIBRARY_H__

/*!	\file 
	\brief Management of the db library

*/

#include "gzGraphLibrary.h"

#include "gzDbManagerInitializer.h"
#include "gzDbManager_3ds.h"
#include "gzDbManager_flt.h"
#include "gzDbManager_gzd.h"
#include "gzDbManager_gzx.h"
#include "gzDbManager_gzl.h"
#include "gzDbManager_pfb.h"
#include "gzDbManager_txp.h"
#include "gzDbManager_wrl.h"
#include "gzDbManager_dae.h"
#include "gzDbManager_xfr.h"
#include "gzDbManager_obj.h"
#include "gzDbManager_sba.h"
#include "gzDbManager_glTF.h"

#include "gzDbManagerResource.h"		// Def of res: url

// -------------------------------------- Library version ---------------------------------------------------------------

GZ_DB_EXPORT gzVoid gzCheckLibraryVersion_db(gzInt32 major=GZ_VERSION_MAJ , gzInt32 minor=GZ_VERSION_MIN , gzInt32 dev=GZ_VERSION_DEV);

GZ_DB_EXPORT gzLibReference *gzGetLibReference_db();

// Define used library
#if !defined GZDB_EXPORTS && !defined GZ_IGNORE_LIBDEFS && defined GZ_WINDOWS
#pragma comment( lib, "gzDb" GZ_LIB_EXT ".lib" )
#endif


#endif // __GZ_DB_LIBRARY_H__






