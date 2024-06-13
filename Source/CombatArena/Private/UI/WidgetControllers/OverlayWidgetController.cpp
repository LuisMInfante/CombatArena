// Copyright Luis Infante


#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/CombatArenaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues(); // This is empty
	
	if(const UCombatArenaAttributeSet* CombatArenaAttributeSet = Cast<UCombatArenaAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(CombatArenaAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(CombatArenaAttributeSet->GetMaxHealth());
		OnShieldsChanged.Broadcast(CombatArenaAttributeSet->GetShields());
		OnMaxShieldsChanged.Broadcast(CombatArenaAttributeSet->GetMaxShields());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	if(const UCombatArenaAttributeSet* CombatArenaAttributeSet = Cast<UCombatArenaAttributeSet>(AttributeSet))
	{
		// Bind Health Changed
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CombatArenaAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

		// Bind Max Health Changed
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CombatArenaAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

		// Bind Shields Changed
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CombatArenaAttributeSet->GetShieldsAttribute()).AddUObject(this, &UOverlayWidgetController::ShieldsChanged);

		// Bind Max Shields Changed
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CombatArenaAttributeSet->GetMaxShieldsAttribute()).AddUObject(this, &UOverlayWidgetController::MaxShieldsChanged);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ShieldsChanged(const FOnAttributeChangeData& Data) const
{
	OnShieldsChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxShieldsChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxShieldsChanged.Broadcast(Data.NewValue);
}
