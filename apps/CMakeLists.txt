add_executable(mesh_core_test 
    mesh_core_test.cpp
    algorithmns_test.cpp)

target_link_libraries(mesh_core_test PRIVATE core)
target_link_libraries(mesh_core_test PRIVATE topology)
target_link_libraries(mesh_core_test PRIVATE algorithms)
