#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Делегаты
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, double, NewHealth, double, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, double, DamageAmount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINJAMAINPROJ_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	// Основные параметры здоровья
	
	// Максимальное здоровье
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(ClampMin="1.0"))
	double MaxHealth = 100.0;

	// Текущее здоровье
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	double Health = 100.0;

	// Настройка параметров для материала хелсбара
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MinMaterialValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxMaterialValue = 1.21f;

	// События
	
	// Событие изменения здоровья (NewHealth, Delta)
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnHealthChanged OnHealthChanged;

	// Событие смерти
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDeath OnDeath;

	// Событие получения урона
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDamageTaken OnDamageTaken;

	// Функции
	
	// Инициализация здоровья
	UFUNCTION(BlueprintCallable, Category="Health")
	void InitializeHealth(double InMaxHealth, double InHealth);

	// Получение урона
	UFUNCTION(BlueprintCallable, Category="Health")
	void TakeDamage(double Amount);

	// Лечение
	UFUNCTION(BlueprintCallable, Category="Health")
	void Heal(double Amount);

	// Проверка смерти
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	bool IsDead() const;

	// Получить текущее здоровье
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	double GetHealth() const;

	// Получить максимальное здоровье
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	double GetMaxHealth() const;

	// Получить процент здоровья
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	double GetHealthPercent() const;

	// Получить значения для материала хелсбара (для MI_HealthBar)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	float GetHealthBarMaterialValue() const;

protected:
	virtual void BeginPlay() override;

private:
	// Флаг для предотвращения множественных вызовов смерти
	bool bDeathBroadcasted = false;

	// Внутренние функции
	void BroadcastHealthChanged(double OldHealth);
	void HandleDeathOnce();
		
};
