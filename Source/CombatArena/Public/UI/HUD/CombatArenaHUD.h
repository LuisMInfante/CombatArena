// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatArenaHUD.generated.h"

/*
	* 
*/

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UCombatArenaUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class COMBATARENA_API ACombatArenaHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitOverlay(APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent,
		UAttributeSet* InAttributeSet
		);
	
public:
	UPROPERTY()
	TObjectPtr<UCombatArenaUserWidget> OverlayWidget;
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "OverlayWidgetClass"))
	TSubclassOf<UCombatArenaUserWidget> m_OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> m_OverlayWidgetController;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "OverlayWidgetControllerClass"))
	TSubclassOf<UOverlayWidgetController> m_OverlayWidgetControllerClass;
};
