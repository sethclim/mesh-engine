#pragma once

#include "mesh_render_session.hpp"
#include "raw_mesh_render_session.hpp"

class Viewer
{
public:
    static MeshRenderSession render(const Mesh &mesh);
    static RawMeshRenderSession render(const RawMesh &mesh);
};