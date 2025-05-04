// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;


UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp; //This is the basic collision

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp; //Velocity

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp; //Particle system

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
