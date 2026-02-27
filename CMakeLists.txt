cmake_minimum_required(VERSION 3.12...3.29)

project(MeshEngine VERSION 0.0.1)

find_package(VTK  
    COMPONENTS
        CommonColor
        CommonCore
        FiltersSources
        InteractionStyle
        RenderingContextOpenGL2
        RenderingCore
        RenderingFreeType
        RenderingGL2PSOpenGL2
        RenderingOpenGL2
    CONFIG REQUIRED)

add_subdirectory(core)
add_subdirectory(topology)
add_subdirectory(algorithms)
add_subdirectory(viewer)
add_subdirectory(bindings/python)

add_subdirectory(apps)

target_compile_features(core PRIVATE cxx_std_17)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB ASSETS "${CMAKE_SOURCE_DIR}/assets/*")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR}/assets)
