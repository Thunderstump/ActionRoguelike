// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

//The more includes, the more compilation time. So instead we "forward declare":

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY() //Macro by Unreal Engine, adds a lot of code and needs to be the first line of the class. 
	 
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; //For a third person character, zooms

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp; //To get a camera in game
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //This is part of actor. It will be called when the level is first loaded. But also when our character spawns in to the world.

	void MoveForward(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; //This gets called every frame. Deltatime is the amount of seconds that has passed since the last frame. Probably 16ms for 60fps.

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //Input, such as movement.

};
