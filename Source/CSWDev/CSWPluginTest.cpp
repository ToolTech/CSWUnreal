// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWPluginTest.h"
#include "cswUEUtility.h"
#include "cswUEGlue.h"


// Sets default values
AStreamingMapTest::AStreamingMapTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

AStreamingMapTest::~AStreamingMapTest()
{
}

// Called when the game starts or when spawned
void AStreamingMapTest::BeginPlay()
{
	Super::BeginPlay();

	//FString t("kjh");

}

// Called every frame
void AStreamingMapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#include "data.h"
#include "gzImageLibrary.h"

gzImage* getDDS()
{
	gzImage* im = gzImageManager::loadImage(gzString::formatString("mem:%lld,%lld?format=dds", img_data, sizeof(img_data)));

	return im;
}

