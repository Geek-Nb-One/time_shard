add_library(state_machine STATIC
    state_machine.cpp
    state.cpp
    scene_state.cpp
    loading_state.cpp
)

target_link_libraries(state_machine PRIVATE game_object scene managers)