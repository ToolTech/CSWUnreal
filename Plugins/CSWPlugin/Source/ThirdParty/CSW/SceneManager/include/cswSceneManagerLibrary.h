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
// File			: cswSceneManagerLibrary.h
// Module		: cswSceneManager
// Description	: Management of the SceneManager library
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
// AMO	240912	Created file 							(1.1.1)
//
//******************************************************************************
#pragma once

#include "cswSceneManager.h"		// The manager to communicate with
#include "cswCommandReceiver.h"		// Interface for receiving data
#include "cswCommandBuffer.h"		// Buffer to handle async
#include "cswSceneCommands.h"		// Various commands

// -------------------------------------- Library version ---------------------------------------------------------------

CSW_SM_EXPORT gzVoid cswCheckLibraryVersion_SceneManager(gzInt32 major=CSW_VERSION_MAJ , gzInt32 minor=CSW_VERSION_MIN , gzInt32 dev=CSW_VERSION_DEV);

CSW_SM_EXPORT gzLibReference *cswGetLibReference_SceneManager();

// Define used library
#if !defined CSW_SM_EXPORTS && !defined CMW_IGNORE_LIBDEFS && defined GZ_WINDOWS
	#pragma comment( lib, "cswSceneManager" GZ_LIB_EXT ".lib" )
#endif








