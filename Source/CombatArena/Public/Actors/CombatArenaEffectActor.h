// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "CombatArenaEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

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

	UFUNCTION(BlueprintCallable)
	void ApplyEffectsToTarget(AActor* TargetActor, const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffects);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
protected:
	/*	Instant Effects	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Instant")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Instant")
	TArray<TSubclassOf<UGameplayEffect>> InstantEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Instant")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/*	Duration Effects  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Duration")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Duration")
	TArray<TSubclassOf<UGameplayEffect>> DurationEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/*	Infinite Effects  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Infinite")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Infinite")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	/*	General	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Options")
	bool bDestroyOnEffectRemoval = false;

	TMultiMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects | Options")
	float ActorLevel = 1.0f;
};
