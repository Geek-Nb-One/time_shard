#include "ui_controller.h"

#include <managers/event_manager.h>
namespace ts
{
void UiController::update(float deltaTime)
{
    if(input->isActive(ControlAction::START_ACTION))
    {
        Console::logFrame("UiController detected START_ACTION, publishing ChangeSceneEvent");
        ChangeSceneEvent event;
        event.newSceneName = "test_scene";
        EventManager::getInstance()->emit<ChangeSceneEvent>(event);
    }
}
}