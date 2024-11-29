// Fill out your copyright notice in the Description page of Project Settings.


#include "cswTransform.h"
#include "cswGeometry.h"

// Sets default values for this component's properties
UCSWTransform::UCSWTransform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bTickInEditor = true;
	bAutoActivate = true;

	// ...

	


}

void UCSWTransform::build()
{
	geom = NewObject<UCSWGeometry>(this, NAME_None);

	geom->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	geom->build();
}


// Called when the game starts
void UCSWTransform::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCSWTransform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}

