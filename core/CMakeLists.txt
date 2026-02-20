add_library(
    core
    Mesh.hpp
    Mesh.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})