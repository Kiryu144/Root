/* Created by David Klostermann on 03.06.2017. */
#ifndef ROOT_CHUNK_H
#define ROOT_CHUNK_H

#define CHUNK_WIDTH 16
#define CHUNK_AREA 16*16

#include <vector>
#include <map>
#include <memory>
#include <THREADS/mingw.thread.h>
#include <THREADS/mingw.mutex.h>

#include "world/block/iblockaccessible.h"
#include "world/block/block.h"
#include "world/block/blockmesh.h"

class Chunk : public IBlockAccessible {
private:
    std::map<long, std::vector<std::unique_ptr<Block>>> m_chunkLayers;
    std::set<int> m_existingLayers;
    std::mutex m_layersMutex;

    BlockMesh m_blockMesh;
public:
    Chunk();

    //TODO: Move to IBlockAccessible (?)
    static int get2DIndex(int x, int y);
    static int get2DIndex(glm::vec2 vec);
    static glm::vec2 get2DPosition(int index);
    static bool positionIsInsideChunk(glm::vec3 pos);

    void createEmptyLayer(long height);
    bool layerExists(long height);

    void setBlock(glm::vec3 chunkPosition, Block block);
    Block getBlock(glm::vec3 chunkPosition);
    bool blockExists(glm::vec3 chunkPosition);

    BlockMesh& getChunkMesh();
    void regenerateChunkMesh();
};

#endif
