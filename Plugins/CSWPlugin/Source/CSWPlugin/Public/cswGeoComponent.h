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
// File			: cswGeoComponent.h
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW/GZ SceneComponent classes in Unreal
// Author		: Anders Modén		
// Product		: CSW 1.1.2
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

#include "gzMatrix.h"
#include "cswGeoComponent.generated.h"

UENUM()
enum CoordType
{
	Geometry	UMETA(DisplayName = "Geometry"),
	Geocentric  UMETA(DisplayName = "Geocentric"),
	Geodetic    UMETA(DisplayName = "Geodetic"),
	Projected   UMETA(DisplayName = "Projected"),
	UTM			UMETA(DisplayName = "UTM"),
	FlatEarth   UMETA(DisplayName = "FlatEarth"),
};

UCLASS(Abstract)
class CSWPLUGIN_API UCSWGeoComponent :	public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeoComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual gzVoid setCoordinateSystem(const gzString& cs, const gzVec3D& origo);
};


