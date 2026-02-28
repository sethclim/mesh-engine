#pragma once

#include <vector>

#include "Mesh.hpp"

namespace Algorithms
{
    std::vector<Vec3> Laplacian(const Mesh &mesh);
}
