/* Created by David Klostermann on 17.06.2017. */
#ifndef ROOT_BLOCKWORLD_H
#define ROOT_BLOCKWORLD_H

#include <deque>
#include <algorithm>
#include <atomic>

#include "resources/resourcemanager.h"
#include "world/chunk/chunk.h"
#include "render/chunkbatch.h"

class BlockWorld {
private:
    std::map<int, std::map<int, Chunk>> m_chunks; //All chunks stored
    std::deque<glm::vec2> m_loadedChunks; //Chunks currently drawn/updated
    std::deque<glm::vec2> m_chunkQueue; //Chunks that have to be generated

    std::mutex m_chunkMutex, m_loadedChunkMutex, m_chunkQueueMutex;
    std::thread m_chunkGenerationThread;
    std::atomic<bool> m_stopChunkGeneration;

    AM::Shader* m_chunkShader;
    ChunkBatch m_chunkBatch;

public:
    BlockWorld();
    ~BlockWorld();

    void chunkGenerationLoop();

    void generateChunk(glm::vec2 chunkPosition);
    void unloadChunk(glm::vec2 chunkPosition);
    void addToLoadedChunks(glm::vec2 chunkPosition);
    void deleteChunk(glm::vec2 chunkPosition);
    Chunk& getChunk(glm::vec2 chunkPosition);
    bool chunkExists(glm::vec2 chunkPosition);
    bool chunkLoaded(glm::vec2 chunkPosition);
    bool chunkInQueue(glm::vec2 chunkPosition);
    int  loadedChunkAmount();

    void update();
    void draw(AM::Camera& cam);



};


#endif
