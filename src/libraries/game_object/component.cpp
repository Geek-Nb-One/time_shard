#include "component.h"



void ts::Component::assign(GameObject *gameObject){
    this->gameObject = gameObject;
}

ts::GameObject * ts::Component::getGameObject() const {
    return gameObject;
}
