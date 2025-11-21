#pragma once

#include "base_component.h"
#include "transform.h"
#include <managers/input_manager.h>

namespace ts
{
    class PlayerController : public Component
    {
    public:
        void init() override;
        void update(float deltaTime) override;
        void destroy() override{};

    private:

        Transform* transform = nullptr;
        InputManager* input = InputManager::getInstance();

        float walkingSpeed = 240.0f;

    };
}