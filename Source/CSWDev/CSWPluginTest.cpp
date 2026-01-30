// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWPluginTest.h"
#include "cswGroundClampAsyncAction.h"
#include "UEGlue/cswUEUtility.h"
#include "UEGlue/cswUEGlue.h"
#include "UEGlue/cswUETemplates.h"


// Sets default values
ACSWDevTest::ACSWDevTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;


}

ACSWDevTest::~ACSWDevTest()
{
}

// Called when the game starts or when spawned
void ACSWDevTest::BeginPlay()
{
	Super::BeginPlay();
	bGeoTestLogged = false;
	bGroundClampTestInFlight = false;
	bGroundClampTestLogged = false;
	GroundClampRequestId = 0;
}


UCSWGroundClampAsyncAction* ACSWDevTest::RunGroundClampAsyncExample(float TimeoutSeconds)
{
	if (!Scene)
		return nullptr;

	return UCSWGroundClampAsyncAction::GroundClampAsync(this, Scene, GroundClampLatitude, GroundClampLongitude, GroundClampHeightAboveGround, bGroundClampWaitForData, TimeoutSeconds);
}

// Called every frame
void ACSWDevTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRunGeoTest && !bGeoTestLogged && Scene && !Scene->CoordSystem.IsEmpty())
	{
		FVector3d WorldPos;
		if (Scene->GeodeticToWorld(TestLatitude, TestLongitude, TestAltitude, WorldPos))
		{
			cswScreenMessage(gzString::formatString("GeodeticToWorld: lat=%f lon=%f alt=%f -> UE=(%f, %f, %f)", TestLatitude, TestLongitude, TestAltitude, WorldPos.X, WorldPos.Y, WorldPos.Z));
			double Lat = 0.0;
			double Lon = 0.0;
			double Alt = 0.0;
			if (Scene->WorldToGeodetic(WorldPos, Lat, Lon, Alt))
			{
				cswScreenMessage(gzString::formatString("WorldToGeodetic: UE=(%f, %f, %f) -> lat=%f lon=%f alt=%f", WorldPos.X, WorldPos.Y, WorldPos.Z, Lat, Lon, Alt));
				FVector WorldPosF = FVector(WorldPos);
				OnGeoTestComplete(WorldPosF, Lat, Lon, Alt);
			}
			else
			{
				OnGeoTestFailed();
			}
		}
		else
		{
			OnGeoTestFailed();
		}
		bGeoTestLogged = true;
	}

	if (bRunGroundClampTest && !bGroundClampTestLogged && !bGroundClampTestInFlight && Scene && !Scene->CoordSystem.IsEmpty())
	{
		GroundClampRequestId = Scene->RequestGroundClampPosition(GroundClampLatitude, GroundClampLongitude, GroundClampHeightAboveGround, bGroundClampWaitForData);
		if (GroundClampRequestId > 0)
		{
			bGroundClampTestInFlight = true;
		}
		else
		{
			bGroundClampTestLogged = true;
			OnGroundClampTestFailed();
		}
	}

	if (bGroundClampTestInFlight && Scene)
	{
		FCSWGroundClampResult result;
		if (Scene->TryGetGroundClampResponse(GroundClampRequestId, result))
		{
			bGroundClampTestInFlight = false;
			bGroundClampTestLogged = true;
			if (result.bSuccess)
				OnGroundClampTestComplete(result);
			else
				OnGroundClampTestFailed();
		}
	}
}

#include "data.h"
#include "gzImageLibrary.h"

gzImage* getDDS()
{
	gzImage* im = gzImageManager::loadImage(gzString::formatString("mem:%lld,%lld?format=dds", img_data, sizeof(img_data)));

	return im;
}
