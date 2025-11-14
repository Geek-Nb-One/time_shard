#pragma once

#include "../../pch.h"

namespace ts
{
    class GameObject;

    class Component
    {

    public:
        void assign(GameObject *gameObject);
        virtual void init()=0;
        virtual void update(float deltaTime)=0;
        virtual void destroy()=0;

        GameObject * getGameObject() const;

    private:
        GameObject *gameObject;
    };

}


#include "game_object.h"