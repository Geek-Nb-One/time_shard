#include "game_object.h"

// Template implementation is now in the header file

void ts::GameObject::init()
{
    for(const auto& [key, comp] : components) {
        comp->init();
    }
}


void ts::GameObject::destroy()
{
    for(const auto& [key, comp] : components) {
        comp->destroy();
    }
}