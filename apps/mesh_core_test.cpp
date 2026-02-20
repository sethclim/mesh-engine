#include <iostream>
#include "mesh.hpp"

int main()
{
    Mesh mesh;

    int v0 = mesh.add_vertex({0, 0, 0});
    int v1 = mesh.add_vertex({1, 0, 0});
    int v2 = mesh.add_vertex({0, 1, 0});

    mesh.add_triangle(v0, v1, v2);

    std::cout << "Vertices: " << mesh.vertex_count() << "\n";
    std::cout << "Faces: " << mesh.face_count() << "\n";

    return 0;
}