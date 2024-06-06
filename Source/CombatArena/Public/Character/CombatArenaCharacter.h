// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "Character/CombatArenaCharacterBase.h"
#include "CombatArenaCharacter.generated.h"

/*
	* Player Controlled Character
*/
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;

UCLASS()
class COMBATARENA_API ACombatArenaCharacter : public ACombatArenaCharacterBase
{
	GENERATED_BODY()

public:
	ACombatArenaCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	
private:
	TObjectPtr<UCharacterMovementComponent> m_CharacterMovement;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> m_CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> m_Camera;
	
};
