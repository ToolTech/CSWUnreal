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
// File			: cswTransform.h
// Module		: CSW StreamingMap Unreal
// Description	: class def of gzTransform equiv cswTransform
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

#include "CoreMinimal.h"
#include "cswNode.h"
#include "cswTransform.generated.h"

class UCSWGeometry;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSWPLUGIN_API UCSWTransform : public UCSWNode
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWTransform(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual bool build(UCSWSceneComponent* parent, gzNode* buildItem, gzState* state,BuildProperties& buildProperties, cswResourceManager* resources) override;

	virtual bool destroy(gzNode* destroyItem, cswResourceManager* resources) override;
		
};
