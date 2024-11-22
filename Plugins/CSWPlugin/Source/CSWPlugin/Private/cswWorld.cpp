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
// File			: cswWorld.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Interface to StreamingMapPlugin
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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#include "CSWWorld.h"

#include "cswUEGlue.h"


ACSWWorld::ACSWWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cswInitializeUnrealGlue();

	registerPropertyUpdate("MapUrls", &ACSWWorld::onMapUrlsPropertyUpdate);

	propertyUpdate("MapUrls");

	Scene = CreateDefaultSubobject<UCSWScene>(TEXT("Scene"));

	DefaultCamera = CreateDefaultSubobject<UCSWCamera>(TEXT("Camera"));

	FName name = "MapUrls";
	int32 id = name.GetNumber();
}

ACSWWorld::~ACSWWorld()
{
	cswUnInitializeUnrealGlue();
}

bool ACSWWorld::onMapUrlsPropertyUpdate()
{
	return true;
}

// Called when the game starts or when spawned
void ACSWWorld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSWWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called after the C++ constructor and after the properties have been initialized, including those loaded from config.This is called before any serialization or other setup has happened.

void ACSWWorld::PostInitProperties()
{
	Super::PostInitProperties();
}

//Do any object-specific cleanup required immediately after loading an object. This is not called for newly-created objects, and by default will always execute on the game thread.

void ACSWWorld::PostLoad()
{
	Super::PostLoad();

	propertyUpdate();
}

void ACSWWorld::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.Property) 
		return;

	FName PropName = PropertyChangedEvent.Property->GetFName();

	if (!propertyUpdate(PropName))
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to do a ACSWWorld::PostEditChangeProperty on property (%s)", toString(PropName));
}

void ACSWWorld::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedChainEvent);
}

void ACSWWorld::PostEditUndo()
{
	Super::PostEditUndo();

	propertyUpdate();
}

void ACSWWorld::PostEditImport()
{
	Super::PostEditImport();

	propertyUpdate();
}

