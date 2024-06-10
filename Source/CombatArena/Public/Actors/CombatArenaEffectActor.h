// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatArenaEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class COMBATARENA_API ACombatArenaEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACombatArenaEffectActor();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Instant")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
