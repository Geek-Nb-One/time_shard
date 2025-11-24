#pragma once

#include "base_component.h"
#include "movement.h"
#include <managers/input_manager.h>

namespace ts
{
    class PlayerController : public Component
    {
    public:
        void init() override;
        void update(float deltaTime) override;

        UpdatePriority getPriority() const override { return INPUT; }

        void setEnabled(bool isEnabled);

    private:

        Movement* movement = nullptr;
        InputManager* input = InputManager::getInstance();

        float walkingSpeed = 240.0f;

        bool enabled = true;

    };
}