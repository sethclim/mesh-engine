#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Mesh.hpp"

namespace py = pybind11;

PYBIND11_MODULE(meshlib, m)
{
    py::class_<Mesh>(m, "Mesh")
        .def(py::init<>())
        .def("add_vertex", &Mesh::add_vertex)
        .def("add_triangle", &Mesh::add_triangle)
        .def("vertex_count", &Mesh::vertex_count)
        .def("face_count", &Mesh::face_count)

        .def_property(
            "has_normals",
            &Mesh::has_normals,
            &Mesh::set_has_normals)
        .def_property(
            "has_edges",
            &Mesh::has_edges,
            &Mesh::set_has_edges);
}