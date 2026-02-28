add_library(
    topology
    NeighborBuilder.hpp
    NeighborBuilder.cpp
)

target_include_directories(topology PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(topology PRIVATE core)