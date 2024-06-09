// Copyright Luis Infante


#include "UI/Widgets/CombatArenaUserWidget.h"

void UCombatArenaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
