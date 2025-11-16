#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterData.generated.h"

class USkeletalMesh;
class UAnimationAsset;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FCharacterAnimationSet
{
	GENERATED_BODY()

	// Animation assets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* MeleeAttackMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* JumpMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* DeathMontage = nullptr;
};

UCLASS(BlueprintType)
class NINJAMAINPROJ_API UCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Character mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	USkeletalMesh* CharacterMesh = nullptr;

	// Animation blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TSubclassOf<UAnimInstance> AnimationBlueprint = nullptr;

	// Animation sets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	FCharacterAnimationSet AnimationSet;

	// Combat parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BaseDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackRange = 100.0f;

	// Movement parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 900.0f;
};