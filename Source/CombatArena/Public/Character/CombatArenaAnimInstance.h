// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CombatArenaAnimInstance.generated.h"

/*
	*
*/
class ACombatArenaCharacterBase;
class UCharacterMovementComponent;

UCLASS()
class COMBATARENA_API UCombatArenaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = true, DisplayName = "Owner"))
	TObjectPtr<ACombatArenaCharacterBase> m_OwnerCharacter;

	TObjectPtr<UCharacterMovementComponent> m_MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = true, DisplayName = "Speed"))
	float m_Speed;
	
	UPROPERTY(BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = true, DisplayName = "InAir"))
	bool m_bIsInAir;
	
	UPROPERTY(BlueprintReadOnly, Category = "Character|Movement", meta = (AllowPrivateAccess = true, DisplayName = "Accelerating"))
	bool m_bIsAccelerating;
};
