add_library(
    algorithms
    Laplacian.hpp
    Laplacian.cpp
)

target_include_directories(algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(algorithms PRIVATE core)