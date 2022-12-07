// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponShotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRBASE_API UWeaponShotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponShotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = Shot, BlueprintCallable)
		void Shot(FVector startPos, FVector dir);

protected:
	UPROPERTY(Category = Shot, EditAnywhere, BlueprintReadWrite)
		float distanceShot = 100000.f;
	UPROPERTY(Category = Shot, EditAnywhere, BlueprintReadWrite)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	UPROPERTY(Category = Shot, EditAnywhere, BlueprintReadWrite)
		float damage = 10.f;
};
