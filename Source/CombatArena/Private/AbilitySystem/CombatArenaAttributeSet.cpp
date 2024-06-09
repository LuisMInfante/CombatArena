// Copyright Luis Infante


#include "AbilitySystem/CombatArenaAttributeSet.h"

#include "Net/UnrealNetwork.h"

UCombatArenaAttributeSet::UCombatArenaAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitShields(100.0f);
	InitMaxShields(100.0f);
}

void UCombatArenaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Always Replicating
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, Shields, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, MaxShields, COND_None, REPNOTIFY_Always);
}

void UCombatArenaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, Health, OldHealth);
}

void UCombatArenaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, MaxHealth, OldMaxHealth);
}

void UCombatArenaAttributeSet::OnRep_Shields(const FGameplayAttributeData& OldShields) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, Shields, OldShields);
}

void UCombatArenaAttributeSet::OnRep_MaxShields(const FGameplayAttributeData& OldMaxShields) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, MaxShields, OldMaxShields);
}
