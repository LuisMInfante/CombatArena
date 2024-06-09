// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatArenaWidgetController.generated.h"

/*
	* Base Class for Widget Controller
	* Handles All Data Sent to Widgets
*/
UCLASS()
class COMBATARENA_API UCombatArenaWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
};
