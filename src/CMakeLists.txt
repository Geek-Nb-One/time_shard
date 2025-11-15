cmake_minimum_required(VERSION 3.10)


add_executable(
    time_shard 

    main.cpp 
    app.cpp

    libraries/game_object/game_object.cpp
    libraries/game_object/base_component.cpp
    libraries/game_object/transform.cpp
    libraries/game_object/camera.cpp
    libraries/renderer/renderer.cpp
    libraries/renderer/resource_manager.cpp
    )


link_libraries(SDL3::SDL3 SDL3_image::SDL3_image glm)
include_directories(libraries ${CMAKE_SOURCE_DIR}/third_party)
    
target_precompile_headers(time_shard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pch.h)


add_subdirectory(libraries EXCLUDE_FROM_ALL)

target_compile_definitions(time_shard PRIVATE GLM_ENABLE_EXPERIMENTAL)
# Link libraries
target_link_libraries(time_shard PRIVATE  game_object state_machine scene managers imgui )






