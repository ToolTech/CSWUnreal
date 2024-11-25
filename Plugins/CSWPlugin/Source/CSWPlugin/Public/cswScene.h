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
// File			: cswScene.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface for StreamingMapComponent
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
#pragma once


#include "Components/SceneComponent.h"

#include "cswSceneManager.h"
#include "cswCommandReceiver.h"

#include "CSWScene.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSWPLUGIN_API UCSWScene : public USceneComponent,
								public cswCommandReceiverInterface
{
	GENERATED_BODY()
public:

	UCSWScene(const FObjectInitializer& ObjectInitializer);
	~UCSWScene();

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Transient)
	UStaticMeshComponent* RootMesh;

protected:

	virtual gzVoid onCommand(cswCommandBuffer* buffer) override;

	cswSceneManager m_manager;

};


