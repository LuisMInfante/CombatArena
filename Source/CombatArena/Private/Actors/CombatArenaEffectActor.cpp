// Copyright Luis Infante


#include "Actors/CombatArenaEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

ACombatArenaEffectActor::ACombatArenaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void ACombatArenaEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatArenaEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Get the Ability System Component of the Target Actor
	TObjectPtr<UAbilitySystemComponent> TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC) return;
	check(GameplayEffectClass);

	// Create a GameplayEffectContext based on Target Actor
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	// Create a GameplayEffectSpec based on Target Actor
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, ActorLevel, EffectContextHandle);

	// Apply Gameplay Effect to Target Actor
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);

	// If duration is Infinite 
	if (EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		// Must be removed
		if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			// Add Effect to our map
			ActiveEffectHandles.Add(TargetASC, ActiveEffectHandle);
		}
	}
}

void ACombatArenaEffectActor::ApplyEffectsToTarget(AActor* TargetActor,
	const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffects)
{
	for (const TSubclassOf<UGameplayEffect> GameplayEffect : GameplayEffects)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffect);
	}
}

void ACombatArenaEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!InstantEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, InstantEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!DurationEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, DurationEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!InfiniteEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, InfiniteEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
}

void ACombatArenaEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!InstantEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, InstantEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!DurationEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, DurationEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!InfiniteEffects.IsEmpty())
		{
			ApplyEffectsToTarget(TargetActor, InfiniteEffects);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Get the Ability System Component of our Target Actor
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// Find and store all Gameplay Effects associated with the Effect Actor
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		ActiveEffectHandles.MultiFind(TargetASC, HandlesToRemove);

		// Remove the Effects and Remove ASC from Map
		for (const FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			TargetASC->RemoveActiveGameplayEffect(Handle, 1);
			ActiveEffectHandles.RemoveSingle(TargetASC, Handle);
		}
	}
}
