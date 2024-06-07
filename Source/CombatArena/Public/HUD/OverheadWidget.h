// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/*
	* Widget Above User's Head
*/

class UTextBlock;

UCLASS()
class COMBATARENA_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDisplayText(const FString& Text) const;

	UFUNCTION(BlueprintCallable)
	void GetPlayerNetRole(const APawn* InPawn) const;

	UFUNCTION(BlueprintCallable)
	void GetPlayerName(const APawn* InPawn);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> m_DisplayText;

protected:
	virtual void NativeDestruct() override;

private:
	FTimerHandle m_PlayerNameTimerHandle;
};
