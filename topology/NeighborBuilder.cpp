#include "NeighborBuilder.hpp"

namespace Topology
{
    Mesh weld_vertices(RawMesh &rMesh)
    {
        std::vector<Vertex> newVertices;
        std::vector<Triangle> newFaces;
        std::unordered_map<Vec3, int> vertexMap;

        for (const Triangle &t : rMesh.faces)
        {
            Triangle newFaceIndices;

            for (int i = 0; i < 3; i++)
            {
                int index = t.v[i];
                Vertex vertex = rMesh.vertices[index];

                Vec3 key = quantize_pos(vertex.pos);

                int mappedIndex;
                if (vertexMap.find(key) != vertexMap.end())
                {
                    mappedIndex = vertexMap[key];
                }
                else
                {
                    mappedIndex = newVertices.size();
                    newVertices.emplace_back(vertex);
                    vertexMap[key] = mappedIndex;
                }
                newFaceIndices.v[i] = mappedIndex;
            }
            newFaces.emplace_back(newFaceIndices);
        }

        Mesh newMesh;
        newMesh.vertices = newVertices;
        newMesh.faces = newFaces;

        return newMesh;
    }

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

    Vec3 quantize_pos(Vec3 pos)
    {
        double qx = round(pos.x / EPS);
        double qy = round(pos.y / EPS);
        double qz = round(pos.z / EPS);

        return Vec3({qx, qy, qz});
    }
}
