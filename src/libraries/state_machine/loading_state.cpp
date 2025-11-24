#include "loading_state.h"

namespace ts
{
    LoadingState::LoadingState(Scene *scene, Renderer* renderer) : scene(scene), renderer(renderer)
    {
    }
    void LoadingState::enter()
    {
        scene->load(renderer);
    }
    void LoadingState::update(float deltaTime)
    {
    }
    void LoadingState::render()
    {
        SDL_Color bgColor = {0, 0, 0, 255};
        renderer->newFrame();
        renderer->present();

    }
    void LoadingState::exit()
    {
    }
}
