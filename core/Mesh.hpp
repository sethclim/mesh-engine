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

    bool operator==(const Vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

inline Vec3 operator*(double s, const Vec3 &v)
{
    return {s * v.x, s * v.y, s * v.z};
}

namespace std
{
    template <>
    struct hash<Vec3>
    {
        size_t operator()(const Vec3 &v) const noexcept
        {
            size_t hx = std::hash<float>{}(v.x);
            size_t hy = std::hash<float>{}(v.y);
            size_t hz = std::hash<float>{}(v.z);

            // Combine hashes (classic boost-style combine)
            size_t seed = hx;
            seed ^= hy + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hz + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };

}

struct Vertex
{
    Vec3 pos;
};

struct Triangle
{
    int v[3];
};

class BaseMesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;
    // std::vector<std::vector<int>> neighbors;

    int add_vertex(const Vec3 &v);
    void add_triangle(int v0, int v1, int v2);
    int vertex_count() const;
    int face_count() const;
};

class RawMesh : public BaseMesh
{
};

class Mesh : public BaseMesh
{
public:
    std::vector<std::vector<int>> neighbors;
};
