#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

UHealthComponent::UHealthComponent()
{
	// Отключаем тик
	PrimaryComponentTick.bCanEverTick = false;

	// Начальные значения
	MaxHealth = 100.0;
	Health = MaxHealth;
	bDeathBroadcasted = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeHealth(MaxHealth, Health);

}

// Основные публичные функции

void UHealthComponent::InitializeHealth(double InMaxHealth, double InHealth)
{
	// Проверка корректности значений и установка максимального здоровья
	if (InMaxHealth < 1.0) MaxHealth = 1.0;
	else MaxHealth = InMaxHealth;

	if (InHealth < 0.0) Health = 0.0;
	else if (InHealth > MaxHealth) Health = MaxHealth;
	else Health = InHealth;
	
	bDeathBroadcasted = false;


}

void UHealthComponent::TakeDamage(double Amount)
{
	// Проверки - нет урона или уже мертв, первая тк в дальнейшем я хочу сделать падение с высоты и столкновение, поэтому урон может быть 0
	if (Amount <= 0.0) return;
	if (IsDead()) return;

	const double OldHealth = Health;

	// Применяем урон
	Health = Health - Amount;
	if (Health < 0.0) Health = 0.0;

	// Оповещаем о получении урона
	OnDamageTaken.Broadcast(Amount);
	
	// Оповещаем об изменении здоровья
	BroadcastHealthChanged(OldHealth);

	// Проверяем смерть
	if (IsDead()) HandleDeathOnce();
}

void UHealthComponent::Heal(double Amount)
{
	// Проверки - нет лечения, уже мертв
	if (Amount <= 0.0) return;
	if (IsDead()) return;

	// Сохраняем старое значение
	const double OldHealth = Health;

	// Лечим Health = Health + Amount, но не больше MaxHealth
	Health = Health + Amount;
	if (Health > MaxHealth) Health = MaxHealth;

	// Оповещаем
	BroadcastHealthChanged(OldHealth);


}

// Остальные публичные функции

bool UHealthComponent::IsDead() const
{
	if (Health <= 0.0) return true;
	return false;
}

double UHealthComponent::GetHealth() const
{
	return Health;
}

double UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

double UHealthComponent::GetHealthPercent() const
{
	if (MaxHealth > 0.0) return Health / MaxHealth ;
	return 0.0;
}

float UHealthComponent::GetHealthBarMaterialValue() const
{
	//Рассчет значений для хелс материала	
	float HealthPercent = static_cast<float>(GetHealthPercent());
	
	float MaterialValue = MaxMaterialValue + (MinMaterialValue - MaxMaterialValue) * HealthPercent;
	
	return MaterialValue;
}

// Приватные функции

void UHealthComponent::BroadcastHealthChanged(double OldHealth)
{
	// Вычисляем дельту и оповещаем
	const double Delta = Health - OldHealth;
	OnHealthChanged.Broadcast(Health, Delta);

	
}

void UHealthComponent::HandleDeathOnce()
{
	// Если смерть еще не обработана, то обрабатываем.
	if (bDeathBroadcasted) return;
	bDeathBroadcasted = true;
	OnDeath.Broadcast();
}

