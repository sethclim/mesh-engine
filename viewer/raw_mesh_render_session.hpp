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

    void run();

private:
    const RawMesh &mesh;
};