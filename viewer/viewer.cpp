#include "viewer.hpp"

MeshRenderSession Viewer::render(const Mesh &mesh)
{
    return MeshRenderSession(mesh);
}

RawMeshRenderSession Viewer::render(const RawMesh &mesh)
{
    return RawMeshRenderSession(mesh);
}