#include "collider.h"

namespace ts
{
    void Collider::init()
    {
        transform = getGameObject()->getComponent<Transform>();
        movement = getGameObject()->getComponent<Movement>();

        if (movement == nullptr)
        {
            isStatic = true;
        }

    }

 
        bool Collider::getStatic() const{
            return isStatic;
        }
        bool BoxCollider::checkCollision(const CircleCollider *other) const
        {
            // Get box bounds
            float boxLeft = position.x - bounds.w / 2.0f;
            float boxRight = position.x + bounds.w / 2.0f;
            float boxTop = position.y - bounds.h / 2.0f;
            float boxBottom = position.y + bounds.h / 2.0f;

            // Find closest point on box to circle center
            float closestX = std::max(boxLeft, std::min(other->position.x, boxRight));
            float closestY = std::max(boxTop, std::min(other->position.y, boxBottom));

            // Calculate distance from circle center to closest point
            float deltaX = other->position.x - closestX;
            float deltaY = other->position.y - closestY;
            float distanceSquared = deltaX * deltaX + deltaY * deltaY;

            // Check if collision occurs
            return distanceSquared <= other->getRadius() * other->getRadius();
        }
        bool BoxCollider::checkCollision(const BoxCollider *other) const
        {
            // Get this box bounds
            float thisLeft = position.x - bounds.w / 2.0f;
            float thisRight = position.x + bounds.w / 2.0f;
            float thisTop = position.y - bounds.h / 2.0f;
            float thisBottom = position.y + bounds.h / 2.0f;

            // Get other box bounds
            float otherLeft = other->position.x - other->bounds.w / 2.0f;
            float otherRight = other->position.x + other->bounds.w / 2.0f;
            float otherTop = other->position.y - other->bounds.h / 2.0f;
            float otherBottom = other->position.y + other->bounds.h / 2.0f;

            // Check for overlap on both axes
            return (thisLeft < otherRight && thisRight > otherLeft &&
                thisTop < otherBottom && thisBottom > otherTop);
            
        }
        bool CircleCollider::checkCollision(const CircleCollider *other) const
        {
            float deltaX = other->position.x - position.x;
            float deltaY = other->position.y - position.y;
            float distanceSquared = deltaX * deltaX + deltaY * deltaY;
            float radiusSum = getRadius() + other->getRadius();
            return distanceSquared <= radiusSum * radiusSum;
        }
        bool CircleCollider::checkCollision(const BoxCollider *other) const
        {
            return other->checkCollision(this);
        }
        float CircleCollider::getRadius() const
        {
            return radius;
        }   

}