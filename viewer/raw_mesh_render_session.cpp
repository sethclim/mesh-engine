#include "raw_mesh_render_session.hpp"

RawMeshRenderSession::RawMeshRenderSession(const RawMesh &mesh) : mesh(mesh) {};

RawMeshRenderSession &RawMeshRenderSession::show_vertex_normals(
    double scale,
    const Vec3 &color)
{
    draw_normals = true;
    normal_scale = scale;
    normal_color = color;
    return *this;
}

void RawMeshRenderSession::run()
{
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    window->AddRenderer(renderer);
    interactor->SetRenderWindow(window);

    // Convert mesh → polydata
    auto polyData = VTKAdapter::convert(mesh);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);

    window->Render();
    interactor->Start();
}