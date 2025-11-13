#pragma once

#include "pch.h"
#include <game_object/game_object.h>

class Scene
{

public:
    void render();
    void update(float deltaTime);
    virtual load() = 0;
    virtual unload() = 0;

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

    void setMainCamera(Camera *cam)
    {
        mainCamera = cam;
    }

private:
    std::unordered_map<int, GameObject *> objects;
    Camera *mainCamera = nullptr;

    int nextID = 0;
};