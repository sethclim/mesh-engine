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

class RawMeshRenderSession : public BaseRenderSession<RawMeshRenderSession>
{
public:
    RawMeshRenderSession(const RawMesh &mesh);

    // RawMeshRenderSession &show_vertex_normals(
    //     double scale = 0.4,
    //     const Vec3 &color = {1, 1, 0});

    void run();

private:
    const RawMesh &mesh;

    // bool draw_normals = false;
    // double normal_scale = 0.4;
    // Vec3 normal_color = {1, 1, 0};
};