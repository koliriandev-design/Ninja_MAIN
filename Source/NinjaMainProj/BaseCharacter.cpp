#include "BaseCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CombatComponent.h"
#include "CharacterData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"

ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// Set default values
	CharacterData = nullptr;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Apply character data if set
	if (CharacterData)
	{
		ApplyCharacterData();
	}
}

void ABaseCharacter::SetupCharacter(UCharacterData* Data)
{
	if (!Data) return;

	CharacterData = Data;
	ApplyCharacterData();
}

void ABaseCharacter::ApplyCharacterData()
{
	if (!CharacterData) return;

	// Apply mesh
	if (CharacterData->CharacterMesh)
	{
		GetMesh()->SetSkeletalMesh(CharacterData->CharacterMesh);
	}

	// Apply animation blueprint
	if (CharacterData->AnimationBlueprint)
	{
		GetMesh()->SetAnimInstanceClass(CharacterData->AnimationBlueprint);
	}

	// Apply movement settings
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterData->WalkSpeed;
	}

	// Pass animation references to combat component
	if (CombatComponent && CharacterData->AnimationSet.MeleeAttackMontage)
	{
		// In a real implementation, you would need to set this through a setter function
		// or use a different approach to pass the montage to the combat component
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Basic input binding
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);
	
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::StartAttack);
}

void ABaseCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ABaseCharacter::StartAttack()
{
	if (CombatComponent)
	{
		CombatComponent->PerformMeleeAttack();
	}
}