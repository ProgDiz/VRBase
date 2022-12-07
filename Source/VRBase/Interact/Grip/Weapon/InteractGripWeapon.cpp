// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Grip/Weapon/InteractGripWeapon.h"

AInteractGripWeapon::AInteractGripWeapon() {
	WeaponShotComponent = CreateDefaultSubobject<UWeaponShotComponent>("WeaponShotComponent");
}

void AInteractGripWeapon::ActivateInteract() {
	if (!WeaponShotComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "WeaponShotComponent not valid");
		return;
	}
	WeaponShotComponent->Shot(GetStartPosShot(), GetDirectionShot());
}

void AInteractGripWeapon::DeactivateInteract() {

}

FVector AInteractGripWeapon::GetDirectionShot_Implementation() {
	return GetActorForwardVector();
}

FVector AInteractGripWeapon::GetStartPosShot_Implementation() {
	return GetActorLocation();
}