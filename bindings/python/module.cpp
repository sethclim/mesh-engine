#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Mesh.hpp"
#include "edge_detection.hpp"
#include "NeighborBuilder.hpp"

#include "mesh_render_session.hpp"
#include "raw_mesh_render_session.hpp"
#include "viewer.hpp"

namespace py = pybind11;

PYBIND11_MODULE(meshlib, m)
{
    py::class_<Vec3>(m, "Vec3")
        .def(py::init<double, double, double>())
        .def_readwrite("x", &Vec3::x)
        .def_readwrite("y", &Vec3::y)
        .def_readwrite("z", &Vec3::z);

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

    py::class_<MeshRenderSession>(m, "MeshRenderSession")
        .def("color",
             &MeshRenderSession::color,
             py::return_value_policy::reference_internal)

        .def("background_color",
             &MeshRenderSession::background_color,
             py::return_value_policy::reference_internal)

        .def("show_vertex_normals",
             &MeshRenderSession::show_vertex_normals,
             py::return_value_policy::reference_internal,
             py::arg("scale") = 0.4,
             py::arg("color") = Vec3{0.2588, 0.5294, 0.9608})

        .def("smooth_shading",
             &MeshRenderSession::smooth_shading,
             py::return_value_policy::reference_internal)

        .def("show_edges",
             &MeshRenderSession::show_edges,
             py::return_value_policy::reference_internal)

        .def("run", &MeshRenderSession::run);

    py::class_<RawMeshRenderSession>(m, "RawMeshRenderSession")
        .def("color",
             &RawMeshRenderSession::color,
             py::return_value_policy::reference_internal)

        .def("background_color",
             &RawMeshRenderSession::background_color,
             py::return_value_policy::reference_internal)

        .def("run", &RawMeshRenderSession::run);

    py::class_<Viewer>(m, "Viewer")
        .def_static("render",
                    py::overload_cast<const Mesh &>(&Viewer::render))

        .def_static("render",
                    py::overload_cast<const RawMesh &>(&Viewer::render));
}