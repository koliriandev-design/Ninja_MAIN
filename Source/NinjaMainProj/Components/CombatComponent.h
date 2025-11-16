#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

// Forward declarations
class UAnimMontage;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NINJAMAINPROJ_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	// Combat functions
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformMeleeAttack();

	// Animation functions
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayMeleeAttackMontage();

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat")
	bool IsAttacking() const { return bIsAttacking; }

private:
	// Combat state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking = false;

	// Animation references
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* MeleeAttackMontage;

	// Internal functions
	void OnMeleeAttackCompleted();
};