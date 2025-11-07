cmake_minimum_required(VERSION 3.10)


add_executable(time_shard 
main.cpp 
app.cpp
window.cpp
control_manager.cpp
map.cpp
libraries/state_machine/state_machine.cpp
libraries/state_machine/state.cpp
libraries/state_machine/test_state.cpp
)


target_precompile_headers(time_shard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pch.h)


add_subdirectory(libraries EXCLUDE_FROM_ALL)

target_compile_definitions(time_shard PRIVATE GLM_ENABLE_EXPERIMENTAL)
# Link libraries
target_link_libraries(time_shard PRIVATE SDL3::SDL3 SDL3_image::SDL3_image glm game_object)
target_include_directories(time_shard PRIVATE libraries)


# Set up precompiled headers




