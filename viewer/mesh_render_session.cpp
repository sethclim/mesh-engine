#include "mesh_render_session.hpp"

MeshRenderSession::MeshRenderSession(const Mesh &mesh) : mesh(mesh) {};

MeshRenderSession &MeshRenderSession::show_vertex_normals(
    double scale,
    const Vec3 &color)
{
    draw_normals = true;
    normal_scale = scale;
    normal_color = color;
    return *this;
}

void MeshRenderSession::run()
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

    if (draw_normals)
    {
        display_vertex_normals(mesh, renderer, 4);
    }

    window->Render();
    interactor->Start();
}

void MeshRenderSession::display_vertex_normals(const Mesh &mesh, vtkRenderer *renderer, double scale)
{
    auto points = vtkSmartPointer<vtkPoints>::New();
    auto normals = vtkSmartPointer<vtkDoubleArray>::New();
    normals->SetNumberOfComponents(3);
    normals->SetName("Normals");

    for (auto &v : mesh.vertices)
    {
        points->InsertNextPoint(v.pos.x, v.pos.y, v.pos.z);
        normals->InsertNextTuple3(v.normal.x, v.normal.y, v.normal.z);
    }

    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->GetPointData()->SetNormals(normals);

    auto arrowSource = vtkSmartPointer<vtkArrowSource>::New();
    arrowSource->SetTipLength(0.3);
    arrowSource->SetTipRadius(0.05);
    arrowSource->SetShaftRadius(0.02);

    auto glyph = vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetSourceConnection(arrowSource->GetOutputPort());
    glyph->SetInputData(polyData);
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(scale);
    glyph->Update();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(glyph->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
}