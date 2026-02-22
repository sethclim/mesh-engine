#include <iostream>
#include "mesh.hpp"
#include "NeighborBuilder.hpp"
#include "Laplacian.hpp"

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

int main()
{
    Mesh mesh;

    int v0 = mesh.add_vertex({0, 0, 0});
    int v1 = mesh.add_vertex({1, 0, 0});
    int v2 = mesh.add_vertex({0, 1, 0});

    mesh.add_triangle(v0, v1, v2);

    int v3 = mesh.add_vertex({1, 1, 0});
    mesh.add_triangle(v1, v3, v2);

    std::cout << "Vertices: " << mesh.vertex_count() << "\n";
    std::cout << "Faces: " << mesh.face_count() << "\n";

    Topology::build_neighbors(mesh);

    for (size_t i = 0; i < mesh.vertex_count(); ++i)
    {
        std::cout << "Vertex " << i
                  << " len neighbors: "
                  << mesh.neighbors[i].size() << "\n";
        std::cout << "neighbors: \n";
        for (size_t j = 0; j < mesh.neighbors[i].size(); ++j)
        {
            std::cout << mesh.neighbors[i][j] << ", ";
        }
        std::cout << "\n";
    }

    double alpha = 0.1;
    auto lap = Algorithms::Laplacian(mesh);

    for (size_t i = 0; i < mesh.vertex_count(); ++i)
    {
        mesh.vertices[i].pos.x += alpha * lap[i].x;
        mesh.vertices[i].pos.y += alpha * lap[i].y;
        mesh.vertices[i].pos.z += alpha * lap[i].z;
    }

    // This creates a polygonal cylinder model with eight circumferential facets.
    //
    vtkCylinderSource *cylinder = vtkCylinderSource::New();
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes
    // are defined.
    //
    vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it -22.5 degrees.
    vtkActor *cylinderActor = vtkActor::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    // Create the graphics structure. The renderer renders into the
    // render window. The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    //
    vtkRenderer *ren1 = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

    // Add the actors to the renderer, set the background and size
    //
    ren1->AddActor(cylinderActor);
    ren1->SetBackground(0.1, 0.2, 0.4);
    renWin->SetSize(200, 200);

    // We'll zoom in a little by accessing the camera and invoking a "Zoom"
    // method on it.
    ren1->ResetCamera();
    ren1->GetActiveCamera()->Zoom(1.5);
    renWin->Render();

    // This starts the event loop and as a side effect causes an initial render.
    iren->Start();

    // Exiting from here, we have to delete all the instances that
    // have been created.
    cylinder->Delete();
    cylinderMapper->Delete();
    cylinderActor->Delete();
    ren1->Delete();
    renWin->Delete();
    iren->Delete();

    return 0;
}