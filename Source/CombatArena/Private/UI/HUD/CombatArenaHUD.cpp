// Copyright Luis Infante


#include "UI/HUD/CombatArenaHUD.h"

#include "UI/Widgets/CombatArenaUserWidget.h"

void ACombatArenaHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), m_OverlayWidgetClass);
	Widget->AddToViewport();
	
}
