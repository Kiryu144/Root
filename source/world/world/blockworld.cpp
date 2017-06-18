/* Created by David Klostermann on 17.06.2017. */
#include "blockworld.h"

BlockWorld::BlockWorld() {
    m_stopChunkGeneration = false;
    m_chunkShader = &ResourceManager::shaders.get("chunk");
    m_chunkGenerationThread = std::thread(&BlockWorld::chunkGenerationLoop, std::ref(*this));
}

BlockWorld::~BlockWorld() {
    m_stopChunkGeneration = true;
    m_chunkGenerationThread.join();
}

void BlockWorld::generateChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
    m_chunkQueue.push_back(chunkPosition);
}

void BlockWorld::unloadChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    auto it = std::find(m_loadedChunks.begin(), m_loadedChunks.end(), chunkPosition);
    while (it != m_loadedChunks.end()){
        m_loadedChunks.erase(it);
        it = std::find(m_loadedChunks.begin(), m_loadedChunks.end(), chunkPosition);
    }
}

void BlockWorld::addToLoadedChunks(glm::vec2 chunkPosition) {
    if(!this->chunkLoaded(chunkPosition)){
        std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
        m_loadedChunks.push_back(chunkPosition);
    }
}

void BlockWorld::deleteChunk(glm::vec2 chunkPosition) {
    if(this->chunkExists(chunkPosition)){
        std::lock_guard<std::mutex> locker(m_chunkMutex);
        m_chunks.at(chunkPosition.x).erase(chunkPosition.y);
        this->unloadChunk(chunkPosition);
    }
}

Chunk &BlockWorld::getChunk(glm::vec2 chunkPosition) {
    return m_chunks[chunkPosition.x][chunkPosition.y];
}

bool BlockWorld::chunkExists(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkMutex);
    auto it = m_chunks.find(chunkPosition.x);
    if(it != m_chunks.end()){
        if(it->second.find(chunkPosition.y) != it->second.end()){
            return true;
        }
    }
    return false;
}

bool BlockWorld::chunkLoaded(glm::vec2 chunkPosition) {
    if(!this->chunkExists(chunkPosition)){
        return false;
    }
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    return std::find(m_loadedChunks.begin(), m_loadedChunks.end(), chunkPosition) != m_loadedChunks.end();
}

bool BlockWorld::chunkInQueue(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
    return std::find(m_chunkQueue.begin(), m_chunkQueue.end(), chunkPosition) != m_chunkQueue.end();
}

void BlockWorld::chunkGenerationLoop() {
    glfwMakeContextCurrent(AM::WindowHandler::getSharedGlfwWindow());
    while(!m_stopChunkGeneration){
        m_chunkQueueMutex.lock();
        if(m_chunkQueue.size() > 0){
            glm::vec2 chunkPos = m_chunkQueue.at(0); //Get position of the chunk to generate
            m_chunkQueue.erase(m_chunkQueue.begin());
            m_chunkQueueMutex.unlock();
            this->unloadChunk(chunkPos); //Prevent main thread from drawing unfinished chunk

            Chunk* chunk = nullptr;

            m_chunkMutex.lock();
            m_chunks[chunkPos.x][chunkPos.y];
            chunk = &m_chunks[chunkPos.x][chunkPos.y];
            m_chunkMutex.unlock();

            //TODO: Replace with actual chunk generator stuff
            for(int x = 0; x < 16; x++){
                for(int y = 0; y < 16; y++) {
                    for (int z = 0; z < 16; z++) {
                        chunk->setBlock(glm::vec3(x, y, z), Block(Voxel(glm::vec4(x/16.0f, y/16.0f, z/16.0f, 1))));
                    }
                }
            }
            //TODO ends here

            chunk->regenerateChunkMesh();
            glFinish(); //TODO: Check if this is a performance problem. Maybe batch uploading?

            this->addToLoadedChunks(chunkPos);
        }else{
            m_chunkQueueMutex.unlock();
        }
    }
}

int BlockWorld::loadedChunkAmount() {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    return m_loadedChunks.size();
}

void BlockWorld::draw(AM::Camera& cam) {
    for(const glm::vec2& chunkPos : m_loadedChunks){
        m_chunkBatch.push(&m_chunks[chunkPos.x][chunkPos.y], chunkPos);
    }
    m_chunkBatch.draw(m_chunkShader, cam);
}
