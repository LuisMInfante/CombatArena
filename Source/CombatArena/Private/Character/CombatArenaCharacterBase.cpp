// Copyright Luis Infante


#include "Character/CombatArenaCharacterBase.h"


ACombatArenaCharacterBase::ACombatArenaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ACombatArenaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACombatArenaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
