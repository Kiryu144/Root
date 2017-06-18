/* Created by David Klostermann on 14.06.2017. */
#include "blockmesh.h"

BlockMesh::BlockMesh(IBlockAccessible& source) : m_blockSource(source) {

}

std::vector<glm::vec3> BlockMesh::translateVertices(std::vector<glm::vec3> &vertices, glm::vec3 pos) {
    std::vector<glm::vec3> vec;
    for(int i = 0; i < vertices.size(); i++){
        vec.push_back(vertices.at(i) + pos);
    }
    return vec;
}

void BlockMesh::regenerate(AABB aabb, std::set<int> yCoords) {
    if(m_vertices.vboExists()) m_vertices.deleteVBO();
    if(m_normals.vboExists()) m_normals.deleteVBO();
    if(m_colors.vboExists()) m_colors.deleteVBO();

    AM::Mesh<glm::vec3> f_vertices;
    AM::Mesh<glm::vec3> f_normals;
    AM::Mesh<glm::vec4> f_color;

    auto it = yCoords.begin();

    for(int yi = 0; yi < yCoords.size(); yi++) {
        int y = *std::next(it, yi);
        for(int x = aabb.getFirst().x; x < aabb.getSecond().x; x++){
            for (int z = aabb.getFirst().z; z < aabb.getSecond().z; z++) {
                glm::vec3 currentPosition(x, y, z);
                if(!m_blockSource.blockExists(currentPosition)){
                    continue;
                }
                Block currentBlock = m_blockSource.getBlock(currentPosition);
                if(!currentBlock.exists()){
                    continue;
                }

                //Is true of specified side needs a face
                bool front = true, right = true, back = true, left = true, top = true, bottom = true;

                front = !m_blockSource.blockExists(currentPosition + glm::vec3(0, 0, -1)) || !m_blockSource.getBlock(currentPosition + glm::vec3(0, 0, -1)).isSolid();
                right = !m_blockSource.blockExists(currentPosition + glm::vec3(1, 0, 0)) || !m_blockSource.getBlock(currentPosition + glm::vec3(1, 0, 0)).isSolid();
                back = !m_blockSource.blockExists(currentPosition + glm::vec3(0, 0, 1)) || !m_blockSource.getBlock(currentPosition + glm::vec3(0, 0, 1)).isSolid();
                left = !m_blockSource.blockExists(currentPosition + glm::vec3(-1, 0, 0)) || !m_blockSource.getBlock(currentPosition + glm::vec3(-1, 0, 0)).isSolid();
                top = !m_blockSource.blockExists(currentPosition + glm::vec3(0, 1, 0)) || !m_blockSource.getBlock(currentPosition + glm::vec3(0, 1, 0)).isSolid();
                bottom = !m_blockSource.blockExists(currentPosition + glm::vec3(0, -1, 0)) || !m_blockSource.getBlock(currentPosition + glm::vec3(0, -1, 0)).isSolid();
                
                
                if(front){
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_front, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_front_normal);
                    for(int i = 0; i < 6; i++){
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }

                if(right){
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_right, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_right_normal);
                    for(int i = 0; i < 6; i++){
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }

                if(back){
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_back, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_back_normal);
                    for(int i = 0; i < 6; i++){
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }

                if(left){
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_left, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_left_normal);
                    for(int i = 0; i < 6; i++){
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }

                if(top){
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_top, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_top_normal);
                    for(int i = 0; i < 6; i++){
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }

                if(bottom) {
                    std::vector<glm::vec3> vertices = translateVertices(standardmesh::model_cube_bottom, glm::vec3(x, y, z));
                    f_vertices.add(vertices);
                    f_normals.add(standardmesh::model_cube_bottom_normal);
                    for (int i = 0; i < 6; i++) {
                        f_color.add(currentBlock.getVoxel().getColor());
                    }
                }
            }
        }
    }

    m_vertices.upload(f_vertices.get());
    m_normals.upload(f_normals.get());
    m_colors.upload(f_color.get());

    m_verticeAmount = f_vertices.get().size();
}

void BlockMesh::regenerate(AABB aabb) {
    std::set<int> yCoords;
    for(int i = aabb.getFirst().y; i <= aabb.getSecond().y; i++){
        yCoords.insert(i);
    }
    regenerate(aabb, yCoords);
}

AM::VBO<glm::vec3, 3>& BlockMesh::getVerticeVBO() {
    return m_vertices;
}

AM::VBO<glm::vec3, 3>& BlockMesh::getNormalVBO() {
    return m_normals;
}

AM::VBO<glm::vec4, 4>& BlockMesh::getColorVBO() {
    return m_colors;
}

int BlockMesh::getVerticeAmount() {
    return m_verticeAmount;
}



