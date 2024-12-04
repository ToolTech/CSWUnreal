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
// File			: cswSceneComponent.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW/GZ SceneComponent classes in Unreal
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

#include "components/cswSceneComponent.h"


// Sets default values for this component's properties
UCSWSceneComponent::UCSWSceneComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// Default to static mesh fixed grid
	SetMobility(EComponentMobility::Stationary);

	PrimaryComponentTick.bCanEverTick = false;
}

bool UCSWSceneComponent::build(UCSWSceneComponent* parent, gzNode* buildItem)
{
	return true;
}

bool  UCSWSceneComponent::destroy(gzNode* destroyItem)
{
	// Do cleanup

	return true;
}


