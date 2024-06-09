// Copyright Luis Infante


#include "UI/HUD/OverheadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(const FString& Text) const
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(Text));
	}
}

void UOverheadWidget::GetPlayerNetRole(const APawn* InPawn) const
{
	const ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;

	switch (LocalRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
			break;
	case ROLE_None:
		Role = FString("None");
		break;
	default:
		break;
	}

	FString FormattedString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(FormattedString);
}

void UOverheadWidget::GetPlayerName(const APawn* InPawn)
{
	// If Player Has Spawned In
	if (TObjectPtr<APlayerState> PlayerState = InPawn->GetPlayerState())
	{
		FString PlayerName = FString::Printf(TEXT("%s"), *PlayerState->GetPlayerName());
		SetDisplayText(PlayerName);

		// Stop Timer
		if(TObjectPtr<UWorld> World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(m_PlayerNameTimerHandle);
			return;
		}
	}

	// Start Recall if Timer isn't running
	if(!m_PlayerNameTimerHandle.IsValid())
	{
		if(TObjectPtr<UWorld> World = GetWorld())
		{
			World->GetTimerManager().SetTimer(m_PlayerNameTimerHandle,
									[this, InPawn](){GetPlayerName(InPawn);},
										0.5f,
										true
										);
		}
	}
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
