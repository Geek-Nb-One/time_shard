#include "player_controller.h"

namespace ts
{
    void PlayerController::init()
    {
        transform = getGameObject()->getComponent<Transform>();
    }

    void PlayerController::update(float deltaTime)
    {
        // Calculate movement vector
        glm::vec3 movement(0.0f);
        
        if (input->isActive(ControlAction::MOVE_LEFT))
        {
            movement.x -= 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_RIGHT))
        {
            movement.x += 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_UP))
        {
            movement.y -= 1.0f;
        }
        if (input->isActive(ControlAction::MOVE_DOWN))
        {
            movement.y += 1.0f;
        }
        
        // Normalize diagonal movement for consistent speed
        if (glm::length(movement) > 0.0f) {
            movement = glm::normalize(movement);
            transform->position += movement * walkingSpeed * deltaTime;
        }
    }
}