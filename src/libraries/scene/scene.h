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
        void render(Renderer *renderer);
        void update(float deltaTime);
        virtual void load(Renderer *renderer) = 0;
        virtual void unload() = 0;

        int addGameObject(GameObject *object);
        GameObject *getGameObject(int id) const;
        void setMainCamera(GameObject *camera);
        GameObject* createCamera();

    private:
        std::unordered_map<int, GameObject *> objects;
        GameObject *mainCamera = nullptr;

        int nextID = 0;

        void addObjectToRender(Renderer* renderer,const GameObject * object, glm::vec3 position);
    };
}