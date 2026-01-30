#include "cswGroundClampAsyncAction.h"

#include "Engine/Engine.h"
#include "Engine/World.h"

UCSWGroundClampAsyncAction* UCSWGroundClampAsyncAction::GroundClampAsync(UObject* WorldContextObject, UCSWScene* Scene, double LatitudeDeg, double LongitudeDeg, double HeightAboveGround, bool WaitForData, float TimeoutSeconds)
{
	UCSWGroundClampAsyncAction* action = NewObject<UCSWGroundClampAsyncAction>();
	action->WorldContextPtr = WorldContextObject;
	action->ScenePtr = Scene;
	action->Latitude = LatitudeDeg;
	action->Longitude = LongitudeDeg;
	action->Height = HeightAboveGround;
	action->bWaitForData = WaitForData;
	action->TimeoutSeconds = TimeoutSeconds;
	return action;
}

void UCSWGroundClampAsyncAction::Activate()
{
	if (bCompleted)
		return;

	UObject* WorldContextObject = WorldContextPtr.Get();
	UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr;

	if (!ScenePtr.IsValid() || !World)
	{
		FCSWGroundClampResult result;
		Finish(false, result);
		return;
	}

	RegisterWithGameInstance(WorldContextObject);
	ScenePtr->OnGroundClampResponse.AddDynamic(this, &UCSWGroundClampAsyncAction::HandleGroundClamp);

	RequestId = ScenePtr->RequestGroundClampPosition(Latitude, Longitude, Height, bWaitForData);
	if (RequestId <= 0)
	{
		ScenePtr->OnGroundClampResponse.RemoveDynamic(this, &UCSWGroundClampAsyncAction::HandleGroundClamp);
		FCSWGroundClampResult result;
		result.RequestId = RequestId;
		Finish(false, result);
		return;
	}

	StartTimeout();
}

void UCSWGroundClampAsyncAction::HandleGroundClamp(const FCSWGroundClampResult& Result)
{
	if (bCompleted)
		return;

	if (Result.RequestId != RequestId)
		return;

	Finish(Result.bSuccess, Result);
}

void UCSWGroundClampAsyncAction::Finish(bool bSuccess, const FCSWGroundClampResult& Result)
{
	if (bCompleted)
		return;

	bCompleted = true;
	ClearTimeout();

	if (ScenePtr.IsValid())
		ScenePtr->OnGroundClampResponse.RemoveDynamic(this, &UCSWGroundClampAsyncAction::HandleGroundClamp);

	if (bSuccess)
		OnSuccess.Broadcast(Result);
	else
		OnFail.Broadcast(Result);

	SetReadyToDestroy();
}

void UCSWGroundClampAsyncAction::StartTimeout()
{
	if (TimeoutSeconds <= 0.0f)
		return;

	UObject* WorldContextObject = WorldContextPtr.Get();
	UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr;
	if (!World)
		return;

	World->GetTimerManager().SetTimer(TimeoutHandle, this, &UCSWGroundClampAsyncAction::OnTimeout, TimeoutSeconds, false);
}

void UCSWGroundClampAsyncAction::ClearTimeout()
{
	UObject* WorldContextObject = WorldContextPtr.Get();
	UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull) : nullptr;
	if (!World)
		return;

	World->GetTimerManager().ClearTimer(TimeoutHandle);
}

void UCSWGroundClampAsyncAction::OnTimeout()
{
	if (bCompleted)
		return;

	FCSWGroundClampResult result;
	result.RequestId = RequestId;
	Finish(false, result);
}
