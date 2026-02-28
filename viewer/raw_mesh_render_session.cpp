#include "raw_mesh_render_session.hpp"

RawMeshRenderSession::RawMeshRenderSession(const RawMesh &mesh) : mesh(mesh) {};

void RawMeshRenderSession::run()
{
    RenderContext ctx = create_render_context();

    auto polyData = VTKAdapter::convert(mesh);

    auto actor = create_actor(polyData);

    start_interaction(ctx, actor);
}