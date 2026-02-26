#pragma once

// #include "vtkCylinderSource.h"
// #include "vtkPolyDataMapper.h"
// #include "vtkActor.h"
// #include "vtkRenderer.h"
// #include "vtkRenderWindow.h"
// #include "vtkRenderWindowInteractor.h"
// #include "vtkProperty.h"
// #include "vtkCamera.h"

// #include <vtkDoubleArray.h>
// #include <vtkPointData.h>
// #include <vtkPolyData.h>
// #include <vtkPoints.h>
// #include <vtkArrowSource.h>
// #include <vtkGlyph3D.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkActor.h>
// #include <vtkRenderer.h>
// #include <vtkSmartPointer.h>

// #include "vtk_adaptor.hpp"

#include "mesh_render_session.hpp"
#include "raw_mesh_render_session.hpp"
// class Viewer
// {
// public:
//     void render(const RawMesh &mesh);
//     void render(const Mesh &mesh);

//     Viewer &show_vertex_normals(
//         double scale = 0.4,
//         Vec3 color = {1.0, 1.0, 0.0});

// private:
//     void display_vertex_normals(const Mesh &mesh, vtkRenderer *renderer, double scale);
//     bool drawNormals = false;
//     double normalScale = 0.4;
//     Vec3 normalColor = {1.0, 1.0, 0.0};
// };

class Viewer
{
public:
    static MeshRenderSession render(const Mesh &mesh);
    static RawMeshRenderSession render(const RawMesh &mesh);
};