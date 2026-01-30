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
// File			: cswGeometry.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Builder class for gzGeometry
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
// AMO	241211	Created file 					(1.1.1)
//
//******************************************************************************
#include "Builders/cswGeometry.h"

// GizmoSDK
#include "gzGeometry.h"

// Glue
#include "UEGlue/cswUEMatrix.h"

#include "cswResourceManager.h"
#include "cswSceneManagerBase.h"

#include "MeshDescription.h"
#include "StaticMeshAttributes.h"

GZ_DECLARE_TYPE_CHILD(gzReference, cswGeometryBuild, "cswGeometryBuild");

// Sets default values for this component's properties
UCSWGeometry::UCSWGeometry(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


bool UCSWGeometry::build(UCSWSceneComponent* parent, gzNode* buildItem, gzState* state, BuildProperties& buildProperties, cswResourceManager* resources)
{
	if (!Super::build(parent,buildItem, state, buildProperties,resources))
		return false;

	
	GZ_INSTRUMENT_NAME("UCSWGeometry::build");

	cswGeometryBuild* buildData = gzDynamic_Cast<cswGeometryBuild>(gzDynamic_Cast<gzReference*>(buildItem->getAttribute(CSW_META, CSW_BUILD_DATA)));

	if (!buildData)
		return false;


	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::component setup");

		// New object
		m_meshComponent = NewObject<UStaticMeshComponent>(this, buildItem->getName().getWideString());

		// Settings specific and optims for fast render
		m_meshComponent->SetSimulatePhysics(buildProperties.simulatePhysics);
		m_meshComponent->SetCollisionEnabled(buildProperties.collision);

		m_meshComponent->SetUsingAbsoluteLocation(false);
		m_meshComponent->SetUsingAbsoluteRotation(false);
		m_meshComponent->SetUsingAbsoluteScale(false);
		
		#if CSW_FORCE_LOD0
		m_meshComponent->ForcedLodModel = 1; // Force LOD0
		#else
		m_meshComponent->ForcedLodModel = 0; // Auto LOD
		#endif

		m_meshComponent->SetMobility(EComponentMobility::Stationary);

		m_meshComponent->SetRenderCustomDepth(false); // stänger av outline effekter

		//m_meshComponent->SetCastShadow(false); // Ingen skuggning

		m_meshComponent->bAffectDistanceFieldLighting = false; // avståndsbaserad 

		m_meshComponent->bAffectDynamicIndirectLighting = false;

		m_meshComponent->bAlwaysCreatePhysicsState = false;

		m_meshComponent->bReceivesDecals = false;

		//m_meshComponent->bUseAttachParentBound = true;

	}
	
			
	// Assign new static mesh to the static mesh component and finalize build ------------------

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::set mesh");
		m_meshComponent->SetStaticMesh(buildData->staticMesh);
	}

	UMaterialInterface* material = resources->getMaterial(this, state, CSW_MATERIAL_TYPE_BASE_MATERIAL);

	if(material)
		m_meshComponent->SetMaterial(0,material);
		

	{
		GZ_INSTRUMENT_NAME("UCSWGeometry::build::Attach & Register");

		m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

		m_meshComponent->RegisterComponent();
	}

	buildItem->removeAllUserData();

	return true;
}

bool UCSWGeometry::update(UCSWSceneComponent* parent, gzNode* buildItem, gzState* state, BuildProperties& buildProperties, cswResourceManager* resources)
{
	GZ_INSTRUMENT_NAME("UCSWGeometry::update");

	if (!parent || !buildItem)
		return false;

	AttachToComponent(parent, FAttachmentTransformRules::KeepRelativeTransform);

	cswGeometryBuild* buildData = gzDynamic_Cast<cswGeometryBuild>(gzDynamic_Cast<gzReference*>(buildItem->getAttribute(CSW_META, CSW_BUILD_DATA)));

	if (!buildData)
		return false;

	if (!m_meshComponent)
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "UCSWGeometry::update: missing mesh component, rebuilding");
		return build(parent, buildItem, state, buildProperties, resources);
	}

	if (shouldSkipUpdate(buildItem))
		return true;

	// Update component settings and mesh without creating a new component
	m_meshComponent->SetSimulatePhysics(buildProperties.simulatePhysics);
	m_meshComponent->SetCollisionEnabled(buildProperties.collision);
	m_meshComponent->SetUsingAbsoluteLocation(false);
	m_meshComponent->SetUsingAbsoluteRotation(false);
	m_meshComponent->SetUsingAbsoluteScale(false);

	#if CSW_FORCE_LOD0
	m_meshComponent->ForcedLodModel = 1; // Force LOD0
	#else
	m_meshComponent->ForcedLodModel = 0; // Auto LOD
	#endif

	m_meshComponent->SetMobility(EComponentMobility::Stationary);
	m_meshComponent->SetRenderCustomDepth(false);
	m_meshComponent->bAffectDistanceFieldLighting = false;
	m_meshComponent->bAffectDynamicIndirectLighting = false;
	m_meshComponent->bAlwaysCreatePhysicsState = false;
	m_meshComponent->bReceivesDecals = false;

	if (buildData->staticMesh)
		m_meshComponent->SetStaticMesh(buildData->staticMesh);

	markUpdated(buildItem);

	UMaterialInterface* material = resources->getMaterial(this, state, CSW_MATERIAL_TYPE_BASE_MATERIAL);
	if (material)
		m_meshComponent->SetMaterial(0, material);

	if (m_meshComponent->GetAttachParent() != this)
		m_meshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	if (!m_meshComponent->IsRegistered())
		m_meshComponent->RegisterComponent();

	return true;
}

bool  UCSWGeometry::destroy(gzNode* destroyItem, cswResourceManager* resources)
{
	// Do cleanup

	GZ_INSTRUMENT_NAME("UCSWGeometry::destroy");

	m_meshComponent->DestroyComponent();

	return Super::destroy(destroyItem, resources);
}
