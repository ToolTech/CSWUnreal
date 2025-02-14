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
// File			: gzRenderAction.h
// Module		: 
// Description	: Class definition of the gzRenderAction class
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
// AMO	981127	Created file 	
//
//******************************************************************************
#ifndef __GZ_RENDER_ACTION_H__
#define __GZ_RENDER_ACTION_H__

/*!	\file 
	\brief Base definitions for scene graph rendering

*/


#include "gzNode.h"
#include "gzCamera.h"
#include "gzMatrix.h"
#include "gzEnvironment.h"

class gzRenderNode
{
public:
	gzNode				*node;
	gzUInt32				stateAttributeIndex;
	gzUInt32				transformIndex;
	gzUInt32				transformUpdateID;
	gzUInt32				transformBaseIndex;
	gzUInt32				lightStateIndex;
	gzUInt32				clipStateIndex;
	gzUInt32				fogStateIndex;
};

//******************************************************************************
// Class	: gzRenderAction
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981127	Created 
//									
//******************************************************************************
class gzRenderAction : public gzTraverseAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzRenderAction();
	GZ_GRAPH_EXPORT virtual ~gzRenderAction(){};

	GZ_GRAPH_EXPORT virtual gzBool isTransformTraverser()	const override { return TRUE; }
	GZ_GRAPH_EXPORT virtual gzBool isRenderTraverser()		const override { return TRUE; }
	GZ_GRAPH_EXPORT virtual gzBool isIntersectorTraverser() const override { return FALSE; }

	GZ_GRAPH_EXPORT virtual gzVoid initTraversal(gzContext *context) override;

	GZ_GRAPH_EXPORT gzVoid reset(gzContext *context,gzBool mainLoop);

	GZ_GRAPH_EXPORT gzVoid render(gzNode *node ,gzContext *context,gzBool mainLoop);
	GZ_GRAPH_EXPORT gzVoid renderGroup(gzGroup *group ,gzContext *context,gzBool mainLoop);
	GZ_GRAPH_EXPORT gzVoid executeRenderStages(gzContext *context);

	// ----------------- stage management -------------------------------
	GZ_GRAPH_EXPORT gzVoid addNodeToRenderStage( gzContext *context , gzNode *node , gzActionStage stage);
	GZ_GRAPH_EXPORT gzVoid renderStage(gzContext *context , gzActionStage stage);

	// ----------------- Compiled stages --------------------------------
	GZ_GRAPH_EXPORT static gzVoid convertToCompiledStages(const gzMatrix4 &inv,gzContext *context);
	GZ_GRAPH_EXPORT static gzVoid addReferenceToCompiledStages(gzContext *context);
	GZ_GRAPH_EXPORT static gzVoid releaseReferenceToCompiledStages(gzContext *context);
	GZ_GRAPH_EXPORT static gzVoid expandMatrixGeometry(gzContext *context);

	
protected:

	GZ_GRAPH_EXPORT virtual gzBool checkBoundary(gzContext *context , gzNode *node) override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzNode *node , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzNode *node , gzContext *context) override;

};

GZ_DECLARE_REFPTR(gzRenderAction);

#endif
