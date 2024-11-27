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
#include "cswUETemplates.h"

#include "CSWScene.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSWPLUGIN_API UCSWScene : public USceneComponent,
								public cswCommandReceiverInterface,
								public cswUEPropertyChain<UCSWScene>
{
	GENERATED_BODY()
public:

	UCSWScene(const FObjectInitializer& ObjectInitializer);
	~UCSWScene();

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditUndo() override;
	virtual void PostEditImport() override;
#endif

	// Properties ------------------------------------------------------------------
	// 
	//UPROPERTY(Transient)
	//UStaticMeshComponent* RootMesh;

	UPROPERTY(EditAnywhere, Category = "CSW")
	FString MapUrls;

	void test(bool inPlay);

protected:

	// Init scenemanager and set up context
	void initSceneManager();
	
	virtual void BeginPlay() override;

	// Transfer buffers from in to out
	void fetchBuffers();

	// Perform work on buffers Out
	void processBuffersOut();

	// Property Update callbacks
	bool onMapUrlsPropertyUpdate();

	virtual gzVoid onCommand(cswCommandBuffer* buffer) override;

	cswSceneManagerPtr m_manager;

	UPROPERTY(Transient)
	UStaticMeshComponent* _smComp;

	

private:

	gzMutex							m_bufferInLock;		// Lock for callback accessing bufferIn
	gzRefList<cswCommandBuffer>		m_bufferIn;			// Buffer In
	gzRefList<cswCommandBuffer>		m_bufferOut;		// Buffer Out

};


