#pragma once

#include "../../pch.h"

namespace ts
{
    class GameObject;

    enum UpdatePriority{
        INPUT = 100,
        MOVEMENT = 200,
        REGULAR = 300,
        CAMERA = 400,
        RENDER = 500
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