// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Grip/Weapon/Component/WeaponShotComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWeaponShotComponent::UWeaponShotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponShotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponShotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponShotComponent::Shot(FVector startPos, FVector dir) {
	FVector _normDir = dir;
	_normDir.Normalize();

	FHitResult OutHit;
	FVector _end = ((_normDir * distanceShot) + startPos);
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypes);
	FCollisionQueryParams CollisionParams;
	

	if (GetWorld()->LineTraceSingleByObjectType(OutHit, startPos, _end, ObjectQueryParams, CollisionParams)){
		if (OutHit.bBlockingHit){
			if(OutHit.Actor.IsValid()) {
				UGameplayStatics::ApplyDamage(OutHit.Actor.Get(), damage, nullptr, GetOwner(), UDamageType::StaticClass());
			}

			if (GEngine) {
				DrawDebugLine(GetWorld(), startPos, OutHit.Location, FColor::Green, false, 0.1, 0, 1);
				DrawDebugLine(GetWorld(), OutHit.Location, _end, FColor::Red, false, 0.1, 0, 1);
				DrawDebugPoint(GetWorld(), OutHit.Location, 5, FColor::Green, false, 0.1, 0);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "Shot BlockingHit");
			}
		}
	}
	else {
		if (GEngine) {
			DrawDebugLine(GetWorld(), startPos, _end, FColor::Red, false, 0.1, 0, 1);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Shot not block");
		}
	}
}
