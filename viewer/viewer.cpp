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

    // Interactor (mouse, keyboard)
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // Render & start event loop
    window->Render();
    interactor->Start();
}