#pragma once

#include "component.h"

namespace ts
{
    class Transform : public Component
    {
    public:
        void init() override;
        void update(float deltaTime) override{};
        void destroy() override{};

        glm::vec3 position;

        // Add transform-specific methods and members here
    };
}