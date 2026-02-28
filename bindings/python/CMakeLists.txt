find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(meshlib module.cpp)

target_link_libraries(meshlib
    PRIVATE
    core
    topology
    pybind11::headers
)