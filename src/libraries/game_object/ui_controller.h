#pragma once

#include "base_component.h"
#include <managers/input_manager.h>

namespace ts
{
    class UiController : public ts::Component
    {
    public:


        void update(float deltaTime) override;

        UpdatePriority getPriority() const override { return REGULAR; }

    private:
        InputManager* input = InputManager::getInstance();
    };
}
