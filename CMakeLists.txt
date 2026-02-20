cmake_minimum_required(VERSION 3.12...3.29)

project(MeshEngine VERSION 0.0.1)

add_subdirectory(core)
add_subdirectory(apps)

target_compile_features(core PRIVATE cxx_std_17)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)