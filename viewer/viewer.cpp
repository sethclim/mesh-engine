#include "viewer.hpp"

void Viewer::render(const RawMesh &mesh)
{
    // Convert mesh → vtkPolyData
    vtkSmartPointer<vtkPolyData> polyData = VTKAdapter::convert(mesh);

    // Create mapper & actor
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Optionally set color
    actor->GetProperty()->SetColor(1.0, 0.5, 0.3);

    // Renderer + window
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(800, 600);

    // Interactor (mouse, keyboard)
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // Render & start event loop
    window->Render();
    interactor->Start();
}

void Viewer::render(const Mesh &mesh)
{
    // Convert mesh → vtkPolyData
    vtkSmartPointer<vtkPolyData> polyData = VTKAdapter::convert(mesh);

    // Create mapper & actor
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Optionally set color
    actor->GetProperty()->SetColor(1.0, 0.5, 0.3);

    // Renderer + window
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(800, 600);

    show_vertex_normals(mesh, renderer, 4);

    // Interactor (mouse, keyboard)
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // Render & start event loop
    window->Render();
    interactor->Start();
}

void Viewer::show_vertex_normals(const Mesh &mesh, vtkRenderer *renderer, double scale = 0.4)
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