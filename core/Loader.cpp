#include "Loader.hpp"

namespace Loader
{
    bool loadBinarySTL(const std::string &path, RawMesh &mesh)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            return false;

        // Skip header
        char header[80];
        file.read(header, 80);

        uint32_t triangleCount;
        file.read(reinterpret_cast<char *>(&triangleCount), 4);

        std::cout << "TriCout" << triangleCount << std::endl;

        mesh.vertices.reserve(triangleCount * 3);
        mesh.faces.reserve(triangleCount);

        for (uint32_t i = 0; i < triangleCount; ++i)
        {
            float normal[3];
            float v0[3], v1[3], v2[3];
            uint16_t attr;

            file.read(reinterpret_cast<char *>(normal), 12);
            file.read(reinterpret_cast<char *>(v0), 12);
            file.read(reinterpret_cast<char *>(v1), 12);
            file.read(reinterpret_cast<char *>(v2), 12);
            file.read(reinterpret_cast<char *>(&attr), 2);

            int baseIndex = static_cast<int>(mesh.vertices.size());

            mesh.vertices.push_back({v0[0], v0[1], v0[2]});
            mesh.vertices.push_back({v1[0], v1[1], v1[2]});
            mesh.vertices.push_back({v2[0], v2[1], v2[2]});

            mesh.faces.push_back({baseIndex, baseIndex + 1, baseIndex + 2});
        }

        return true;
    }
}
