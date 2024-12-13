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
// File			: cswResourceManager.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Implementation shared resources
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
#include "cswResourceManager.h"
#include "UEGlue/cswUEUtility.h"

#include "Materials/MaterialExpressionTextureSample.h"

GZ_DECLARE_TYPE_CHILD(gzObject, cswResourceManager, "cswResourceManager");


bool cswResourceManager::initialize()
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("/CSWPlugin/Materials/cswBaseMaterial.cswBaseMaterial"));

	if (!MaterialFinder.Succeeded())
		return false;

	m_baseMaterial = MaterialFinder.Object;
	
	return true;
}

UMaterial* cswResourceManager::getMaterial(gzState* state, cswMaterialType type)
{
	if (!state)
		return nullptr;

	if (type == CSW_MATERIAL_TYPE_BASE_MATERIAL)
	{
		gzTexture* texture = state->getTexture(0);

		if (!texture)
			return nullptr;

		gzImage* image = texture->getImage();

		if (!image)
			return nullptr;

		// Get a texture
		UTexture2D* ue_texture = cswUETexture2DFromImage(image);

		if (!ue_texture)
			return nullptr;

		UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(m_baseMaterial, GetTransientPackage());

		if (!material)
			return nullptr;
		/*

		material->BlendMode = EBlendMode::BLEND_Opaque;
		material->bUseMaterialAttributes = false;

		UMaterialExpressionTextureSample* sampler = NewObject<UMaterialExpressionTextureSample>(material);

		if (!sampler)
			return nullptr;

		sampler->Texture = ue_texture;

		material->Expr*/
	}

	return nullptr;
}

FStaticMaterial cswResourceManager::getStaticMaterial(gzState* state, cswMaterialType type)
{
	UMaterial* mat = getMaterial(state, type);

	return FStaticMaterial();
}

cswMaterialType cswResourceManager::getStateCapabilities(gzState* state)
{
	// Test code 
	return CSW_MATERIAL_TYPE_BASE_MATERIAL;
}

uint32 cswResourceManager::getMaterialSlots(cswMaterialType type) 
{
	// Number of defined slot entries in type
	return gzBitCount((uint32)type);
}