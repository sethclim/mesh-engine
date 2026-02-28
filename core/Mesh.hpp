#pragma once

#include <vector>

struct Vec3
{
    double x, y, z;

    Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};

struct Vertex
{
    Vec3 pos;
};

struct Triangle
{
    int v[3];
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;
    std::vector<std::vector<int>> neighbors;

    int add_vertex(const Vec3 &v);
    void add_triangle(int v0, int v1, int v2);
    int vertex_count() const;
    int face_count() const;
};

inline Vec3 operator*(double s, const Vec3 &v)
{
    return {s * v.x, s * v.y, s * v.z};
}