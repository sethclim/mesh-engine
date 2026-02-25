#pragma once
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include "mesh.hpp"

class VTKAdapter
{
public:
    static vtkSmartPointer<vtkPolyData> convert(const RawMesh &mesh)
    {
        auto points = vtkSmartPointer<vtkPoints>::New();
        auto polys = vtkSmartPointer<vtkCellArray>::New();

        // Fill points
        for (const auto &v : mesh.vertices)
            points->InsertNextPoint(v.x, v.y, v.z);

        // Fill triangles
        for (const auto &f : mesh.faces)
        {
            auto tri = vtkSmartPointer<vtkTriangle>::New();
            tri->GetPointIds()->SetId(0, f.v[0]);
            tri->GetPointIds()->SetId(1, f.v[1]);
            tri->GetPointIds()->SetId(2, f.v[2]);
            polys->InsertNextCell(tri);
        }

        auto polydata = vtkSmartPointer<vtkPolyData>::New();
        polydata->SetPoints(points);
        polydata->SetPolys(polys);
        return polydata;
    }

    static vtkSmartPointer<vtkPolyData> convert(const Mesh &mesh)
    {
        auto points = vtkSmartPointer<vtkPoints>::New();
        auto polys = vtkSmartPointer<vtkCellArray>::New();

        // Fill points
        for (const auto &v : mesh.vertices)
            points->InsertNextPoint(v.pos.x, v.pos.y, v.pos.z);

        // Fill triangles
        for (const auto &f : mesh.faces)
        {
            auto tri = vtkSmartPointer<vtkTriangle>::New();
            tri->GetPointIds()->SetId(0, f.v[0]);
            tri->GetPointIds()->SetId(1, f.v[1]);
            tri->GetPointIds()->SetId(2, f.v[2]);
            polys->InsertNextCell(tri);
        }

        auto polydata = vtkSmartPointer<vtkPolyData>::New();
        polydata->SetPoints(points);
        polydata->SetPolys(polys);
        return polydata;
    }
};