// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cswNode.h"
#include "cswGeometry.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSWPLUGIN_API UCSWGeometry : public UCSWNode
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeometry(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual bool build(UCSWSceneComponent* parent, gzNode* buildItem) override;

	virtual bool destroy(gzNode* destroyItem) override;

protected:

	TObjectPtr<UStaticMeshComponent> m_meshComponent;

		
};
