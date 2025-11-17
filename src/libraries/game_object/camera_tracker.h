#pragma once

#include "base_component.h"
#include "transform.h"
namespace ts
{
    class CameraTracker : public Component
    {
    public:
        void init() override;
        void update(float deltaTime) override;
        void destroy() override{};

        void setTargetTransform(Transform* target);
        void startTracking();
        void stopTracking();
        bool isTracking() const;

        Transform* getTransform() const;

    private:
        Transform* transform = nullptr;
        Transform* targetTransform = nullptr;

        bool _isTracking = false;

        float baseSpeed = 150.0f;
        float maxSpeed = 200.0f;
        float maxDistance = 50.0f;
    };
}
