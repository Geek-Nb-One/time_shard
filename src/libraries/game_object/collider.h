#pragma once

#include "base_component.h"
#include "movement.h"
namespace ts
{

    class Collider : public ts::Component
    {
    public:

        virtual float getRadius() const = 0;

        void init() override;

        bool getStatic() const;

        glm::vec2 position;

        UpdatePriority getPriority() const override { return REGULAR; }

    private:
        bool isStatic = false;
        Movement* movement = nullptr;
        Transform* transform = nullptr;
    };

    class CircleCollider;

    class BoxCollider : public Collider
    {
    public:
        BoxCollider(const SDL_FRect &bounds) : bounds(bounds) {}
        bool checkCollision(const CircleCollider *other) const;
        bool checkCollision(const BoxCollider *other) const;
        float getRadius() const override
        {
            return sqrt(bounds.w * bounds.w + bounds.h * bounds.h) / 2.0f;
        }

    private:
        SDL_FRect bounds;
    };

    class CircleCollider : public Collider
    {
    public:
        bool checkCollision(const CircleCollider *other) const;
        bool checkCollision(const BoxCollider *other) const;

        float getRadius() const override;
    private:
        float radius;
    };
}