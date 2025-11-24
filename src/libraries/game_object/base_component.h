#pragma once

#include "../../pch.h"

namespace ts
{
    class GameObject;

    enum UpdatePriority{
        IGNORE = 0,
        INPUT = 100,
        MOVEMENT = 200,
        REGULAR = 300,
        ANIMATION = 400,
        CAMERA = 500,
        RENDER = 600
    };

    class Component
    {

    public:
        void assign(GameObject *gameObject);
        virtual void init(){};
        virtual void update(float deltaTime){};
        virtual void destroy(){};

        virtual UpdatePriority getPriority() const = 0;

        GameObject * getGameObject() const;

    private:
        GameObject *gameObject;
    };

}


#include "game_object.h"