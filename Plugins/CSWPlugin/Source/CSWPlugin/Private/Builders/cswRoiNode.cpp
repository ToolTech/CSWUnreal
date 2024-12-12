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
// File			: cswRoiNode.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Builder class for gzRoi and gzRoiNode
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
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************

#include "Builders/cswRoiNode.h"

#include "gzRoi.h"
#include "UEGlue/cswUEMatrix.h"


// Sets default values for this component's properties
UCSWRoiNode::UCSWRoiNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}


bool UCSWRoiNode::build(UCSWSceneComponent* parent, gzNode* buildItem, gzState* state,  BuildProperties& buildProperties, cswResourceManager* resources)
{
	if (!UCSWNode::build(parent,buildItem, state, buildProperties, resources))
		return false;

	gzRoiNode* roi = gzDynamic_Cast<gzRoiNode>(buildItem);

	if (!roi)
		return false;

	FTransform m;

	// Get roi position
	gzDoubleXYZ position = roi->getPosition();

	// We will send this subtree to roi position in Unreal

	gzMatrix4D translation=gzMatrix4D::translateMatrix(position.x,position.y,position.z);
	
	m.SetFromMatrix(cswMatrix4d::UEMatrix4(translation));

	SetRelativeTransform(m);
		

	return true;
}

bool  UCSWRoiNode::destroy(gzNode* destroyItem, cswResourceManager* resources)
{
	// Do cleanup

	return Super::destroy(destroyItem, resources);
}

