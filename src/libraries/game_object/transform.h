#pragma once

#include "base_component.h"

namespace ts
{
    class Transform : public Component
    {
    public:
 
        glm::vec3 position;

        // Add transform-specific methods and members here
        UpdatePriority getPriority() const override { return IGNORE; }
    };
}