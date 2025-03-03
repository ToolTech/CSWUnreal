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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#include "CSWWorld.h"

#include "UEGlue/cswUEGlue.h"
#include "gzDynamicLoader.h"

ACSWWorld::ACSWWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cswInitializeUnrealGlue();

	Scene = CreateDefaultSubobject<UCSWScene>(TEXT("Scene"));

	SetRootComponent(Scene);

	// Register callbacks
	registerPropertyUpdate("EnableLoaders", &ACSWWorld::onEnableLoadersPropertyUpdate);
	registerPropertyUpdate("LoaderThreads", &ACSWWorld::onEnableLoadersPropertyUpdate);
}

ACSWWorld::~ACSWWorld()
{
	cswUnInitializeUnrealGlue();
}


// Called when the game starts or when spawned
void ACSWWorld::BeginPlay()
{
	Super::BeginPlay();

}

bool ACSWWorld::onEnableLoadersPropertyUpdate()
{
	gzDynamicLoaderManager::setNumberOfActiveLoaders(LoaderThreads);

	LoaderThreads = gzDynamicLoaderManager::getNumberOfActiveLoaders();

	if (EnableLoaders)
	{
		gzDynamicLoaderManager::startManager();
	}
	else
	{
		gzDynamicLoaderManager::stopManager();
	}

	return true;
}

// Called every frame
void ACSWWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Drive the scene from tick

	/*static bool first = true;

	Scene->processFrames(first);

	first = false;*/
}

// Called after the C++ constructor and after the properties have been initialized, including those loaded from config.This is called before any serialization or other setup has happened.

void ACSWWorld::PostInitProperties()
{
	Super::PostInitProperties();

	propertyUpdate();
}

//Do any object-specific cleanup required immediately after loading an object. This is not called for newly-created objects, and by default will always execute on the game thread.

void ACSWWorld::PostLoad()
{
	Super::PostLoad();

	propertyUpdate();
}

#if WITH_EDITOR	// ------------------------------ EDITOR Only --------------------------------------

void ACSWWorld::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.Property)
		return;

	FName PropName = PropertyChangedEvent.Property->GetFName();

	if (!propertyUpdate(PropName))
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to do a ACSWWorld::PostEditChangeProperty on property (%s)", toString(PropName));
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

#endif // ------------------------------ EDITOR Only --------------------------------------
