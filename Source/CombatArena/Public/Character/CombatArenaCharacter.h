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
class UWidgetComponent;
class ACombatArenaPlayerState;
class AWeaponBase;

UCLASS()
class COMBATARENA_API ACombatArenaCharacter : public ACombatArenaCharacterBase
{
	GENERATED_BODY()

public:
	ACombatArenaCharacter();
	virtual void Tick(float DeltaTime) override;

	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~ End APawn Interface
	
	void SetOverlappedWeapon(const TObjectPtr<AWeaponBase>& Weapon);

protected:
	virtual void BeginPlay() override;

private:
	void InitAbilityActorInfo();
	
	UFUNCTION()
	void OnRep_OverlappedWeapon(AWeaponBase* LastOverlappedWeapon) const;

	
private:
	UPROPERTY(VisibleAnywhere, Category = "Player State")
	TObjectPtr<ACombatArenaPlayerState> m_PlayerState;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> m_CharacterMovement;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> m_CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Overhead Widget"))
	TObjectPtr<UWidgetComponent> m_OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappedWeapon)
	TObjectPtr<AWeaponBase> m_OverlappedWeapon;
};
