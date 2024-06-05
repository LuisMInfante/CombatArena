// Copyright Luis Infante


#include "Character/CombatArenaCharacterBase.h"


ACombatArenaCharacterBase::ACombatArenaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ACombatArenaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}