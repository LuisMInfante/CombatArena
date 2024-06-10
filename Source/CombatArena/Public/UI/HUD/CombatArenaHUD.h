// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatArenaHUD.generated.h"

/*
	* 
*/

class UCombatArenaUserWidget;

UCLASS()
class COMBATARENA_API ACombatArenaHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UCombatArenaUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "OverlayWidgetClass"))
	TSubclassOf<UCombatArenaUserWidget> m_OverlayWidgetClass;
};
