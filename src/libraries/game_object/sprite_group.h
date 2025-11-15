#pragma once

#include "base_component.h"
#include "transform.h"
namespace ts
{
    class SpriteGroup : public Component
    {
    public:
        void update(float deltaTime) override{};
        void destroy() override{};
        void init() override{};


        float getWidth() const;
        float getHeight() const;
        
        void setWidth(float width);
        void setHeight(float height);

        bool inCameraView(const glm::vec2& cameraPos, int cameraWidth, int cameraHeight) const;
    private:

        float width;
        float height;

        Transform* transform;

    };
}