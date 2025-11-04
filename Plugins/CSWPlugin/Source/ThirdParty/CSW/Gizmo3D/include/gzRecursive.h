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
// File			: gzRecursive.h
// Module		: 
// Description	: Class definition of the gzRecursive class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.283
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
// AMO	991116	Created file 	
//
//******************************************************************************
#ifndef __GZ_RECURSIVE_H__
#define __GZ_RECURSIVE_H__

/*!	\file 
	\brief Base definitions for recursive group nodes

*/
#include "gzGroup.h"
#include "gzThread.h"

class gzRecursiveData 
{
public:

	gzRecursiveData():depth(0){};
	virtual ~gzRecursiveData(){};

	gzFloat depth;

	gzQueue<gzFloat>	depthStorage;
};


//******************************************************************************
// Class	: gzRecursive
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991116	Created 
//									
//******************************************************************************
class gzRecursive : public gzGroup
{
public:
	GZ_GRAPH_EXPORT gzRecursive(const gzString & name=GZ_EMPTY_STRING);
	GZ_GRAPH_EXPORT virtual ~gzRecursive();

	GZ_GRAPH_EXPORT gzRecursive(const gzRecursive &copy);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;
	GZ_GRAPH_EXPORT	virtual gzVoid setCopyMode(const gzCopyMode & mode) override;

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzVoid updateNodeData(gzBool force=FALSE) override;

	// ---------- Action Interface --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzBool isTraversable( gzTraverseAction *action , gzNode *node , gzUInt32 index, gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Recursive ---------------------------------------------

	GZ_GRAPH_EXPORT gzVoid	setMaxDepth( gzFloat depth );
	GZ_GRAPH_EXPORT gzVoid	setTransform(const gzMatrix4 &transform);
	GZ_GRAPH_EXPORT gzVoid	setMaxDepthNode(gzNode *node);
	GZ_GRAPH_EXPORT gzVoid	useDistanceDepth(gzBool on);
	GZ_GRAPH_EXPORT gzVoid	setDistanceDepthEquation(gzFloat farDistance=100,gzFloat speed=1);

	// ---------- Render models -----------------------------------------

	GZ_GRAPH_EXPORT gzVoid	renderOnRecursion( gzBool on=FALSE );

	GZ_GRAPH_EXPORT gzVoid	transferLightStates( gzBool on=FALSE );


	// ---------- Debug function ----------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid debugOutputTraverse(gzString base , gzString anchor , gzDebugFlags features) override;
	GZ_GRAPH_EXPORT virtual gzVoid debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	GZ_GRAPH_EXPORT virtual gzNode * find(const gzString &path,gzBool recursive=TRUE) override;
	GZ_GRAPH_EXPORT virtual gzBool	hasSiblingNode(gzNode *child) override;

	// --------- Properties --------------------------------------------

	GZ_PROPERTY_EXPORT(gzBool,			RelativeSceneTransform,		GZ_GRAPH_EXPORT);

protected:

	GZ_GRAPH_EXPORT	gzFloat	evaluateMaxDepth(gzContext *context);

	gzFloat												m_maxDepth;
	gzLateBindData<gzMatrix4>							m_transform;
	gzFloat												m_maxscale;
	gzRefPointer<gzNode>								m_maxDepthNode;

	gzLateBindData<gzFloatXY>							m_distanceEquation;

	gzBool												m_renderOnRecursion:1;
	gzBool												m_transferLightState:1;

	gzUInt32											m_id;
	static gzUniqueIDManager							s_idManager;
};


#endif
