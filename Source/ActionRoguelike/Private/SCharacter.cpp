// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/RotationMatrix.h"


// Sets default values
ASCharacter::ASCharacter() //Use the constructor to inizialize variables, create components, etc.
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //The name how it sohws up in the editor in quotations.
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent); //Attach Springarm to RootComponent, which is the first component in the hierarchy. In our case, this is the capsule.

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp); //Attach our Cameracomponent to SpringarmComponent. The springarm controls the distance between the character and our camera.

	//InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	//AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	//ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");




	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned. 
void ASCharacter::BeginPlay() //This is run only after the constructor is done and everything is completely initialized. This is where we initialize timers.
{
	Super::BeginPlay();
	
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

	const APlayerController* PC = GetController <APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);


	Subsystem->ClearAllMappings();


	// Add mappings for our game, more complex games may have multiple Contexts that are added/removed at runtime
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	// New Enhanced Input system
	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	//General
	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ASCharacter::Move);
	InputComp->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ASCharacter::Jump);
	//InputComp->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryInteract);

	// Sprint while key is held
	//InputComp->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ASCharacter::SprintStart);
	//InputComp->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ASCharacter::SprintStop);

	// MKB
	InputComp->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ASCharacter::LookMouse);
	//Gamepad
	InputComp->BindAction(Input_LookStick, ETriggerEvent::Triggered, this, &ASCharacter::LookStick);

	//Abilities
	//InputComp->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
	//InputComp->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, &ASCharacter::BlackHoleAttack);
	//InputComp->BindAction(Input_Dash, ETriggerEvent::Triggered, this, &ASCharacter::Dash);
}

void ASCharacter::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	//move forward/back
	AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	//Move Right/Left strafe
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);
}

void ASCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);

}

void ASCharacter::LookStick(const FInputActionValue& InputValue)
{
	FVector2D Value = InputValue.Get<FVector2D>();

	//Track negative as we'll lose this during the conversion
	bool XNegative = Value.X < 0.f;
	bool YNegative = Value.Y < 0.f;

	//Can further modify with 'sensitivity' settings
	static const float LookYawRate = 100.0f;
	static const float LookPitchRate = 50.0f;

	//non-linear to make aiming a little easier
	Value = Value * Value;

	if (XNegative)
	{
		Value.X *= -1.f;
	}

	if (YNegative)
	{
		Value.Y *= -1.f;
	}

	AddControllerYawInput(Value.X * LookYawRate * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(Value.Y * LookPitchRate * GetWorld()->GetDeltaSeconds());
}

/*
void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


void ASCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void ASCharacter::BlackHoleAttack()
{
	ActionComp->StartActionByName(this, "Blackhole");
}

void ASCharacter::Dash()
{
	ActionComp->StartActionByName(this,"Dash");
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

*/