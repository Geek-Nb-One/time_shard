#include "camera_tracker.h"

namespace ts
{
    void CameraTracker::init()
    {

        transform = getGameObject()->getComponent<Transform>();
    }

    void CameraTracker::update(float deltaTime)
    {

        // Example logic: Make the camera follow the target transform
        if (transform && targetTransform && _isTracking)
        {
            Console::logFrame("CameraTracker updating camera position");

            switch (followType)
            {
            case EXACT:
                followExact(deltaTime);
                break;
            case SMOOTH:
                followSmooth(deltaTime);
                break;
            default:
                break;
            }
        }
    }
    void CameraTracker::setTargetTransform(Transform *target)
    {
        targetTransform = target;
        startTracking();
    }

    void CameraTracker::startTracking()
    {
        _isTracking = true;
    }

    void CameraTracker::stopTracking()
    {
        _isTracking = false;
    }

    bool CameraTracker::isTracking() const
    {
        return _isTracking;
    }
    Transform *CameraTracker::getTransform() const
    {
        return transform;
    }
    void CameraTracker::setFollowType(FollowType type)
    {
        followType = type;
    }
    FollowType CameraTracker::getFollowType() const
    {
        return followType;
    }
    void CameraTracker::followExact(float deltaTime)
    {
        glm::vec3 direction = targetTransform->position - transform->position;
        float distance = glm::length(direction);
        Console::logFrame("CameraTracker followExact distance to target: " + std::to_string(distance));
        
        // Use smaller dead zone for exact mode
        const float deadZone = 0.1f;
        if (distance > deadZone) {
            // Much gentler snap speed to prevent overshooting
            float snapSpeed = 8.0f;
            float clampedSpeed = glm::min(snapSpeed, distance / deltaTime * 0.8f);
            
            glm::vec3 newPos = glm::mix(transform->position, targetTransform->position, clampedSpeed * deltaTime);
            transform->position = targetTransform->position;
        }
    }
    void CameraTracker::followSmooth(float deltaTime)
    {
        glm::vec3 direction = targetTransform->position - transform->position;
        float distance = glm::length(direction);
        
        // Smaller dead zone for smoother tracking
        const float deadZone = 0.2f;
        if (distance > deadZone)
        {
            // More gradual smoothing
            float smoothTime = 0.2f;  // Slower, more gradual approach
            float alpha = 1.0f - exp(-deltaTime / smoothTime);
            
            // Clamp alpha to prevent overshooting
            alpha = glm::min(alpha, 0.5f);
            
            glm::vec3 newPos = glm::mix(transform->position, targetTransform->position, alpha);
            transform->position = newPos;
            
            Console::logFrame("CameraTracker moving camera towards target. Distance: " + std::to_string(distance) + " Alpha: " + std::to_string(alpha));
        }
    }
}