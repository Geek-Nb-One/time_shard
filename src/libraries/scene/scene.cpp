#include "scene.h"

namespace ts
{

    void Scene::render(Renderer &renderer)
    {
        if (mainCamera == nullptr)
        {
            throw std::runtime_error("Main camera is not set for the scene");
        }

        renderer.setCamera(
            mainCamera->getComponent<Camera>()->getScreenPosition(),
            mainCamera->getComponent<Camera>()->getWidth(),
            mainCamera->getComponent<Camera>()->getHeight());

        for (const auto &[id, object] : objects)
        {
            Console::logFrame("Rendering object ID: " + std::to_string(id));
            auto transform = object->getComponent<Transform>();
            auto sprite = object->getComponent<Sprite>();

            if (sprite && transform)
            {
                renderer.addTextureRenderObject(
                    sprite->getTexture(),
                    sprite->getSourceRect(),
                    sprite->getDestinationRect(),
                    transform->position);
            }
            auto border = object->getComponent<Border>();
            if (border && transform)
            {
                Console::logFrame("Rendering border for object ID: " + std::to_string(id));
                renderer.addRectangleRenderObject(
                    border->getRect(),
                    border->getColor(),
                    transform->position);
            }
        }
    }

    void Scene::update(float deltaTime)
    {

        for (const auto &[id, object] : objects)
        {
            object->update(deltaTime);
        }
    }
}