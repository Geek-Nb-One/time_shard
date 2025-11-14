#pragma once

#include "pch.h"
#include <game_object/game_object.h>
#include <renderer/renderer.h>
#include <game_object/component.h>

namespace ts
{
    class Scene
    {

    public:
        void render(Renderer &renderer);
        void update(float deltaTime);
        virtual void load() = 0;
        virtual void unload() = 0;

        int addGameObject(GameObject *object)
        {
            int objID = nextID++;
            objects[objID] = object;
            return objID;
        }

        GameObject *getGameObject(int id) const
        {
            auto it = objects.find(id);
            if (it != objects.end())
            {
                return it->second;
            }
            return nullptr;
        }

        void setMainCamera(GameObject *camera)
        {
            if(!camera->hasComponent<Camera>()){
                throw std::runtime_error("GameObject does not have a Camera component");
            }
            mainCamera = camera;
        }

    private:
        std::unordered_map<int, GameObject *> objects;
        GameObject *mainCamera = nullptr;

        int nextID = 0;
    };
}