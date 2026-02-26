#include "raw_mesh_render_session.hpp"

RawMeshRenderSession::RawMeshRenderSession(const RawMesh &mesh) : mesh(mesh) {};

// RawMeshRenderSession &RawMeshRenderSession::show_vertex_normals(
//     double scale,
//     const Vec3 &color)
// {
//     draw_normals = true;
//     normal_scale = scale;
//     normal_color = color;
//     return *this;
// }

void RawMeshRenderSession::run()
{
    RenderContext ctx = create_render_context();

    auto polyData = VTKAdapter::convert(mesh);

    auto actor = create_actor(polyData);

    start_interaction(ctx, actor);
}