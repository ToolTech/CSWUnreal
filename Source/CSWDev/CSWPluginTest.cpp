// Fill out your copyright notice in the Description page of Project Settings.


#include "CSWPluginTest.h"
#include "UEGlue/cswUEUtility.h"
#include "UEGlue/cswUEGlue.h"
#include "UEGlue/cswUETemplates.h"


// Sets default values
ACSWDevTest::ACSWDevTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

ACSWDevTest::~ACSWDevTest()
{
}

// Called when the game starts or when spawned
void ACSWDevTest::BeginPlay()
{
	Super::BeginPlay();

	cswUEReference<UMaterial>* test = new cswUEReference<UMaterial>;

	*test=NewObject<UMaterial>();

	{
		gzRefPointer<cswUEReference<UMaterial>> inst = test;
	}

}

// Called every frame
void ACSWDevTest::Tick(float DeltaTime)
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

