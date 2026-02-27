#pragma once

#include "Mesh.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

struct EdgeHash
{
    std::size_t operator()(const Edge &e) const
    {
        // simple hash combining two integers
        return std::hash<int>()(e.first) ^ (std::hash<int>()(e.second) << 1);
    }
};

namespace Topology
{
    void edge_detection(Mesh &mesh)
    {
        std::unordered_map<Edge, int, EdgeHash> edgeCounts;

        for (const Triangle &t : mesh.faces)
        {
            int v0 = t.v[0];
            int v1 = t.v[1];
            int v2 = t.v[2];

            std::vector<Edge> edges{
                {v0, v1}, {v1, v2}, {v2, v0}};

            for (const Edge &e : edges)
            {

                Edge canonical = {std::min(e.first, e.second),
                                  std::max(e.first, e.second)};
                if (edgeCounts.find(canonical) != edgeCounts.end())
                {
                    edgeCounts[canonical] += 1;
                }
                else
                {
                    edgeCounts[canonical] = 1;
                }
            }
        }

        std::vector<Edge> boundaryEdges;
        std::vector<Edge> interiorEdges;
        std::vector<Edge> nonManifoldEdges;

        for (auto it = edgeCounts.begin(); it != edgeCounts.end(); ++it)
        {
            Edge e = it->first;
            int count = it->second;

            if (count == 1)
                boundaryEdges.push_back(e);
            else if (count == 2)
                interiorEdges.push_back(e);
            else
                nonManifoldEdges.push_back(e);

            // std::cout << "Key: (" << e.first << " " << e.second << ") , Value: " << it->second << "\n";
        }

        std::cout << "boundaryEdges: " << boundaryEdges.size() << " interiorEdges " << interiorEdges.size() << " nonManifoldEdges: " << nonManifoldEdges.size() << "\n";

        mesh.edges.boundaryEdges = boundaryEdges;
        mesh.edges.interiorEdges = interiorEdges;
        mesh.edges.nonManifoldEdges = nonManifoldEdges;

        mesh.set_has_edges(true);
    }
}