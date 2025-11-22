#include "collider.h"

namespace ts
{
    // ColliderShape implementations
    glm::vec3 ColliderShape::getPosition() const
    {
        return transform->position;
    }

    bool ColliderShape::checkBoxVsBox(const Box &boxA, const Box &boxB) const
    {
        // Check for overlap on both axes
        return (boxA.topLeft < boxB.bottomRight && boxA.topRight > boxB.bottomLeft &&
                boxA.bottomLeft < boxB.topRight && boxA.bottomRight > boxB.topLeft);
    }

    bool ColliderShape::checkBoxVsCircle(const Box &box, const Circle &circle) const
    {
        // Find closest point on box to circle center
        float closestX = std::max(box.topLeft, std::min(circle.center.x, box.topRight));
        float closestY = std::max(box.bottomLeft, std::min(circle.center.y, box.bottomRight));
        // Calculate distance from circle center to closest point
        float deltaX = circle.center.x - closestX;
        float deltaY = circle.center.y - closestY;
        float distanceSquared = deltaX * deltaX + deltaY * deltaY;
        return distanceSquared <= circle.radius * circle.radius;
    }

    bool ColliderShape::checkCircleVsCircle(const Circle &circleA, const Circle &circleB) const
    {
        return (circleA.radius + circleB.radius) * (circleA.radius + circleB.radius) >=
               (circleA.center.x - circleB.center.x) * (circleA.center.x - circleB.center.x) +
                   (circleA.center.y - circleB.center.y) * (circleA.center.y - circleB.center.y);
    }

    // ColliderShapeBox implementations
    bool ColliderShapeBox::checkCollisionBox(const Box &box)
    {
        Box thisBox = getBox();
        return checkBoxVsBox(thisBox, box);
    }

    bool ColliderShapeBox::checkCollisionCircle(const Circle &circle)
    {
        return checkBoxVsCircle(getBox(), circle);
    }

    bool ColliderShapeBox::checkCollision(ColliderShape *other)
    {
        return other->checkCollisionBox(getBox());
    }

    Box ColliderShapeBox::getBox() const
    {
        auto position = getPosition();
        // Get this box bounds
        float thisLeft = position.x - bounds.w / 2.0f;
        float thisRight = position.x + bounds.w / 2.0f;
        float thisTop = position.y - bounds.h / 2.0f;
        float thisBottom = position.y + bounds.h / 2.0f;

        return Box{thisLeft, thisRight, thisTop, thisBottom};
    }

    // ColliderShapeCircle implementations
    bool ColliderShapeCircle::checkCollisionBox(const Box &box)
    {
        Circle thisCircle = getCircle();
        return checkBoxVsCircle(box, thisCircle);
    }

    bool ColliderShapeCircle::checkCollisionCircle(const Circle &circle)
    {
        Circle thisCircle = getCircle();
        return checkCircleVsCircle(thisCircle, circle);
    }

    bool ColliderShapeCircle::checkCollision(ColliderShape *other)
    {
        Circle thisCircle = getCircle();
        return other->checkCollisionCircle(thisCircle);
    }

    Circle ColliderShapeCircle::getCircle() const
    {
        return Circle{glm::vec2(getPosition().x, getPosition().y), radius};
    }

    // Collider implementations
    void Collider::init()
    {
        transform = getGameObject()->getComponent<Transform>();
        movement = getGameObject()->getComponent<Movement>();

        if (movement == nullptr)
        {
            _isStatic = true;
        }
    }

    bool Collider::isStatic() const
    {
        return _isStatic;
    }

    void Collider::setShapeBox(const SDL_FRect &bounds)
    {
        shape = new ColliderShapeBox(transform, bounds);
    }

    void Collider::setShapeCircle(const float radius)
    {
        shape = new ColliderShapeCircle(transform, radius);
    }

    bool Collider::isCollidingWith(Collider *other)
    {
        if (shape != nullptr && other->shape != nullptr)
        {
            return shape->checkCollision(other->shape);
        }
        return false;
    }
}