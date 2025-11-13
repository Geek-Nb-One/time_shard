#pragma once

#include "component.h"
#include  "transform.h"

namespace ts
{
    class Camera : public Component
    {
    public:

        void update(float deltaTime) override{};
        void destroy() override{};
        void init() override;

        glm::vec2 getScreenPosition(glm::vec3 position) const;
        glm::vec2 getScreenPosition(float x, float y, float z = 0) const;

        int getWidth() const;
        int getHeight() const;

        void setDimension(int width, int height);

        glm::vec3 getCenter() const;
    private:

        int width, height;
        Transform* transform = nullptr;

        // Add transform-specific methods and members here
    };
}