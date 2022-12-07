// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/Grip/InteractGripBase.h"
#include "Interact/Grip/Weapon/Component/WeaponShotComponent.h"
#include "InteractGripWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VRBASE_API AInteractGripWeapon : public AInteractGripBase
{
	GENERATED_BODY()
public:

	// Sets default values for this actor's properties
	AInteractGripWeapon();

	virtual void ActivateInteract() override;
	virtual void DeactivateInteract() override;

	UPROPERTY(Category = GripWeapon, VisibleAnywhere, BlueprintReadOnly)
		UWeaponShotComponent* WeaponShotComponent;

	UFUNCTION(Category = Shot, BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
		FVector GetDirectionShot();
	UFUNCTION(Category = Shot, BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
		FVector GetStartPosShot();
};
