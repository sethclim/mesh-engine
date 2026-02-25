#include "Mesh.hpp"

int BaseMesh::add_vertex(const Vec3 &v)
{
    vertices.push_back(Vertex{v});
    return vertices.size() - 1;
}

void BaseMesh::add_triangle(int v0, int v1, int v2)
{
    faces.push_back(Triangle{v0, v1, v2});
}

int BaseMesh::vertex_count() const
{
    return vertices.size();
}

int BaseMesh::face_count() const
{
    return faces.size();
}
