/* Created by David Klostermann on 19.06.2017. */
#ifndef ROOT_VOXELSTRUCTURE_H
#define ROOT_VOXELSTRUCTURE_H

#include <amethyst>
#include <algorithm>
#include "voxel/voxel.h"
#include "world/block/iblockaccessible.h"

/*
class VoxelStructure : public IBlockAccessible {
private:
    std::map<int16_t, std::map<int16_t, std::map<int16_t, Voxel>>> m_voxels;
    std::vector<glm::tvec3<int16_t>> m_allExistingVoxels;

    std::vector<glm::vec3> m_translateVertices(std::vector<glm::vec3>& vertices, glm::vec3 position);
public:
    VoxelStructure();

    bool voxelExists(glm::tvec3<int16_t> position);
    Voxel getVoxel(glm::tvec3<int16_t> position);
    void setVoxel(glm::tvec3<int16_t> position, Voxel voxel);
    const std::vector<glm::tvec3<int16_t>>& getVoxelPositions();
    void generateMesh(AM::Mesh<glm::vec3>& vertexMesh, AM::Mesh<glm::vec3>& normalMesh, AM::Mesh<glm::vec4>& colorMesh);
};
*/

#endif
