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
// File			: cswGeoModelComponent.h
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW/GZ Model geomtries
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
#pragma once

#include "cswGeoComponent.h"
#include "cswGeoModelComponent.generated.h"


UCLASS(Abstract,ClassGroup=(Custom),NotBlueprintable)
class CSWPLUGIN_API UCSWGeoModelComponent :	public UCSWGeoComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeoModelComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};


