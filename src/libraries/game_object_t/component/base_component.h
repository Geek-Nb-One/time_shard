#pragma once

#include "../pch.h"


class GameObject;
class Transform;


class Component
{

public:
    Component(const char *name);
    void assign(GameObject *gameObject);
    const char *getName() const;
    GameObject *getGameObject() const;

    Transform& getTransform() const;

    virtual ~Component() = default;

    // virtual void serialize() = 0;
    // virtual void deserialize() = 0;
private:
    const char *name;
    GameObject *gameObject;
};