#pragma once

#include "base_component.h"

class RectangleCollider;

class ColliderComponent : public Component
{
public:
    ColliderComponent(const char *name) : Component(name) {}
    virtual bool checkCollision(RectangleCollider *other) = 0;
};

class RectangleCollider : public ColliderComponent
{
public:
    RectangleCollider(float width, float height);
    bool checkCollision(RectangleCollider *other) override;

    void setSize(float width, float height);

private:
    float width;
    float height;
};