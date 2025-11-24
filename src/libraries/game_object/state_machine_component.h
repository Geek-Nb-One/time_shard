#pragma once

#include "base_component.h"
#include <unordered_map>
#include <functional>

namespace ts
{
    // Hash function for std::pair to use in unordered_map
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const {
            auto h1 = std::hash<T1>{}(pair.first);
            auto h2 = std::hash<T2>{}(pair.second);
            return h1 ^ (h2 << 1);
        }
    };

    template <typename StateType>
    class StateMachineComponent : public Component
    {
    public:
        StateMachineComponent(StateType initialState) : currentState(initialState) {}

        void addState(StateType state, std::function<void(float)> updateFunction) {
            stateUpdates[state] = updateFunction;
        }

        void addTransition(StateType fromState, StateType toState, std::function<bool()> conditionFunction) {
            transitionConditions[{fromState, toState}] = conditionFunction;
        }

        void addTransitionAction(StateType fromState, StateType toState, std::function<void()> actionFunction) {
            transitionActions[{fromState, toState}] = actionFunction;
        }

        void changeState(StateType newState) {
            Console::log("Changing state from " + std::to_string(static_cast<int>(currentState)) + " to " + std::to_string(static_cast<int>(newState)));
            if (newState != currentState) {
                onStateExit(currentState);
                
                // Execute transition action if exists
                auto actionKey = std::make_pair(currentState, newState);
                if (transitionActions.find(actionKey) != transitionActions.end()) {
                    transitionActions[actionKey]();
                }
                
                currentState = newState;
                onStateEnter(currentState);
            }
        }

        StateType getCurrentState() const {
            return currentState;
        }

        
        void update(float deltaTime) override {
            // Check for automatic transitions
            for (const auto& [transition, condition] : transitionConditions) {
                if (transition.first == currentState && condition()) {
                    changeState(transition.second);
                    break; // Only one transition per frame
                }
            }
            
            // Update current state
            if (stateUpdates.find(currentState) != stateUpdates.end()) {
                stateUpdates[currentState](deltaTime);
            }
        }
        

        UpdatePriority getPriority() const override { return REGULAR; }
        
    protected:
        virtual void onStateEnter(StateType state) {}
        virtual void onStateExit(StateType state) {}
        
    private:
        StateType currentState;
        std::unordered_map<StateType, std::function<void(float)>> stateUpdates;
        std::unordered_map<std::pair<StateType, StateType>, std::function<void()>, PairHash> transitionActions;
        std::unordered_map<std::pair<StateType, StateType>, std::function<bool()>, PairHash> transitionConditions;
    };

}