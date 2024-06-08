// Copyright Luis Infante


#include "Weapons/WeaponBase.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/CombatArenaCharacter.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Construct Weapon
	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(m_WeaponMesh);
	m_WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block); // Drop Weapon on Ground
	m_WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // Players/AI can walk through it
	m_WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Spawns in with no collision

	// Construct Overlap Volume
	m_OverlapVolume = CreateDefaultSubobject<USphereComponent>("OverlapVolume");
	m_OverlapVolume->SetupAttachment(RootComponent);
	// Must be enabled on server
	m_OverlapVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_OverlapVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Construct Widget
	m_PickupWidget = CreateDefaultSubobject<UWidgetComponent>("Pickup Widget");
	m_PickupWidget->SetupAttachment(RootComponent);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// If we are on the server 
	if (HasAuthority())
	{
		m_OverlapVolume->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		m_OverlapVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		m_OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnSphereOverlap);
		m_OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnSphereEndOverlap);
	}

	if (m_PickupWidget)
	{
		m_PickupWidget->SetVisibility(false);
	}
}

void AWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ACombatArenaCharacter> Player = Cast<ACombatArenaCharacter>(OtherActor);
	// If the Actor that overlapped is a Human Player
	if (Player)
	{
		Player->SetOverlappedWeapon(this);
	}
}

void AWeaponBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TObjectPtr<ACombatArenaCharacter> Player = Cast<ACombatArenaCharacter>(OtherActor);
	// If the Actor that overlapped is a Human Player
	if (Player)
	{
		Player->SetOverlappedWeapon(nullptr);
	}
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::ShowPickupWidget(const bool bShowWidget) const
{
	if (m_PickupWidget)
	{
		m_PickupWidget->SetVisibility(bShowWidget);
	}
}

