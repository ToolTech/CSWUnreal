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
// File			: cswUEGlue.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Glue Between Unreal CSW and GizmoSDK callbacks
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

#include "components/cswRoiNode.h"
#include "components/cswGeometry.h"

#include "gzRoi.h"
#include "cswUEMatrix.h"

// Sets default values for this component's properties
UCSWRoiNode::UCSWRoiNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}


bool UCSWRoiNode::build(UCSWSceneComponent* parent, gzNode* buildItem)
{
	if (!UCSWNode::build(parent,buildItem))
		return false;

	gzRoiNode* roi = gzDynamic_Cast<gzRoiNode>(buildItem);

	if (!roi)
		return false;

	/*if (transform->isActive())
	{
		FTransform m;

		m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4((gzMatrix4D)transform->getTransform()));

		SetRelativeTransform(m);
	}
	*/	

	return true;
}

bool  UCSWRoiNode::destroy(gzNode* destroyItem)
{
	// Do cleanup

	return Super::destroy(destroyItem);
}

