// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASCharacter::ASCharacter() //Use the constructor to inizialize variables, create components, etc.
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //The name how it sohws up in the editor in quotations.
	SpringArmComp->SetupAttachment(RootComponent); //Attach Springarm to RootComponent, which is the first component in the hierarchy. In our case, this is the capsule.

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp); //Attach our Cameracomponent to SpringarmComponent. The springarm controls the distance between the character and our camera.
}

// Called when the game starts or when spawned. 
void ASCharacter::BeginPlay() //This is run only after the constructor is done and everything is completely initialized. This is where we initialize timers.
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);

}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward); //This allows us to move forward and backwards. 1 is forward -1 is backwards.

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); //Allows us to turn
}

