#include "Mesh.hpp"

int RawMesh::add_vertex(const Vec3 &v)
{
    vertices.push_back({v});
    return vertices.size() - 1;
}

void RawMesh::add_triangle(int v0, int v1, int v2)
{
    faces.push_back(Triangle{v0, v1, v2});
}

int RawMesh::vertex_count() const
{
    return vertices.size();
}

int RawMesh::face_count() const
{
    return faces.size();
}

int Mesh::add_vertex(const Vec3 &v)
{
    vertices.push_back(Vertex{v});
    return vertices.size() - 1;
}

void Mesh::add_triangle(int v0, int v1, int v2)
{
    faces.push_back(Triangle{v0, v1, v2});
}

int Mesh::vertex_count() const
{
    return vertices.size();
}

int Mesh::face_count() const
{
    return faces.size();
}

bool Mesh::has_normals() const
{
    return m_HasNormals;
}

void Mesh::set_has_normals(bool value)
{
    m_HasNormals = value;
}

bool Mesh::has_edges() const
{
    return m_HasEdges;
}

void Mesh::set_has_edges(bool value)
{
    m_HasEdges = value;
}
