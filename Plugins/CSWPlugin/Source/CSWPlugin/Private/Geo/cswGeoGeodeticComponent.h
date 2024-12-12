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
// File			: cswGeoGeodeticComponent.h
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW Geodetic projection
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


#include "cswGeoGeodeticComponent.generated.h"


UCLASS()
class CSWPLUGIN_API UCSWGeoGeodeticComponent :	public UCSWGeoComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeoGeodeticComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	FString Latitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	FString Longitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double Altitude = 0;

	virtual gzVoid setCoordinateSystem(const gzString& cs, const gzVec3D& origo) override;
};


