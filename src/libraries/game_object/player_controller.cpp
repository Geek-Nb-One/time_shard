#include "player_controller.h"

namespace ts
{
    void PlayerController::init()
    {
        transform = getGameObject()->getComponent<Transform>();
    }

    void PlayerController::update(float deltaTime)
    {
        
        if (input->isActive(ControlAction::MOVE_LEFT))
        {
            Console::logFrame("Moving Left");
            transform->position.x -= walkingSpeed * deltaTime;
        }
        if (input->isActive(ControlAction::MOVE_RIGHT))
        {
            transform->position.x += walkingSpeed * deltaTime;
        }
        if (input->isActive(ControlAction::MOVE_UP))
        {
            transform->position.y -= walkingSpeed * deltaTime;
        }
        if (input->isActive(ControlAction::MOVE_DOWN))
        {
            transform->position.y += walkingSpeed * deltaTime;
        }
    }
}