#pragma once

#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>

#include "Mesh.hpp"
namespace Loader
{
    bool loadBinarySTL(const std::string &path, RawMesh &mesh);
}