// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWPluginTest.h"
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
}

#include "data.h"
#include "gzImageLibrary.h"

gzImage* getDDS()
{
	gzImage* im = gzImageManager::loadImage(gzString::formatString("mem:%lld,%lld?format=dds", img_data, sizeof(img_data)));

	return im;
}

