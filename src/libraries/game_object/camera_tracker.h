#pragma once

#include "base_component.h"
#include "transform.h"
namespace ts
{

    enum FollowType {
        EXACT,
        SMOOTH
    };
    
    class CameraTracker : public Component
    {
    public:

        void update(float deltaTime) override;
        void init() override;

        void setTargetTransform(Transform* target);
        void startTracking();
        void stopTracking();
        bool isTracking() const;

        Transform* getTransform() const;

        void setFollowType(FollowType type);

        FollowType getFollowType() const;

        UpdatePriority getPriority() const override { return CAMERA; }


    private:
        Transform* transform = nullptr;
        Transform* targetTransform = nullptr;

        bool _isTracking = false;

        FollowType followType = EXACT;

        float baseSpeed = 150.0f;
        float maxSpeed = 200.0f;
        float maxDistance = 50.0f;

        void followExact(float deltaTime);
        void followSmooth(float deltaTime);
    };
}
