/* Created by David Klostermann on 14.06.2017. */
#ifndef ROOT_BLOCKMESH_H
#define ROOT_BLOCKMESH_H

#include <amethyst>
#include <set>
#include "world/block/iblockaccessible.h"
#include "static/basicmesh.h"

class BlockMesh {
private:
    IBlockAccessible& m_blockSource;

    AM::VBO<glm::vec3, 3> m_vertices;
    AM::VBO<glm::vec3, 3> m_normals;
    AM::VBO<glm::vec4, 4> m_colors;

    int m_verticeAmount = 0;

    std::vector<glm::vec3> translateVertices(std::vector<glm::vec3>& vertices, glm::vec3 pos);
public:
    BlockMesh(IBlockAccessible& source);

    void regenerate(AABB aabb, std::set<int> yCoords);
    void regenerate(AABB aabb);

    AM::VBO<glm::vec3, 3>& getVerticeVBO();
    AM::VBO<glm::vec3, 3>& getNormalVBO();
    AM::VBO<glm::vec4, 4>& getColorVBO();

    int getVerticeAmount();
};

#endif
