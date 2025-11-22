#include "player_controller.h"

namespace ts
{
    void PlayerController::init()
    {
        movement = getGameObject()->getComponent<Movement>();
    }

    void PlayerController::update(float deltaTime)
    {
            // Calculate movement vector
        glm::vec3 direction(0.0f);
        
        if (input->isActive(ControlAction::MOVE_LEFT))
        {
            direction.x -= 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_RIGHT))
        {
            direction.x += 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_UP))
        {
            direction.y -= 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_DOWN))
        {
            direction.y += 1.0f;
        }
        
        // Normalize diagonal movement for consistent speed
        if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);
            movement->move(direction);
            movement->setSpeed(walkingSpeed);
        } else {
            movement->stop();
        }
    }
}