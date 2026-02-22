add_executable(mesh_core_test 
    mesh_core_test.cpp
    algorithmns_test.cpp)

target_link_libraries(mesh_core_test PRIVATE core)
target_link_libraries(mesh_core_test PRIVATE topology)
target_link_libraries(mesh_core_test PRIVATE algorithms)

target_link_libraries(mesh_core_test PRIVATE ${VTK_LIBRARIES})

add_custom_command(TARGET mesh_core_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${VCPKG_INSTALLED_DIR}/x64-windows/bin
    $<TARGET_FILE_DIR:mesh_core_test>)

vtk_module_autoinit(
  TARGETS mesh_core_test
  MODULES ${VTK_LIBRARIES}
)