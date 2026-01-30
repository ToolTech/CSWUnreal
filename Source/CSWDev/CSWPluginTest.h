#pragma once

#include "cswWorld.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSWPluginTest.generated.h"

class UCSWGroundClampAsyncAction;

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
	double TestLatitude = 59.333354559480298;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double TestLongitude = 18.124421520193231;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double TestAltitude = 31.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	bool bRunGroundClampTest = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double GroundClampLatitude = 59.333354559480298;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double GroundClampLongitude = 18.124421520193231;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	double GroundClampHeightAboveGround = 1000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW|Test")
	bool bGroundClampWaitForData = false;

	UFUNCTION(BlueprintCallable, Category="CSW|Test")
	UCSWGroundClampAsyncAction* RunGroundClampAsyncExample(float TimeoutSeconds = 2.0f);

	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGroundClampTestComplete(const FCSWGroundClampResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGroundClampTestFailed();


	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGeoTestComplete(const FVector& WorldPos, double LatitudeDeg, double LongitudeDeg, double AltitudeMeters);

	UFUNCTION(BlueprintImplementableEvent, Category="CSW|Test")
	void OnGeoTestFailed();


	UPROPERTY(Transient)
	bool bGeoTestLogged = false;

	UPROPERTY(Transient)
	bool bGroundClampTestInFlight = false;

	UPROPERTY(Transient)
	int32 GroundClampRequestId = 0;

	UPROPERTY(Transient)
	bool bGroundClampTestLogged = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
