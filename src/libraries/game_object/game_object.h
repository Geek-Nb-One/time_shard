#pragma once

#include "pch.h"

struct Transform
{
    glm::vec3 position;
};

class GameObject
{

public:
    Transform& getTransform() { return transform; }

    const Transform& getTransform() const { return transform; }

    void move(float deltaX, float deltaY, float deltaZ = 0.0f)
    {
        move(glm::vec3(deltaX, deltaY, deltaZ));
    }

    void move(const glm::vec3& delta)
    {
        transform.position += delta;
    }

private:
    Transform transform;
};