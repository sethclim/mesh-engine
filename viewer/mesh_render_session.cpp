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

MeshRenderSession &MeshRenderSession::smooth_shading()
{
    smoothShading = true;
    return *this;
}

void MeshRenderSession::run()
{

    RenderContext ctx = create_render_context();
    // Convert mesh → polydata
    auto polyData = VTKAdapter::convert(mesh);

    auto sourceNormals = polyData->GetPointData()->GetNormals();

    auto actor = create_actor(polyData);

    // auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    // mapper->SetInputData(polyData);

    // auto actor = vtkSmartPointer<vtkActor>::New();
    // actor->SetMapper(mapper);
    // // actor->GetProperty()->LightingOff();
    // actor->GetProperty()->SetColor(actorColor.x, actorColor.y, actorColor.z);

    if (smoothShading)
        actor->GetProperty()->SetInterpolationToPhong();

    if (draw_normals)
    {
        display_vertex_normals(mesh, sourceNormals, ctx.renderer, normal_scale);
    }

    start_interaction(ctx, actor);
}

void MeshRenderSession::display_vertex_normals(const Mesh &mesh, vtkDataArray *normals, vtkRenderer *renderer, double scale)
{
    auto points = vtkSmartPointer<vtkPoints>::New();

    for (auto &v : mesh.vertices)
    {
        points->InsertNextPoint(v.pos.x, v.pos.y, v.pos.z);
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
