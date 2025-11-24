#include "event_manager.h"

namespace ts{
    // This is the DEFINITION
    EventManager* EventManager::instance = nullptr;

    EventManager* EventManager::getInstance(){
        if(instance == nullptr){
            instance = new EventManager();
        }
        return instance;
    }

    void EventManager::clear(){
        listeners.clear();
    }
}