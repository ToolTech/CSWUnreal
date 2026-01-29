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

	// Blueprint test settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	bool bRunGeoTest = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double TestLatitude = 58.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double TestLongitude = 15.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double TestAltitude = 0.0;

	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGeoTestComplete(const FVector& WorldPos, double LatitudeDeg, double LongitudeDeg, double AltitudeMeters);

	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGeoTestFailed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
