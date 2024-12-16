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
// File			: cswResourceManager.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface to shared Resources per scenemanager
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
// AMO	241211	Created file 							(1.1.1)
//
//******************************************************************************
#pragma once

#include "gzNode.h"
#include "Materials/Material.h"


enum cswMaterialType
{
	CSW_MATERIAL_TYPE_BASE_MATERIAL		= 1<<0,		// Standard base material with glTF shader stuff
	CSW_MATERIAL_TYPE_DSM				= 1<<1,		// Material for Surface height
	CSW_MATERIAL_TYPE_FEATURE			= 1<<2,		// Material for feature classification
};

GZ_USE_BIT_LOGIC(cswMaterialType);

class cswResourceManager : public gzObject
{
public:

	// Type info
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSWPLUGIN_API);			// Each factory has a specific type and hierarchy

	CSWPLUGIN_API bool initialize();

	CSWPLUGIN_API UMaterialInterface* getMaterial(UActorComponent *owner, gzState* state, cswMaterialType type = CSW_MATERIAL_TYPE_BASE_MATERIAL);

private:

	TObjectPtr<UMaterialInterface>	m_baseMaterial;
};

GZ_DECLARE_REFPTR(cswResourceManager);