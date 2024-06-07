// Copyright Luis Infante


#include "Character/CombatArenaAnimInstance.h"

#include "Character/CombatArenaCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCombatArenaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_OwnerCharacter = Cast<ACombatArenaCharacterBase>(TryGetPawnOwner());
	
	if (m_OwnerCharacter)
	{
		m_MovementComponent = m_OwnerCharacter->GetCharacterMovement();
	}
}

void UCombatArenaAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if(!m_OwnerCharacter)
	{
		m_OwnerCharacter = Cast<ACombatArenaCharacterBase>(TryGetPawnOwner());
	}

	if(!m_OwnerCharacter) return;

	FVector Velocity = m_OwnerCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	m_Speed = Velocity.Size();

	m_IsInAir = m_MovementComponent->IsFalling();
	m_IsAccelerating = m_MovementComponent->GetCurrentAcceleration().Size() ? true : false;

}
