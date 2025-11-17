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

            glm::vec3 direction = targetTransform->position - transform->position;
            float distance = glm::length(direction);
            if (distance > 0.1f)
            {
                float speed = (distance < maxDistance) ? baseSpeed : maxSpeed;

                Console::logFrame("CameraTracker moving camera towards target. Distance: " + std::to_string(distance) + " Speed: " + std::to_string(speed));
                glm::vec3 movement = glm::normalize(direction) * speed * deltaTime;
                if (glm::length(movement) > distance)
                {
                    transform->position = targetTransform->position;
                }
                else
                {
                    transform->position += movement;
                }
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
}