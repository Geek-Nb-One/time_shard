add_library(game_object STATIC
    camera.cpp
    player.cpp
    component/base_component.cpp
    component/collider.cpp
    component/sprite_component.cpp
    component/camera_tracker.cpp

    )



target_precompile_headers(game_object PRIVATE pch.h)

target_link_libraries(game_object PRIVATE managers)