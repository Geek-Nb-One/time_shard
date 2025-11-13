#include "game_object.h"

// Template implementation is now in the header file

void ts::GameObject::initComponent()
{
    for(const auto& [key, comp] : components) {
        comp->init();
    }
}
