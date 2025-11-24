#pragma once

#include "pch.h"

namespace ts{

    struct ChangeSceneEvent{
        std::string newSceneName;
    };

    class EventManager{
    public:
        static EventManager* getInstance();

        template <typename T>
        void subscribe(std::function<void(const T&)> callback){
              std::type_index eventType = std::type_index(typeid(T));
            
            // Wrap the typed callback in a generic function
            auto wrapper = [callback](const void* eventPtr) {
                const T* typedEvent = static_cast<const T*>(eventPtr);
                callback(*typedEvent);
            };
            
            listeners[eventType].push_back(wrapper);
        }

        template <typename T>
        void emit(T event){
            std::type_index eventType = std::type_index(typeid(T));
            
            if(listeners.find(eventType) != listeners.end()){
                for(auto& callback : listeners[eventType]){
                    callback(&event);
                }
            }
        }

        void clear();

    private:
        EventManager() = default;
        static EventManager* instance;

        std::unordered_map<std::type_index, std::vector<std::function<void(const void *)>>> listeners;
    };
}