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
// File			: cswScene.cpp
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

#include "cswScene.h"

UCSWScene::UCSWScene(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	// Register callbacks
	registerPropertyUpdate("MapUrls", &UCSWScene::onMapUrlsPropertyUpdate);
		
	initSceneManager();
}

UCSWScene::~UCSWScene()
{
	// Cleanup while we have virtual members
	m_manager = nullptr;
}

void UCSWScene::initSceneManager()
{
	m_manager = new cswSceneManager();

	// Register us as receiver of scene commands
	m_manager->addCommandReceiver(this);

	// Commands
	cswCommandBufferPtr buffer = new cswCommandBuffer;

	buffer->addCommand(new cswSceneCommandInitialize(FALSE));

	buffer->addCommand(new cswSceneCommandSetOmniTraverse(FALSE));
	//buffer->addCommand(new cswSceneCommandSetLoaders(4));

	m_manager->addCommandBuffer(buffer);
}

void UCSWScene::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
}

gzVoid UCSWScene::onCommand(cswCommandBuffer* buffer)
{

}

bool UCSWScene::onMapUrlsPropertyUpdate()
{
	gzString mapURL = toString(MapUrls);

	if (mapURL.length())
	{
		// We got a map. lets start manager
		m_manager->run();
		m_manager->addSingleCommand(new cswSceneCommandSetMapUrls(mapURL));
	}
		
	return true;
}

// Called after the C++ constructor and after the properties have been initialized, including those loaded from config.This is called before any serialization or other setup has happened.

void UCSWScene::PostInitProperties()
{
	Super::PostInitProperties();

	propertyUpdate();
}

//Do any object-specific cleanup required immediately after loading an object. This is not called for newly-created objects, and by default will always execute on the game thread.

void UCSWScene::PostLoad()
{
	Super::PostLoad();

	propertyUpdate();
}

#if WITH_EDITOR	// ------------------------------ EDITOR Only --------------------------------------

void UCSWScene::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.Property)
		return;

	FName PropName = PropertyChangedEvent.Property->GetFName();

	if (!propertyUpdate(PropName))
		GZMESSAGE(GZ_MESSAGE_WARNING, "Failed to do a UCSWScene::PostEditChangeProperty on property (%s)", toString(PropName));
}

void UCSWScene::PostEditUndo()
{
	Super::PostEditUndo();

	propertyUpdate();
}

void UCSWScene::PostEditImport()
{
	Super::PostEditImport();

	propertyUpdate();
}

#endif // ------------------------------ EDITOR Only --------------------------------------
