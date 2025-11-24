#pragma once

#include "state_machine.h"
#include "movement.h"
#include "animator.h"
#include "player_controller.h"


namespace ts
{

    enum class PlayerState
    {
        IDLE,
        WALKING
    };


    class PlayerStateMachine : public StateMachine<PlayerState>
    {

        public:
            PlayerStateMachine() : StateMachine<PlayerState>(PlayerState::IDLE) {}

            void init() override;

        private:
            Movement* movement = nullptr;
            Animator * animator = nullptr;
            PlayerController* controller = nullptr;

            void updateIdle(float deltaTime);
            void updateWalking(float deltaTime);

            void startIdle();
            void startWalking();
        
            void endIdle();
            void endWalking();

            void onStateEnter(PlayerState state) override;
            void onStateExit(PlayerState state) override ;

            Direction playerDirection= Direction::DOWN;

    };
}