#include "state_machine.h"

#include "scene_state.h"

#include <managers/event_manager.h>

#include <scene/test_scene.h>
#include <scene/start_scene.h>

namespace ts
{

    void StateMachine::init(ts::Renderer *renderer)
    {
        this->renderer = renderer;

        addState<SceneState>("test_scene",new TestScene(), renderer);
        addState<SceneState>("start_scene", new StartScene(), renderer);

        EventManager::getInstance()->subscribe<ChangeSceneEvent>([this](const ChangeSceneEvent& event) {
            this->changeState(event.newSceneName);
        });
        changeState("start_scene");
    }

    void StateMachine::changeState(const std::string &name)
    {
        auto it = states.find(name);
        if (it != states.end())
        {
            nextState = std::move(it->second);
            Console::log("Changing state to: " + name);
        }
    }

    void StateMachine::update(float deltaTime)
    {
        // Handle state transitions
        if (nextState)
        {

            if (currentState)
            {
                currentState->exit();
            }
            currentState = std::move(nextState);
            currentState->enter();
            nextState.reset();
        }

        // Update current state
        if (currentState)
        {
            currentState->update(deltaTime);
        }
    }

    void StateMachine::render()
    {

        if (currentState)
        {

            currentState->render();
        }
    }

    void StateMachine::handleEvent(const SDL_Event *event)
    {
        if (currentState)
        {
            currentState->handleEvent(event);
        }
    }

    void StateMachine::destroy()
    {
    }
}