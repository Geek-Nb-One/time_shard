#include "state_machine_player.h"

namespace ts
{
    void StateMachinePlayer::init()
    {

        movement = getGameObject()->getComponent<Movement>();
        animator = getGameObject()->getComponent<Animator>();
        controller = getGameObject()->getComponent<PlayerController>();
        // Define states
        addState(PlayerState::IDLE, [this](float deltaTime)
                 { updateIdle(deltaTime); });

        addState(PlayerState::WALKING, [this](float deltaTime)
                 {
                     // Walking-specific logic
                     updateWalking(deltaTime); });

        // Define transitions
        addTransition(PlayerState::IDLE, PlayerState::WALKING, [this]()
                      { return movement && movement->isMoving(); });

        addTransition(PlayerState::WALKING, PlayerState::IDLE, [this]()
                      { return movement && !movement->isMoving(); });

        addTransitionAction(PlayerState::IDLE, PlayerState::WALKING, [this]()
                            {

                                // Action on entering WALKING state
                                Console::logFrame("Transitioning to WALKING state"); });
        addTransitionAction(PlayerState::WALKING, PlayerState::IDLE, [this]()
                            {
                                // Action on entering IDLE state
                                Console::logFrame("Transitioning to IDLE state"); });

        // Set initial state
        changeState(PlayerState::IDLE);
    }
    void StateMachinePlayer::updateIdle(float deltaTime)
    {
    }
    void StateMachinePlayer::updateWalking(float deltaTime)
    {
        auto checkDirection = movement->getDirection();
        if(checkDirection != playerDirection)
        {
            playerDirection = checkDirection;
            startWalking();
        }
    }
    void StateMachinePlayer::startIdle()
    {

        animator->playAnimation("idle", true);

    }
    void StateMachinePlayer::startWalking()
    {
        switch(playerDirection)
        {
            case LEFT:
                animator->playAnimation("walk_left", true);
                break;
            case RIGHT:
                animator->playAnimation("walk_right", true);
                break;
            case UP:
                animator->playAnimation("walk_up", true);
                break;
            case DOWN:
                animator->playAnimation("walk_down", true);
                break;
            default:
                animator->playAnimation("walk", true);
                break;
        }

    }
   

    void StateMachinePlayer::endIdle()
    {
    }
    void StateMachinePlayer::endWalking()
    {
    }
    void StateMachinePlayer::onStateEnter(PlayerState state)
    {
        switch (state)
        {
        case PlayerState::IDLE:
            startIdle();
            break;
        case PlayerState::WALKING:
            startWalking();
            break;
        }
    }
    void StateMachinePlayer::onStateExit(PlayerState state)
    {
        switch (state)
        {
        case PlayerState::IDLE:
            endIdle();
            break;
        case PlayerState::WALKING:
            endWalking();
            break;
        }
    }
}