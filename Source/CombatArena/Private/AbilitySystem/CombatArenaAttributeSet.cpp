// Copyright Luis Infante


#include "AbilitySystem/CombatArenaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UCombatArenaAttributeSet::UCombatArenaAttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);
	InitShields(0.0f);
	InitMaxShields(100.0f);
}

void UCombatArenaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Always Replicating
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, Shields, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatArenaAttributeSet, MaxShields, COND_None, REPNOTIFY_Always);
}

void UCombatArenaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f,GetMaxHealth());
	}

	if (Attribute == GetShieldsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f,GetMaxShields());
	}
}

void UCombatArenaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);
}

void UCombatArenaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, Health, OldHealth);
}

void UCombatArenaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, MaxHealth, OldMaxHealth);
}

void UCombatArenaAttributeSet::OnRep_Shields(const FGameplayAttributeData& OldShields) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, Shields, OldShields);
}

void UCombatArenaAttributeSet::OnRep_MaxShields(const FGameplayAttributeData& OldMaxShields) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatArenaAttributeSet, MaxShields, OldMaxShields);
}

void UCombatArenaAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties)
{
	
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceAbilitySystemComponent =
		EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// Get Controller and Character info from Source (Thing causing the effect)
	if (IsValid(EffectProperties.SourceAbilitySystemComponent) &&
		EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() &&
		EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

		// If we can't get the controller from the ASC then try from the Actor
		if (!EffectProperties.SourceController && EffectProperties.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
		}

		// Get the Character
		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	// Get info from target
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetAbilitySystemComponent =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}
