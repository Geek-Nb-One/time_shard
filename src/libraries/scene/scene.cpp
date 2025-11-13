#include "scene.h"


void Scene::render()
{
    gameManager.renderer().setCamera(mainCamera->getTransform().position);
    map.render(mainCamera);

    for (auto obj : objects)
    {
        gameManager.renderer().renderGameObject(obj);
    }
}

void Scene::update(float deltaTime)
{
     

    // player->setDirection(
    //     static_cast<float>(input->getHorizontalDirection()),
    //     static_cast<float>(input->getVerticalDirection()));

    // player->update(deltaTime);

    // if (input->isActive(ControlAction::CAMERA_ATTACH_TOGGLE))
    // {
    //     trackPlayer = !trackPlayer;
    //     if (trackPlayer)
    //     {
    //         cameraTracker.trackObject(player);
    //     }
    //     else
    //     {
    //         cameraTracker.trackObject(nullptr);
    //     }
    // }
    // cameraTracker.update(deltaTime);
}
