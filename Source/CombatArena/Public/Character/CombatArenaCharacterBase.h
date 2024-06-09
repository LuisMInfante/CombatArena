// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "AbilitySystemInterface.h"
#include "CombatArenaCharacterBase.generated.h"
/*
	* Traits Shared Between Player and AI
*/

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class COMBATARENA_API ACombatArenaCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACombatArenaCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
