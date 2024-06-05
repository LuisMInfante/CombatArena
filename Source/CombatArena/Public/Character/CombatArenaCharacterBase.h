// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatArenaCharacterBase.generated.h"
/*
	* Traits Shared Between Player and AI
*/

UCLASS(Abstract)
class COMBATARENA_API ACombatArenaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACombatArenaCharacterBase();
	
protected:
	virtual void BeginPlay() override;
	
};
