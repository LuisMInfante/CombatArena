// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatArenaPlayerController.generated.h"

/*
	* Handle Player Input
*/

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ACharacter;
class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;

UCLASS()
class COMBATARENA_API ACombatArenaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACombatArenaPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Jump();
	
private:
	TObjectPtr<ACharacter> m_ControlledCharacter;
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> m_Subsystem;
	TObjectPtr<UEnhancedInputComponent> m_EnhancedInputComponent;
	
	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Mapping Context"))
	TObjectPtr<UInputMappingContext> m_CombatArenaContext;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Move Action"))
	TObjectPtr<UInputAction> m_MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Look Action"))
	TObjectPtr<UInputAction> m_LookAction;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Jump Action"))
	TObjectPtr<UInputAction> m_JumpAction;
};
