#pragma once

#include "cswWorld.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSWPluginTest.generated.h"

UCLASS()
class CSWDEV_API ACSWDevTest : public ACSWWorld
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACSWDevTest();

	~ACSWDevTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
