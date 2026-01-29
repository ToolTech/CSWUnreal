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
// File			: gzGeoSceneOptimizer.h
// Module		: 
// Description	: Global SceneGraph LOD Geometry Optimizer
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
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
// AMO	230124	Created file 										(2.12.50)
//
//******************************************************************************
#ifndef __GZ_GEO_SCENE_OPTIMIZER_H__
#define __GZ_GEO_SCENE_OPTIMIZER_H__

/*!	\file 
	\brief Base definitions for global scene graph geometry optimization classes

*/

#include "gzNode.h"
#include "gzGeometryOptimizer.h"

typedef enum {
	GZ_GEO_SCENE_OPTIMIZE_DEFAULT = 0,			// Default
	//GZ_NODE_OPTIMIZE_ONLY_STATES = (1 << 0),		// Only work on state sharing
	

} gGeoSceneOptimizeLevel;

//! Use Bit Logics for optimizer flags
GZ_USE_BIT_LOGIC(gGeoSceneOptimizeLevel);

//******************************************************************************
// Class	: gzGeoSceneOptimizer
//									
// Purpose  : Utility class to optimize scene graph geometry data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	230125	Created			(2.12.50)
//									
//******************************************************************************
class gzGeoSceneOptimizer
{
public:

	GZ_GRAPH_EXPORT gzGeoSceneOptimizer();

	GZ_GRAPH_EXPORT virtual ~gzGeoSceneOptimizer();

	GZ_GRAPH_EXPORT gzNode* optimize(gzNode* node, gGeoSceneOptimizeLevel level = GZ_GEO_SCENE_OPTIMIZE_DEFAULT);

private:

	gzVoid traverseScene(gzNode* node,  gzUInt32 buildGroup, const gzMatrix4& currentTransform);

	gzVoid addGeometry(gzGeometry* geom, gzState* state, gzUInt32 buildGroup,const gzMatrix4& currentTransform);

	gzContextPtr m_currentContext;
	gzTriangleContainerPtr	m_triangleContainer;

	gzUInt32	m_nextBuildGroup;
};

#endif //__GZ_GEO_SCENE_OPTIMIZER_H__


