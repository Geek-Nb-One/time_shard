add_library(managers STATIC
input_manager.cpp

)


target_precompile_headers(managers PRIVATE pch.h)

target_link_directories(managers PRIVATE imgui)
