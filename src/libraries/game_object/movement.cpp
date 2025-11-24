#include "movement.h"

namespace ts
{
    void Movement::update(float deltaTime)
    {
        if (_isMoving)
        {
            Transform *transform = getGameObject()->getComponent<Transform>();
            if (transform)
            {
                transform->position += direction * speed * deltaTime;
            }
        }
    }
    void Movement::moveBack()
    {
        if (_isMoving)
        {
            Transform *transform = getGameObject()->getComponent<Transform>();
            if (transform)
            {
                transform->position -= direction;
            }
        }
    }
    void Movement::move(const glm::vec3 &dir)
    {
        direction = glm::normalize(dir);
        _isMoving = true;
    }
    void Movement::stop()
    {
        _isMoving = false;
        direction = glm::vec3(0, 0, 0);
    }
    void Movement::setSpeed(float newSpeed)
    {
        speed = newSpeed;
    }

    bool Movement::isMoving() const
    {
        return _isMoving;
    }
    Direction Movement::getDirection() const
    {
        return _isMoving ? direction.x > 0 ? RIGHT : direction.x < 0 ? LEFT
                                                 : direction.y > 0   ? DOWN
                                                                     : UP
                         : NONE;
    }
}