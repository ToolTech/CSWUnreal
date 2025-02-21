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
// File			: gzDisplayList.h
// Module		: 
// Description	: Class definition of the gzDisplayListInfo class
// Author		: Anders Mod�n		
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
// AMO	991101	Created file 	
//
//******************************************************************************
#ifndef __GZ_DISPLAY_LIST_H__
#define __GZ_DISPLAY_LIST_H__

/*!	\file 
	\brief Base definitions of multithread graphics contexts

*/

#include "gzContext.h"

class gzContext;	// Forwar declaration

class gzDisplayListInfo
{
public:

	GZ_GRAPH_EXPORT gzDisplayListInfo();

	GZ_GRAPH_EXPORT virtual ~gzDisplayListInfo();

	GZ_GRAPH_EXPORT gzVoid create(gzContext *context,gzUInt32 count);

	GZ_GRAPH_EXPORT gzVoid destroy();

	GZ_GRAPH_EXPORT gzVoid compile(gzUInt32 index);

	GZ_GRAPH_EXPORT gzVoid compileAndExecute(gzUInt32 index);

	GZ_GRAPH_EXPORT gzVoid endCompile();

	GZ_GRAPH_EXPORT gzVoid execute(gzUInt32 index);

	// Global attributes --------------------------------

	gzUInt32									dispID;

	gzUInt32									dispIDCount;

	gzRefPointer<gzRefIdStorage>			dispUnbindID;

	gzUInt32									contextEnumerator;
};

#endif

