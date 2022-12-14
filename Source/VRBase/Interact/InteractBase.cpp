// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/InteractBase.h"

// Sets default values
AInteractBase::AInteractBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereTrigger = CreateDefaultSubobject<USphereComponent>("SphereTrigger");
	if (SphereTrigger) {
		SphereTrigger->SetupAttachment(RootComponent);
		SphereTrigger->SetSphereRadius(10);
	}
}

// Called when the game starts or when spawned
void AInteractBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractBase::ActivateInteract() {

}

void AInteractBase::DeactivateInteract() {

}