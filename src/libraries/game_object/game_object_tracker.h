#pragma once

#include "base_component.h"
#include "transform.h"

namespace ts
{
    class GameObjectTracker : public Component
    {

    public:
        void init() override {};
        void update(float deltaTime) override
        {
            std::cout << "GameObject position: " << round(getGameObject()->getComponent<Transform>()->position.x) << "," << round(getGameObject()->getComponent<Transform>()->position.y) << std::endl;
        };
        void destroy() override {};

        UpdatePriority getPriority() const override { return REGULAR; }
    };

}