#pragma once

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include "vtk_adaptor.hpp"

#include "Mesh.hpp"
#include "base_render_session.hpp"

class MeshRenderSession : public BaseRenderSession<MeshRenderSession>
{
public:
    MeshRenderSession(const Mesh &mesh);

    MeshRenderSession &show_vertex_normals(
        double scale = 0.4,
        const Vec3 &color = {1, 1, 0});

    MeshRenderSession &smooth_shading();
    // MeshRenderSession &color(Vec3 color);
    // MeshRenderSession &background_color(Vec3 color);

    void run();

private:
    void display_vertex_normals(const Mesh &mesh, vtkDataArray *normals, vtkRenderer *renderer, double scale = 0.4);

private:
    const Mesh &mesh;

    bool draw_normals = false;
    double normal_scale = 0.4;
    Vec3 normal_color = {1, 1, 0};

    bool smoothShading = false;
    // Vec3 meshColor = {1.0, 0.5, 0.3};
    // Vec3 backgroundColor = {0.1, 0.2, 0.4};
};
