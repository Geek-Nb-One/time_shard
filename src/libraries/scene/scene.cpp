#include "scene.h"

namespace ts
{

    void Scene::render(Renderer *renderer)
    {
        if (mainCamera == nullptr)
        {
            throw std::runtime_error("Main camera is not set for the scene");
        }

        renderer->setCamera(
            mainCamera->getComponent<Camera>()->getScreenPosition(),
            mainCamera->getComponent<Camera>()->getWidth(),
            mainCamera->getComponent<Camera>()->getHeight());

        for (const auto &[id, object] : objects)
        {
            addObjectToRender(renderer, object, glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }

    void Scene::update(float deltaTime)
    {

        for (const auto &[id, object] : objects)
        {
            object->update(deltaTime);
        }
    }

    int Scene::addGameObject(GameObject *object)
    {
        int objID = nextID++;
        objects[objID] = object;
        return objID;
    }

    GameObject *Scene::getGameObject(int id) const
    {
        auto it = objects.find(id);
        if (it != objects.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void Scene::setMainCamera(GameObject *camera)
    {
        if(!camera->hasComponent<Camera>()){
            throw std::runtime_error("GameObject does not have a Camera component");
        }
        mainCamera = camera;
    }

    GameObject* Scene::createCamera()
    {
        GameObject *camera = new GameObject();
        camera->addComponent<Transform>();
        auto c = camera->addComponent<Camera>();
        camera->addComponent<CameraTracker>();
        addGameObject(camera);
        setMainCamera(camera);
        camera->init();
        c->setDimension(Config::LOGICAL_WIDTH, Config::LOGICAL_HEIGHT);

        return camera;

    }
    void Scene::addObjectToRender(Renderer* renderer,const GameObject * object, glm::vec3 base_position)
    {
        auto transform = object->getComponent<Transform>();
        auto sprite = object->getComponent<SpriteTexture>();

        glm::vec3 position = base_position + transform->position;

        for(auto & child  : object->getChildren()){
            addObjectToRender(renderer,child.get(),position);
        }

        if (sprite && transform)
        {
            renderer->addTextureRenderObject(
                sprite->getTexture(),
                sprite->getSourceRect(),
                sprite->getDestinationRect(),
                position);
        }
        auto sprite_color = object->getComponent<SpriteColor>();
        if (sprite_color && transform)
        {
           
            renderer->addRectangleRenderObject(
                sprite_color->getRect(),
                sprite_color->getColor(),
                position, 
                sprite_color->isFilled());
        }
    }
}