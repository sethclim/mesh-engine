add_library(
    algorithms
    smoothing.cpp
)

target_include_directories(algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})