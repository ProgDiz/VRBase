// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnVRBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APawnVRBase::APawnVRBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VrRoot = CreateDefaultSubobject<USceneComponent>("VrRoot");
	if (VrRoot){
		VrRoot->SetupAttachment(RootComponent);
	}

	VRCamera = CreateDefaultSubobject<UCameraComponent>("VRCamera");
	if (VRCamera){
		VRCamera->SetupAttachment(VrRoot);
	}

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>("LeftMotionController");
	if (LeftMotionController){
		LeftMotionController->SetupAttachment(VrRoot);
		//LeftMotionController->SetTrackingMotionSource("Left");
		LeftMotionController->MotionSource = "Left";

		SphereLeftController = CreateDefaultSubobject<USphereComponent>("SphereLeftController");
		if (SphereLeftController) {
			SphereLeftController->SetupAttachment(LeftMotionController);
			SphereLeftController->SetSphereRadius(10);
		}
	}
	
	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>("RightMotionController");
	if (RightMotionController) {
		RightMotionController->SetupAttachment(VrRoot);
		//RightMotionController->SetTrackingMotionSource("Right");
		RightMotionController->MotionSource = "Right";

		SphereRightController = CreateDefaultSubobject<USphereComponent>("SphereRightController");
		if (SphereRightController) {
			SphereRightController->SetupAttachment(RightMotionController);
			SphereRightController->SetSphereRadius(10);
		}
	}

}

/********************Input*********************/
void APawnVRBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("TouchGripLeft", IE_Pressed, this, &APawnVRBase::TouchGripLeft_Pressed);
	PlayerInputComponent->BindAction("TouchGripLeft", IE_Released, this, &APawnVRBase::TouchGripLeft_Released);
	PlayerInputComponent->BindAction("TouchGripRight", IE_Pressed, this, &APawnVRBase::TouchGripRight_Pressed);
	PlayerInputComponent->BindAction("TouchGripRight", IE_Released, this, &APawnVRBase::TouchGripRight_Released);
	PlayerInputComponent->BindAction("TriggerLeft", IE_Pressed, this, &APawnVRBase::TriggerLeft_Pressed);
	PlayerInputComponent->BindAction("TriggerLeft", IE_Released, this, &APawnVRBase::TriggerLeft_Released);
	PlayerInputComponent->BindAction("TriggerRight", IE_Pressed, this, &APawnVRBase::TriggerRight_Pressed);
	PlayerInputComponent->BindAction("TriggerRight", IE_Released, this, &APawnVRBase::TriggerRight_Released);
}


void APawnVRBase::OnResetVR(){
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}


void APawnVRBase::TouchGripLeft_Pressed() {
	if (death)
		return;

	if (!SphereLeftController) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "SphereController not valid");
		return;
	}

	AttachInteractActorLeft = GetOevrlapInteractActor(SphereLeftController);
	if (!AttachInteractActorLeft) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorLeft not valid");
		return;
	}

	if (AttachInteractActorRight == AttachInteractActorLeft) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorRight == AttachInteractActorLeft");
		return;
	}

	if (AttachInteractToController(SphereLeftController, AttachInteractActorLeft))
		return;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "TouchGripLeft_Pressed");
}


void APawnVRBase::TouchGripLeft_Released() {
	if (death)
		return;

	if (!AttachInteractActorLeft) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorLeft not valid");
		return;
	}

	DetachInteractActor(AttachInteractActorLeft);
	AttachInteractActorLeft = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "TouchGripLeft_Released");
}


void APawnVRBase::TouchGripRight_Pressed() {
	if (death)
		return;

	if (!SphereRightController) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "SphereController not valid");
		return;
	}

	AttachInteractActorRight = GetOevrlapInteractActor(SphereRightController);
	if (!AttachInteractActorRight) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorRight not valid");
		return;
	}

	if (AttachInteractActorRight == AttachInteractActorLeft) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorRight == AttachInteractActorLeft");
		return;
	}

	if (!AttachInteractToController(SphereRightController, AttachInteractActorRight))
		return;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "TouchGripRight");
}


void APawnVRBase::TouchGripRight_Released() {
	if (death)
		return;

	if (!SphereRightController) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "SphereController not valid");
		return;
	}

	if (!AttachInteractActorRight) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorRight not valid");
		return;
	}

	DetachInteractActor(AttachInteractActorRight);
	AttachInteractActorRight = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "TouchGripRight_Released");
}

void APawnVRBase::TriggerLeft_Pressed() {
	if (death)
		return;

	if (!AttachInteractActorLeft) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorLeft not valid");
		return;
	}
	AttachInteractActorLeft->ActivateInteract();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "TriggerLeft_Pressed");
}

void APawnVRBase::TriggerLeft_Released() {
	if (death)
		return;
}

void APawnVRBase::TriggerRight_Pressed() {
	if (death)
		return;

	if (!AttachInteractActorRight) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "AttachInteractActorRight not valid");
		return;
	}
	AttachInteractActorRight->ActivateInteract();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "TriggerRight_Pressed");
}

void APawnVRBase::TriggerRight_Released() {
	if (death)
		return;
}
/******************************************************************/

void APawnVRBase::BeginPlay()
{
	Super::BeginPlay();
	OnResetVR();
}


// Called every frame
void APawnVRBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


AInteractBase* APawnVRBase::GetOevrlapInteractActor(UPrimitiveComponent* primComp) {
	AInteractBase* _interactObj;

	if (!primComp) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "primComp not valid");
		return nullptr;
	}

	TArray<AActor*> OutOverlappingActors;
	primComp->GetOverlappingActors(OutOverlappingActors, AInteractBase::StaticClass());
	if (OutOverlappingActors.Num() <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "OutOverlappingActors.Num() <= 0");
		return nullptr;
	}
	_interactObj = Cast<AInteractBase>(OutOverlappingActors[0]);

	return _interactObj;
}


bool APawnVRBase::AttachInteractToController(UPrimitiveComponent* primComp, AActor* attachInteractActor) {
	if (!primComp || !attachInteractActor) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "AttachInteractToController error");
		return false;
	}
	FTransform _defTransf;
	attachInteractActor->AttachToComponent(primComp, FAttachmentTransformRules::KeepRelativeTransform, "None");
	attachInteractActor->SetActorRelativeTransform(_defTransf);
	return true;
}


bool APawnVRBase::DetachInteractActor(AActor* detachInteractActor) {
	if (!detachInteractActor) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "DetachInteractActor error");
		return false;
	}

	detachInteractActor->DetachRootComponentFromParent();
	return true;
}



bool APawnVRBase::IsDeath() {
	return death;
}

void APawnVRBase::SetDeath(bool newDeath) {
	if (death == newDeath)
		return;

	death = newDeath;
}

void APawnVRBase::InitDeath() {
	if (death)
		return;

	SetDeath(true);

	if (AttachInteractActorRight) {
		DetachInteractActor(AttachInteractActorRight);
		AttachInteractActorRight = nullptr;
	}
	if (AttachInteractActorLeft) {
		DetachInteractActor(AttachInteractActorLeft);
		AttachInteractActorLeft = nullptr;
	}
}

void APawnVRBase::InitRevival() {
	if (!death)
		return;

	SetDeath(false);
}