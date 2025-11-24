#pragma once

#include "base_component.h"
#include "movement.h"
namespace ts
{

    struct Box
    {
        float topLeft;
        float topRight;
        float bottomLeft;
        float bottomRight;
    };

    struct Circle
    {
        glm::vec2 center;
        float radius;
    };

    class ColliderShape
    {
    public:
        ColliderShape(Transform *transform) : transform(transform) {}
        virtual bool checkCollisionBox(const Box &box) = 0;
        virtual bool checkCollisionCircle(const Circle &circle) = 0;
        virtual bool checkCollision(ColliderShape *other) = 0;

        glm::vec3 getPosition() const;

        bool checkBoxVsBox(const Box &boxA, const Box &boxB) const;

        bool checkBoxVsCircle(const Box &box, const Circle &circle) const;

        bool checkCircleVsCircle(const Circle &circleA, const Circle &circleB) const;

    private:
        Transform *transform = nullptr;
    };

    class ColliderShapeBox : public ColliderShape
    {
    public:
        ColliderShapeBox(Transform *transform, const SDL_FRect &bounds) : ColliderShape(transform), bounds(bounds) {}
        bool checkCollisionBox(const Box &box) override;
        bool checkCollisionCircle(const Circle &circle) override;
        bool checkCollision(ColliderShape *other) override;

    private:
        SDL_FRect bounds;

        Box getBox() const;
    };

    class ColliderShapeCircle : public ColliderShape
    {
    public:
        ColliderShapeCircle(Transform *transform, const float radius) : ColliderShape(transform), radius(radius) {}
        bool checkCollisionBox(const Box &box) override;
        bool checkCollisionCircle(const Circle &circle) override;
        bool checkCollision(ColliderShape *other) override;

    private:
        float radius;
        Circle getCircle() const;
    };

    class Collider : public Component
    {
    public:
        void init() override;
        bool isStatic() const;

        void setShapeBox(const SDL_FRect &bounds);
        void setShapeCircle(const float radius);

        UpdatePriority getPriority() const override { return IGNORE; }

        bool isCollidingWith(Collider *other);

        void moveBack();

    private:
        bool _isStatic = false;
        ColliderShape *shape = nullptr;
        Movement *movement = nullptr;
        Transform *transform = nullptr;
    };
}