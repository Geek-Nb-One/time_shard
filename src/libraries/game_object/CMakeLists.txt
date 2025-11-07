add_library(game_object STATIC
camera.cpp
camera.h
camera_tracker.cpp
camera_tracker.h
game_object.h
)

target_link_libraries(game_object PRIVATE SDL3::SDL3 SDL3_image::SDL3_image glm)

target_precompile_headers(game_object PRIVATE pch.h)
