// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatArenaAttributeSet.generated.h"

/*
	* Set of Attributes for Characters
*/

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	/* Source Effect Properties	*/
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	/* Target Effect Properties	*/
	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

UCLASS()
class COMBATARENA_API UCombatArenaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCombatArenaAttributeSet();
	
	//~ Begin APawn Interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~ End APawn Interface
	
	//~ Begin UAttributeSet Interface
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//~ End UAttributeSet Interface
	
	/*	Health Attributes	*/
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(UCombatArenaAttributeSet, Health);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UCombatArenaAttributeSet, MaxHealth);
	
	/*	Shield Attributes	*/
	UFUNCTION()
	void OnRep_Shields(const FGameplayAttributeData& OldShields) const;
	ATTRIBUTE_ACCESSORS(UCombatArenaAttributeSet, Shields);
	
	UFUNCTION()
	void OnRep_MaxShields(const FGameplayAttributeData& OldMaxShields) const;
	ATTRIBUTE_ACCESSORS(UCombatArenaAttributeSet, MaxShields);
	
public:
	/*	Health Attributes	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes | Health")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes | Health")
	FGameplayAttributeData MaxHealth;
	
	/*	Shields Attributes	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shields, Category = "Attributes | Shields")
	FGameplayAttributeData Shields;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShields, Category = "Attributes | Shields")
	FGameplayAttributeData MaxShields;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
};
