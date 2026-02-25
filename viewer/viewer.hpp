#pragma once

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

#include "vtk_adaptor.hpp"

class Viewer
{
public:
    void render(const RawMesh &mesh);
    void render(const Mesh &mesh);
};