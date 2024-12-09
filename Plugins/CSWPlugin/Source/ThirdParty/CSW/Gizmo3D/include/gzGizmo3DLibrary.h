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
// File			: gzGizmo3DLibrary.h
// Module		: 
// Description	: Management of the Gizmo3D library
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.201
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
// AMO	981027	Created file 	
//
//******************************************************************************
#ifndef __GZ_GIZMO3D_LIBRARY_H__
#define __GZ_GIZMO3D_LIBRARY_H__

/*!	\file 
	\brief Management of the complete Gizmo3D library

*/

#include "gzBaseLibrary.h"
#include "gzImageLibrary.h"
#include "gzGraphLibrary.h"
#include "gzDbLibrary.h"
#include "gzSystemLibrary.h"

//! graceful termination in cases where auto terminate does not work properly
GZ_SYSTEM_EXPORT gzBool gzShutDownGizmo(gzBool force=FALSE,gzBool shutDownGizmoBase=FALSE);

GZ_SYSTEM_EXPORT gzBool gzStartUpGizmo();

// -------------------------------------- Library version ---------------------------------------------------------------

GZ_SYSTEM_EXPORT gzVoid gzCheckLibraryVersion(gzInt32 major=GZ_VERSION_MAJ , gzInt32 minor=GZ_VERSION_MIN , gzInt32 dev=GZ_VERSION_DEV);

class gzSceneGraphDebugger
{
public:

	GZ_SYSTEM_EXPORT ~gzSceneGraphDebugger();

	GZ_SYSTEM_EXPORT gzVoid setScene(gzScene *scene);
	GZ_SYSTEM_EXPORT gzVoid updateScene();
	GZ_SYSTEM_EXPORT gzVoid refresh();

	GZ_SYSTEM_EXPORT gzVoid showHierarchy();
	GZ_SYSTEM_EXPORT gzVoid showProperty();
	GZ_SYSTEM_EXPORT gzVoid showResource();
	GZ_SYSTEM_EXPORT gzVoid showViewer();
	GZ_SYSTEM_EXPORT gzVoid showInfo();

private:

	gzRefPointer<gzModule>	m_debugger;
	gzRefPointer<gzModule>	m_hierarchy;
	gzRefPointer<gzModule>	m_property;
	gzRefPointer<gzModule>	m_resource;
	gzRefPointer<gzModule>	m_viewer;
	gzRefPointer<gzModule>	m_info;
};



#endif // __GZ_GIZMO3D_LIBRARY_H__






