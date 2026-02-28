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

MeshRenderSession &MeshRenderSession::show_edges()
{
    showEdges = true;
    return *this;
}

void MeshRenderSession::run()
{

    RenderContext ctx = create_render_context();
    // Convert mesh → polydata
    auto polyData = VTKAdapter::convert(mesh);

    auto sourceNormals = polyData->GetPointData()->GetNormals();

    auto actor = create_actor(polyData);

    if (smoothShading)
        actor->GetProperty()->SetInterpolationToPhong();

    if (draw_normals)
        display_vertex_normals(mesh, sourceNormals, ctx.renderer, normal_scale);

    if (showEdges)
    {
        display_edge_detection_results(mesh, ctx.renderer);
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
    actor->GetProperty()->SetColor(normal_color.x, normal_color.y, normal_color.z);

    renderer->AddActor(actor);
}

void MeshRenderSession::display_edge_detection_results(const Mesh &mesh, vtkRenderer *renderer)
{
    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    auto points = vtkSmartPointer<vtkPoints>::New();
    auto lines = vtkSmartPointer<vtkCellArray>::New();
    auto colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3); // RGB
    colors->SetName("Colors");

    // Add all mesh vertices
    for (const auto &v : mesh.vertices)
    {
        points->InsertNextPoint(v.pos.x, v.pos.y, v.pos.z);
    }

    auto add_edges = [&](const std::vector<Edge> &edgeList, unsigned char r, unsigned char g, unsigned char b)
    {
        for (const auto &e : edgeList)
        {
            vtkIdType ids[2] = {e.first, e.second};
            lines->InsertNextCell(2, ids);
            colors->InsertNextTuple3(r, g, b);
        }
    };

    // Add edges with colors
    add_edges(mesh.edges.boundaryEdges, 255, 0, 0);      // Red
    add_edges(mesh.edges.interiorEdges, 0, 128, 255);    // Gray
    add_edges(mesh.edges.nonManifoldEdges, 255, 255, 0); // Yellow

    polyData->SetPoints(points);
    polyData->SetLines(lines);
    polyData->GetCellData()->SetScalars(colors);

    // Create mapper and actor
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(2.0);

    // Add to renderer
    renderer->AddActor(actor);
}