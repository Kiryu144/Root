/* Created by David Klostermann on 03.06.2017. */
#include "chunk.h"

int get2DIndex(int x, int y);
int get2DIndex(glm::vec2 vec);
bool positionIsInsideChunk(glm::vec3 pos);
glm::vec2 get2DPosition(int index);

int Chunk::get2DIndex(int x, int y) {
    return y * CHUNK_WIDTH + x;
}

int Chunk::get2DIndex(glm::vec2 vec) {
    return get2DIndex(vec.x, vec.y);
}

glm::vec2 Chunk::get2DPosition(int index) { //TODO: Get yo math straight
    return glm::vec2(index % CHUNK_WIDTH, int(index / CHUNK_WIDTH));
}

bool Chunk::positionIsInsideChunk(glm::vec3 pos) {
    return ((pos.x >= 0 && pos.z >= 0) && (pos.x < CHUNK_WIDTH && pos.z < CHUNK_WIDTH));
}


Chunk::Chunk() : m_blockMesh(*this) {

}

void Chunk::createEmptyLayer(long height) {
    std::lock_guard<std::mutex> locker(m_layersMutex);
    m_chunkLayers[height] = std::vector<std::unique_ptr<Block>>(CHUNK_AREA);
    m_existingLayers.insert(int(height)); //TODO: Is this thread-safe?
}

bool Chunk::layerExists(long height) {
    std::lock_guard<std::mutex> locker(m_layersMutex);
    return m_chunkLayers.find(height) != m_chunkLayers.end();
}

void Chunk::setBlock(glm::vec3 chunkPosition, Block block) {
    if(!layerExists(chunkPosition.y)){
        createEmptyLayer(chunkPosition.y);
    }
    std::lock_guard<std::mutex> locker(m_layersMutex);
    m_chunkLayers.at(chunkPosition.y).at(get2DIndex(chunkPosition.x, chunkPosition.z)) = std::unique_ptr<Block>(new Block(block));
}

Block Chunk::getBlock(glm::vec3 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_layersMutex);
    return *m_chunkLayers.at(chunkPosition.y).at(get2DIndex(chunkPosition.x, chunkPosition.z));
}

bool Chunk::blockExists(glm::vec3 chunkPosition) {
    if(!layerExists(chunkPosition.y) || !Chunk::positionIsInsideChunk(chunkPosition)){
        return false;
    }

    std::lock_guard<std::mutex> locker(m_layersMutex);
    return m_chunkLayers.at(chunkPosition.y).at(get2DIndex(chunkPosition.x, chunkPosition.z)) != nullptr;
}

BlockMesh &Chunk::getChunkMesh() {
    return m_blockMesh;
}

void Chunk::regenerateChunkMesh() {
    m_blockMesh.regenerate(AABB(glm::vec3(0, 0, 0), glm::vec3(16, 8, 16)), m_existingLayers);
}
