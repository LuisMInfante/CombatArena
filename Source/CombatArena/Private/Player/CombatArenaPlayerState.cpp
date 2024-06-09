// Copyright Luis Infante


#include "Player/CombatArenaPlayerState.h"

#include "AbilitySystem/CombatArenaAttributeSet.h"
#include "AbilitySystem/CombatAbilitySystemComponent.h"

ACombatArenaPlayerState::ACombatArenaPlayerState()
{
	// Frequency of updates to clients
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); // PlayerController (Mixed)

	AttributeSet = CreateDefaultSubobject<UCombatArenaAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACombatArenaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
