#include "NeighborBuilder.hpp"

namespace Topology
{
    void build_neighbors(Mesh &mesh)
    {
        size_t n = mesh.vertex_count();

        std::vector<std::unordered_set<int>> temp(n);

        for (const Triangle &t : mesh.faces)
        {
            int a = t.v[0];
            int b = t.v[1];
            int c = t.v[2];

            temp[a].insert(b);
            temp[a].insert(c);

            temp[b].insert(a);
            temp[b].insert(c);

            temp[c].insert(a);
            temp[c].insert(b);

            mesh.neighbors.resize(n);

            for (size_t i = 0; i < n; ++i)
            {
                mesh.neighbors[i] =
                    std::vector<int>(temp[i].begin(), temp[i].end());
            }
        }
    }
}
