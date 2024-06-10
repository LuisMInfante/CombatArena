// Copyright Luis Infante


#include "UI/WidgetControllers/CombatArenaWidgetController.h"

void UCombatArenaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UCombatArenaWidgetController::BroadcastInitialValues()
{
	/*	Implement in Child Classes	*/
}

void UCombatArenaWidgetController::BindCallbacksToDependencies()
{
	/*	Implement in Child Classes	*/
}
