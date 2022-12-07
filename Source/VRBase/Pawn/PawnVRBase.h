// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Interact/InteractBase.h"
#include "Interact/Grip/Weapon/Component/WeaponShotComponent.h"
#include "PawnVRBase.generated.h"

UCLASS()
class VRBASE_API APawnVRBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnVRBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnResetVR();

	void TouchGripLeft_Pressed();
	void TouchGripLeft_Released();
	void TouchGripRight_Pressed();
	void TouchGripRight_Released();

	void TriggerLeft_Pressed();
	void TriggerLeft_Released();
	void TriggerRight_Pressed();
	void TriggerRight_Released();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* VrRoot;

	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* VRCamera;

	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		UMotionControllerComponent* LeftMotionController;
	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* SphereLeftController;

	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		UMotionControllerComponent* RightMotionController;
	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* SphereRightController;

	UPROPERTY(Category = VRBase, VisibleAnywhere, BlueprintReadOnly)
		UWeaponShotComponent* WeaponShotComponent;
	
public:
	UFUNCTION(Category = death, BlueprintCallable, BlueprintPure)
		bool IsDeath();
	UFUNCTION(Category = death, BlueprintCallable)
		void SetDeath(bool newDeath);
	UFUNCTION(Category = death, BlueprintCallable)
		void InitDeath();
	UFUNCTION(Category = death, BlueprintCallable)
		void InitRevival();

private:
	AInteractBase* AttachInteractActorLeft;
	AInteractBase* AttachInteractActorRight;
	bool death;

private:
	AInteractBase* GetOevrlapInteractActor(UPrimitiveComponent* primComp);
	bool AttachInteractToController(UPrimitiveComponent* primComp, AActor* attachInteractActor);
	bool DetachInteractActor(AActor* detachInteractActor);
};
