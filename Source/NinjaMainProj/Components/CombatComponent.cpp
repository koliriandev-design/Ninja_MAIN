#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsAttacking = false;
	MeleeAttackMontage = nullptr;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::PerformMeleeAttack()
{
	if (bIsAttacking) return;
	
	bIsAttacking = true;
	PlayMeleeAttackMontage();
	
	// Set a timer to reset the attack state
	// In a real implementation, you would use animation notifies
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
		OnMeleeAttackCompleted();
	});
}

void UCombatComponent::PlayMeleeAttackMontage()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !MeleeAttackMontage) return;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->Montage_Play(MeleeAttackMontage);
}

void UCombatComponent::OnMeleeAttackCompleted()
{
	bIsAttacking = false;
}