add_library(managers STATIC
render_manager.cpp
input_manager.cpp
game_manager.cpp
)


target_precompile_headers(managers PRIVATE pch.h)

target_link_directories(managers PRIVATE imgui)
