
#pragma once

#include "Mesh.hpp"
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace Topology
{
    const double EPS = 1e-6;
    Mesh weld_vertices(RawMesh &rMesh);
    void build_neighbors(Mesh &mesh);
    void calculate_normals(Mesh &mesh);

    Vec3 quantize_pos(Vec3 pos);
}
