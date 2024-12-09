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

#include "components/cswTransform.h"
#include "components/cswGeometry.h"

#include "gzTransform.h"
#include "cswUEMatrix.h"

// Sets default values for this component's properties
UCSWTransform::UCSWTransform(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

bool UCSWTransform::build(UCSWSceneComponent* parent, gzNode* buildItem)
{
	if (!Super::build(parent,buildItem))
		return false;

	gzTransform* transform = gzDynamic_Cast<gzTransform>(buildItem);

	if (!transform)
		return false;

	if (transform->isActive())
	{
		FTransform m;

		m.SetFromMatrix(cswMatrix4_<double>::UEMatrix4((gzMatrix4D)transform->getTransform()));

		SetRelativeTransform(m);
	}

	return true;
}

bool  UCSWTransform::destroy(gzNode* destroyItem)
{
	// Do cleanup
	
	return Super::destroy(destroyItem);
}

