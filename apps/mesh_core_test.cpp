#include <iostream>
#include "mesh.hpp"
#include "NeighborBuilder.hpp"
#include "Laplacian.hpp"

int main()
{
    Mesh mesh;

    int v0 = mesh.add_vertex({0, 0, 0});
    int v1 = mesh.add_vertex({1, 0, 0});
    int v2 = mesh.add_vertex({0, 1, 0});

    mesh.add_triangle(v0, v1, v2);

    int v3 = mesh.add_vertex({1, 1, 0});
    mesh.add_triangle(v1, v3, v2);

    std::cout << "Vertices: " << mesh.vertex_count() << "\n";
    std::cout << "Faces: " << mesh.face_count() << "\n";

    Topology::build_neighbors(mesh);

    for (size_t i = 0; i < mesh.vertex_count(); ++i)
    {
        std::cout << "Vertex " << i
                  << " len neighbors: "
                  << mesh.neighbors[i].size() << "\n";
        std::cout << "neighbors: \n";
        for (size_t j = 0; j < mesh.neighbors[i].size(); ++j)
        {
            std::cout << mesh.neighbors[i][j] << ", ";
        }
        std::cout << "\n";
    }

    double alpha = 0.1;
    auto lap = Algorithms::Laplacian(mesh);

    for (size_t i = 0; i < mesh.vertex_count(); ++i)
    {
        mesh.vertices[i].pos.x += alpha * lap[i].x;
        mesh.vertices[i].pos.y += alpha * lap[i].y;
        mesh.vertices[i].pos.z += alpha * lap[i].z;
    }

    return 0;
}