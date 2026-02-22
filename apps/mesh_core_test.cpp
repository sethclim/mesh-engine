#include <iostream>
#include "mesh.hpp"
#include "NeighborBuilder.hpp"
#include "Laplacian.hpp"

#include "viewer.hpp"

int main()
{
    // -------------------------------
    // Mesh 1: square (your existing mesh)
    // -------------------------------
    Mesh mesh1;

    int v0 = mesh1.add_vertex({0, 0, 0});
    int v1 = mesh1.add_vertex({1, 0, 0});
    int v2 = mesh1.add_vertex({0, 1, 0});
    int v3 = mesh1.add_vertex({1, 1, 0});

    mesh1.add_triangle(v0, v1, v2);
    mesh1.add_triangle(v1, v3, v2);

    Topology::build_neighbors(mesh1);

    double alpha = 0.1;
    auto lap1 = Algorithms::Laplacian(mesh1);

    for (int i = 0; i < 20; i++)
    {
        auto lap = Algorithms::Laplacian(mesh1);

        for (size_t v = 0; v < mesh1.vertex_count(); v++)
        {
            mesh1.vertices[v].pos += alpha * lap[v];
        }
    }

    // -------------------------------
    // Mesh 2: pyramid
    // -------------------------------
    Mesh mesh2;

    // Base vertices
    int b0 = mesh2.add_vertex({2, 0, 0});
    int b1 = mesh2.add_vertex({3, 0, 0});
    int b2 = mesh2.add_vertex({3, 1, 0});
    int b3 = mesh2.add_vertex({2, 1, 0});

    // Apex
    int apex = mesh2.add_vertex({2.5, 0.5, 1});

    // Base
    mesh2.add_triangle(b0, b1, b2);
    mesh2.add_triangle(b0, b2, b3);

    // Sides
    mesh2.add_triangle(b0, b1, apex);
    mesh2.add_triangle(b1, b2, apex);
    mesh2.add_triangle(b2, b3, apex);
    mesh2.add_triangle(b3, b0, apex);

    Topology::build_neighbors(mesh2);

    auto lap2 = Algorithms::Laplacian(mesh2);
    for (size_t i = 0; i < mesh2.vertex_count(); ++i)
    {
        mesh2.vertices[i].pos.x += alpha * lap2[i].x;
        mesh2.vertices[i].pos.y += alpha * lap2[i].y;
        mesh2.vertices[i].pos.z += alpha * lap2[i].z;
    }

    // -------------------------------
    // Render both meshes
    // -------------------------------
    Viewer viewer;
    viewer.render(mesh1);
    viewer.render(mesh2); // optionally you can merge into one viewer

    return 0;
}