add_library(scene STATIC
    scene.cpp
    map.cpp
    map.h
    test_scene.cpp
)

target_precompile_headers(scene PRIVATE pch.h)


target_link_libraries(scene PRIVATE game_object managers)


