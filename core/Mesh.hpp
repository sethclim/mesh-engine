#pragma once

#include <vector>
#include <cmath>

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

inline Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline Vec3 operator*(double s, const Vec3 &v)
{
    return {s * v.x, s * v.y, s * v.z};
}

inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

inline double length(const Vec3 &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vec3 normalize(const Vec3 &v)
{
    double len = length(v);
    if (len == 0.0)
        return {0.0, 0.0, 0.0}; // handle zero vector safely
    return {v.x / len, v.y / len, v.z / len};
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
    Vec3 normal;
};

struct Triangle
{
    int v[3];
};

class RawMesh
{
public:
    std::vector<Vec3> vertices;
    std::vector<Triangle> faces;
    // std::vector<std::vector<int>> neighbors;

    int add_vertex(const Vec3 &v);
    void add_triangle(int v0, int v1, int v2);
    int vertex_count() const;
    int face_count() const;
};

using Edge = std::pair<int, int>;

struct EdgeClassification
{
    std::vector<Edge> boundaryEdges;
    std::vector<Edge> interiorEdges;
    std::vector<Edge> nonManifoldEdges;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;
    // std::vector<std::vector<int>> neighbors;
    std::vector<std::vector<int>> neighbors;

    EdgeClassification edges;

    int add_vertex(const Vec3 &v);
    void add_triangle(int v0, int v1, int v2);
    int vertex_count() const;
    int face_count() const;

    bool has_normals() const;
    void set_has_normals(bool value);

    bool has_edges() const;
    void set_has_edges(bool value);

private:
    bool hasNormals = false;
    bool hasEdges = false;
};
