// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/CombatArenaWidgetController.h"
#include "OverlayWidgetController.generated.h"

/*
	* Widget Controller for Player HUD
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldsChangedSignature, float, NewShields);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxShieldsChangedSignature, float, NewMaxShields);

UCLASS(BlueprintType, Blueprintable)
class COMBATARENA_API UOverlayWidgetController : public UCombatArenaWidgetController
{
	GENERATED_BODY()

public:
	//~Begin UCombatArenaWidgetController Interface
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	//~End UCombatArenaWidgetController Interface

	/* Delegates */
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnShieldsChangedSignature OnShieldsChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnMaxShieldsChangedSignature OnMaxShieldsChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ShieldsChanged(const FOnAttributeChangeData& Data) const;
	void MaxShieldsChanged(const FOnAttributeChangeData& Data) const;
};
