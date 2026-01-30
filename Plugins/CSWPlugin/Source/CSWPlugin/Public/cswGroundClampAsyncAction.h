#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TimerManager.h"

#include "cswScene.h"

#include "cswGroundClampAsyncAction.generated.h"

UCLASS()
class CSWPLUGIN_API UCSWGroundClampAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="CSW|GroundClamp")
	FCSWGroundClampResponse OnSuccess;

	UPROPERTY(BlueprintAssignable, Category="CSW|GroundClamp")
	FCSWGroundClampResponse OnFail;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category="CSW|GroundClamp")
	static UCSWGroundClampAsyncAction* GroundClampAsync(UObject* WorldContextObject, UCSWScene* Scene, double LatitudeDeg, double LongitudeDeg, double HeightAboveGround = 1000.0, bool WaitForData = false, float TimeoutSeconds = 2.0f);

	virtual void Activate() override;

private:
	UFUNCTION()
	void HandleGroundClamp(const FCSWGroundClampResult& Result);

	void Finish(bool bSuccess, const FCSWGroundClampResult& Result);
	void OnTimeout();
	void StartTimeout();
	void ClearTimeout();

	TWeakObjectPtr<UCSWScene> ScenePtr;
	TWeakObjectPtr<UObject> WorldContextPtr;
	int32 RequestId = 0;
	double Latitude = 0.0;
	double Longitude = 0.0;
	double Height = 0.0;
	bool bWaitForData = false;
	float TimeoutSeconds = 0.0f;
	bool bCompleted = false;
	FTimerHandle TimeoutHandle;
};
