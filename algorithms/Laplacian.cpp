#include "Mesh.hpp"

namespace Algorithms
{
    std::vector<Vec3> Laplacian(const Mesh &mesh)
    {
        std::vector<Vec3> lap(mesh.vertex_count());

        for (size_t i = 0; i < mesh.vertex_count(); i++)
        {
            const std::vector<int> neighbors = mesh.neighbors[i];
            if (neighbors.empty())
            {
                lap[i] = {0, 0, 0};
                continue;
            }

            Vec3 sum = {0, 0, 0};

            for (int j : neighbors)
            {
                sum.x += mesh.vertices[j].pos.x - mesh.vertices[i].pos.x;
                sum.y += mesh.vertices[j].pos.y - mesh.vertices[i].pos.y;
                sum.z += mesh.vertices[j].pos.z - mesh.vertices[i].pos.z;
            }

            double inv = 1.0 / neighbors.size();
            lap[i].x = sum.x * inv;
            lap[i].y = sum.y * inv;
            lap[i].z = sum.z * inv;
        }

        return lap;
    }
}
