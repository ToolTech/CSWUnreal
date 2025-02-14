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
// File			: cswGeoUTMComponent.h
// Module		: CSW StreamingMap Unreal
// Description	: Base class for CSW UTM projection
// Author		: Anders Mod�n		
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


#include "cswGeoComponent.h"


#include "cswGeoUTMComponent.generated.h"


UCLASS()
class CSWPLUGIN_API UCSWGeoUTMComponent :	public UCSWGeoComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeoUTMComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	FString Hemisphere=TEXT("N");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	uint8 Zone=32;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double Easting=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double Northing=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double Height=0;

	virtual gzVoid setCoordinateSystem(const gzString& cs, const gzVec3D& origo) override;
};


