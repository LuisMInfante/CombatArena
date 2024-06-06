// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "CombatArenaCharacterBase.generated.h"
/*
	* Traits Shared Between Player and AI
*/

UCLASS(Abstract)
class COMBATARENA_API ACombatArenaCharacterBase : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ACombatArenaCharacterBase();
	virtual void Highlight() override;
	virtual void RemoveHighlight() override;
	
protected:
	virtual void BeginPlay() override;
	
};
