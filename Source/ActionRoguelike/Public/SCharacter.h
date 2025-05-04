// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"




//The more includes, the more compilation time. So instead we "forward declare":

class UCameraComponent;
class USpringArmComponent;
//class USActionComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY() //Macro by Unreal Engine, adds a lot of code and needs to be the first line of the class. 
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_LookMouse;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_LookStick;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Interact;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Input_SecondaryAttack;


	/*VisibleAnywhere = read-only, still useful to view in-editor and enforce a convention.*/
	//UPROPERTY(VisibleAnywhere, Category = "Effects")

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

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

	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);
	void LookStick(const FInputActionValue& InputValue);
	/*
	void SprintStart();
	void SprintStop();
	void PrimaryAttack();
	void BlackHoleAttack();
	void Dash();
	void PrimaryInteract();
	*/
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; //This gets called every frame. Deltatime is the amount of seconds that has passed since the last frame. Probably 16ms for 60fps.

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //Input, such as movement.

};
