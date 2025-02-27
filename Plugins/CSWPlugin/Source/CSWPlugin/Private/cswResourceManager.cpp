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
#include "cswResourceManager.h"
#include "UEGlue/cswUEUtility.h"

#include "Materials/MaterialExpressionTextureSample.h"

GZ_DECLARE_TYPE_CHILD(gzObject, cswResourceManager, "cswResourceManager");


UMaterialInterface* cswResourceManager::initializeBaseMaterial()
{
	// Path to terrain base material
	FSoftObjectPath MaterialPath(TEXT("/CSWPlugin/Materials/cswBaseMaterial.cswBaseMaterial"));

	m_baseMaterial = Cast<UMaterial>(MaterialPath.ResolveObject());

	if (!m_baseMaterial)
		m_baseMaterial = Cast<UMaterial>(MaterialPath.TryLoad());

	if (!m_baseMaterial)
		GZMESSAGE(GZ_MESSAGE_WARNING, "Couldn't find cswBaseMaterial");
		
	return m_baseMaterial;
}

UMaterialInterface* cswResourceManager::getMaterial(UCSWSceneComponent* owner,gzState* state, cswMaterialType type)
{
	if (!state)
		return nullptr;

	if (!m_baseMaterial)
		return nullptr;

	if (type == CSW_MATERIAL_TYPE_BASE_MATERIAL)
	{
		gzTexture* texture = state->getTexture(0);

		if (!texture)
			return nullptr;

		gzImagePtr image = texture->getImage();

		if (!image)
			return nullptr;

		// Lets try other format

		//image = gzImage::createChecker(gzRGBA(1.f, 1.f, 1.f, 1.f), gzRGBA(0.f, 0.f, 0.f, 1.f), GZ_IMAGE_TYPE_BW_8, 512, 512);

		/*image = gzImage::createChecker(gzRGBA(1.f, 1.f, 1.f, 1.f), gzRGBA(0.f, 0.f, 1.f, 1.f), GZ_IMAGE_TYPE_RGBA_8, 512, 512,16,16);

		image->createMipMaps();*/

		//image = gzImage::createChecker(gzRGBA(1.f, 1.f, 1.f, 1.f), gzRGBA(0.f, 0.f, 0.f, 1.f), GZ_IMAGE_TYPE_BW_8, 4, 4, 2, 2);

		// Get a texture
		UTexture2D* ue_texture = cswUETexture2DFromImage(image);

		if (!ue_texture)
			return nullptr;

		UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(m_baseMaterial,owner);

		if (!material)
			return nullptr;

		material->SetTextureParameterValue(FName("baseTexture"), ue_texture);

		owner->addRefToTexture(ue_texture,material);

		/*

		material->BlendMode = EBlendMode::BLEND_Opaque;
		material->bUseMaterialAttributes = false;
		*/

		return material;
	}

	return nullptr;
}
