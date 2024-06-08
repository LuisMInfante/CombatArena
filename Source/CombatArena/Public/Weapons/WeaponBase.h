// Copyright Luis Infante

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UWidgetComponent;

/* Weapon Types */
UENUM(BlueprintType)
enum EWeaponType : uint8
{
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_Rifle UMETA(DisplayName = "Rifle"),
	EWT_Shotgun UMETA(DisplayName = "Shotgun"),
	EWT_Sniper UMETA(DisplayName = "Sniper"),
	EWT_GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
	EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),

	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};

/* Weapon States */
UENUM(BlueprintType)
enum EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

/*
	* All Weapons Inherit from this
*/
UCLASS()
class COMBATARENA_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;
	void ShowPickupWidget(const bool bShowWidget) const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	UFUNCTION()
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties", meta = (DisplayName = "Weapon Mesh"))
	TObjectPtr<USkeletalMeshComponent> m_WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties", meta = (DisplayName = "Overlap Volume"))
	TObjectPtr<USphereComponent> m_OverlapVolume;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties | State", meta = (DisplayName = "Weapon State"))
	TEnumAsByte<EWeaponState> m_WeaponState;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties | Widgets", meta = (DisplayName = "Pickup Widget"))
	TObjectPtr<UWidgetComponent> m_PickupWidget;
};
