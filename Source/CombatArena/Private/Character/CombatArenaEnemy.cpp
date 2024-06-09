// Copyright Luis Infante


#include "Character/CombatArenaEnemy.h"

#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatArenaAttributeSet.h"

ACombatArenaEnemy::ACombatArenaEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // AI Controlled (Minimal)

	AttributeSet = CreateDefaultSubobject<UCombatArenaAttributeSet>("AttributeSet");
	
}

void ACombatArenaEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Owner Actor is the AI and the Avatar is also the AI
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
