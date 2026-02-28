#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Mesh.hpp"
#include "edge_detection.hpp"
#include "NeighborBuilder.hpp"

namespace py = pybind11;

PYBIND11_MODULE(meshlib, m)
{
    py::class_<RawMesh>(m, "RawMesh")
        .def(py::init<>());

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

    py::module_ topo = m.def_submodule("topology");
    topo.def("weld_vertices", &Topology::weld_vertices);
    topo.def("build_neighbors", &Topology::build_neighbors);
    topo.def("calculate_normals", &Topology::calculate_normals);
    topo.def("edge_detection", &Topology::edge_detection);
}