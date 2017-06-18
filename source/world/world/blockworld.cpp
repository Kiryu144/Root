/* Created by David Klostermann on 17.06.2017. */
#include "blockworld.h"

BlockWorld::BlockWorld() : m_terrainGenerator(time(0)) {
    m_stopChunkGeneration = false;
    m_chunkShader = &ResourceManager::shaders.get("chunk");
    m_chunkGenerationThread = std::thread(&BlockWorld::chunkLoop, std::ref(*this));
}

BlockWorld::~BlockWorld() {
    m_stopChunkGeneration = true;
    m_chunkGenerationThread.join();
}

void BlockWorld::generateChunk(glm::vec2 chunkPosition) {
    if(!this->chunkInGeneratingQueue(chunkPosition)) {
        std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
        m_generateQueue.push_back(chunkPosition);
    }
}

void BlockWorld::unloadChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    auto it = std::find(m_loadedChunks.begin(), m_loadedChunks.end(), chunkPosition);
    if (it != m_loadedChunks.end()) {
        m_loadedChunks.erase(it);
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
        std::lock_guard<std::mutex> locker(m_chunkDeleteMutex);
        m_deletingQueue.push_back(chunkPosition);
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

bool BlockWorld::chunkInGeneratingQueue(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
    return std::find(m_generateQueue.begin(), m_generateQueue.end(), chunkPosition) != m_generateQueue.end();
}

void BlockWorld::removeFromQueue(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
    auto it = std::find(m_generateQueue.begin(), m_generateQueue.end(), chunkPosition);
    while (it != m_generateQueue.end()) {
        m_generateQueue.erase(it);
        it = std::find(m_generateQueue.begin(), m_generateQueue.end(), chunkPosition);
    }
}

void BlockWorld::chunkLoop() {
    glfwMakeContextCurrent(AM::WindowHandler::getSharedGlfwWindow());
    while(!m_stopChunkGeneration){
        m_chunkQueueMutex.lock();
        if(m_generateQueue.size() > 0){
            glm::vec2 chunkPos = m_generateQueue.at(0); //Get position of the chunk to generate
            m_generateQueue.erase(m_generateQueue.begin());
            m_chunkQueueMutex.unlock();
            this->unloadChunk(chunkPos); //Prevent main thread from drawing unfinished chunk

            Chunk* chunk = nullptr;

            m_chunkMutex.lock();
            m_chunks[chunkPos.x][chunkPos.y];
            chunk = &m_chunks[chunkPos.x][chunkPos.y];
            m_chunkMutex.unlock();

            m_terrainGenerator.generate(*chunk, chunkPos);

            chunk->regenerateChunkMesh();
            glFinish(); //TODO: Check if this is a performance problem. Maybe batch uploading?

            this->addToLoadedChunks(chunkPos);
        }else{
            m_chunkQueueMutex.unlock();
        }

        m_chunkDeleteMutex.lock();
        if(m_deletingQueue.size() > 0){
            std::lock_guard<std::mutex> locker(m_drawingMutex);
            glm::vec2 chunkPos = m_deletingQueue.at(0); //Get position of the chunk to generate
            m_deletingQueue.erase(m_deletingQueue.begin());
            m_chunkDeleteMutex.unlock();

            if(this->chunkExists(chunkPos)){
                m_chunkMutex.lock();
                m_chunks.at(chunkPos.x).erase(chunkPos.y);
                m_chunkMutex.unlock();
            }else{
                this->removeFromQueue(chunkPos);
            }

            this->unloadChunk(chunkPos);
        }else{
            m_chunkDeleteMutex.unlock();
        }
    }
}

int BlockWorld::loadedChunkAmount() {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    return m_loadedChunks.size();
}

void BlockWorld::draw(AM::Camera& cam) {
    {
        std::lock_guard<std::mutex> locker(m_drawingMutex);
        std::lock_guard<std::mutex> locker1(m_loadedChunkMutex);
        for (const glm::vec2 &chunkPos : m_loadedChunks) {
            m_chunkBatch.push(&m_chunks[chunkPos.x][chunkPos.y], chunkPos);
        }
        m_chunkBatch.draw(m_chunkShader, cam);
    }
}

