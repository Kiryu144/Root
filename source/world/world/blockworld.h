/* Created by David Klostermann on 17.06.2017. */
#ifndef ROOT_BLOCKWORLD_H
#define ROOT_BLOCKWORLD_H

#include <deque>
#include <algorithm>
#include <atomic>

#include "resources/resourcemanager.h"
#include "world/world/terraingenerator.h"
#include "world/chunk/chunk.h"
#include "render/chunkbatch.h"

class BlockWorld {
protected:
    std::map<int, std::map<int, Chunk>> m_chunks; //All chunks stored
    std::deque<glm::vec2> m_chunksLoaded; //Chunks currently updated/drawn
    std::deque<glm::vec2> m_chunksBusy; //Chunks that is worked on (kinda like a mutex)

    AM::Queue<glm::vec2> m_chunkGenerationQueue; //Chunks that have to be generated
    AM::Queue<glm::vec2> m_chunkMeshQueue; //Chunks that need a ((((fresh mesh))))

    std::deque<glm::vec2> m_deletingQueue; //Chunks that have to be deleted

    std::mutex m_chunkMutex,
                m_loadedChunkMutex,
                m_chunkQueueMutex,
                m_chunkDeleteMutex,
                m_drawingMutex,
                m_chunkMeshMutex,
                m_busyChunks;

    std::thread m_chunkGenerationThread;
    std::thread m_chunkMeshThread;
    std::thread m_chunkManagementThread;

    std::atomic<bool> m_stopChunkGeneration;

    AM::Shader* m_chunkShader;
    ChunkBatch m_chunkBatch;

    TerrainGenerator m_terrainGenerator;
public:
    static glm::vec2 getChunkPosition(glm::vec3 blockPosition);
    static glm::vec3 getChunkOffset(glm::vec3 worldPosition);

    BlockWorld();
    ~BlockWorld();

    void chunkGenerationLoop();
    void chunkMeshLoop(int windowIndex);
    //void chunkManagementThread(int windowIndex);

    void unloadChunk(glm::vec2 chunkPosition);
    void loadChunk(glm::vec2 chunkPosition);
    bool chunkLoaded(glm::vec2 chunkPosition);

    bool chunkIsBusy(glm::vec2 chunkPosition);
    void removeBusyChunk(glm::vec2 chunkPosition);
    void addBusyChunk(glm::vec2 chunkPosition);

    void generateChunk(glm::vec2 chunkPosition);
    void deleteChunk(glm::vec2 chunkPosition);
    Chunk& getChunk(glm::vec2 chunkPosition);
    bool chunkExists(glm::vec2 chunkPosition);

    int  loadedChunkAmount();
    const std::deque<glm::vec2>& getLoadedChunks();

    void setBlock(glm::vec3 worldPosition, Block block);
    Block getBlock(glm::vec3 worldPosition);

    void draw(AM::Camera& cam, World& world);
};


#endif
