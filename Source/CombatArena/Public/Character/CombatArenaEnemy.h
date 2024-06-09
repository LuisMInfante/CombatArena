// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "Character/CombatArenaCharacterBase.h"
#include "CombatArenaEnemy.generated.h"

/*
	* AI Controlled Character
*/
UCLASS()
class COMBATARENA_API ACombatArenaEnemy : public ACombatArenaCharacterBase
{
	GENERATED_BODY()

public:
	ACombatArenaEnemy();
	
protected:
	virtual void BeginPlay() override;
};
