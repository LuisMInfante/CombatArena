// Copyright Luis Infante


#include "UI/HUD/CombatArenaHUD.h"

#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/CombatArenaUserWidget.h"

UOverlayWidgetController* ACombatArenaHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	// Create a Widget Controller if it doesn't already exist
	if(!m_OverlayWidgetController)
	{
		m_OverlayWidgetController = NewObject<UOverlayWidgetController>(this, m_OverlayWidgetControllerClass);
		m_OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		m_OverlayWidgetController->BindCallbacksToDependencies();
		
		return m_OverlayWidgetController;
	}
	
	return m_OverlayWidgetController;
}

void ACombatArenaHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
	UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	// Checking for values in Blueprint
	checkf(m_OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized in BP_CombatArenaHUD!"));
	checkf(m_OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized in BP_CombatArenaHUD!"));

	// Set our Overlay Widget to Blueprint values can cast to our Subclass
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), m_OverlayWidgetClass);
	OverlayWidget = Cast<UCombatArenaUserWidget>(Widget);

	// Create Widget Controller and Set Controller Parameters
	const FWidgetControllerParams ControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAttributeSet);
	m_OverlayWidgetController = GetOverlayWidgetController(ControllerParams);

	// Set our Widget Controller
	OverlayWidget->SetWidgetController(m_OverlayWidgetController);
	
	m_OverlayWidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}