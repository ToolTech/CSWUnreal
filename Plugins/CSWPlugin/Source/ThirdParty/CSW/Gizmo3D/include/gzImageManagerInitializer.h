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
// File			: gzImageManagerInitializer.h
// Module		: 
// Description	: Utilities for image management
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.223
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
// AMO	990301	Created file 	
//
//******************************************************************************
#ifndef __GZ_IMAGE_MANAGER_INITIALIZER_H__
#define __GZ_IMAGE_MANAGER_INITIALIZER_H__

/*!	\file 
	\brief Base definitions for bitmap managers

*/

#include "gzBasicTypes.h"

GZ_IMAGE_EXPORT gzVoid gzInitializeImageManagers();
GZ_IMAGE_EXPORT gzVoid gzUninitializeImageManagers(gzBool force=FALSE);

#endif
