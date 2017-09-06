/* Created by David Klostermann on 17.06.2017. */
#include "blockworld.h"

glm::vec2 BlockWorld::getChunkPosition(glm::vec3 blockPosition) {
    return glm::vec2(int(blockPosition.x) >> 4, int(blockPosition.z) >> 4);
}

glm::vec3 BlockWorld::getChunkOffset(glm::vec3 worldPosition) {
    glm::vec2 positionChunk = getChunkPosition(worldPosition);
    glm::vec3 chunkOffset = glm::vec3(AM::pythonModulus(int(worldPosition.x), CHUNK_WIDTH), worldPosition.y, AM::pythonModulus(int(worldPosition.z), CHUNK_WIDTH));
    //glm::vec3 chunkOffset = glm::vec3(int(worldPosition.x) % CHUNK_WIDTH, worldPosition.y, int(worldPosition.z) % CHUNK_WIDTH);
    return chunkOffset;
}

BlockWorld::BlockWorld() : m_terrainGenerator(time(0)) {
    m_stopChunkGeneration = false;
    m_chunkShader = &ResourceManager::shaders.get("chunk");

    m_chunkGenerationThread = std::thread(&BlockWorld::chunkGenerationLoop, std::ref(*this));
    m_chunkMeshThread = std::thread(&BlockWorld::chunkMeshLoop, std::ref(*this), 1);
    //m_chunkManagementThread = std::thread(&BlockWorld::chunkManagementThread, std::ref(*this), 2);
}

BlockWorld::~BlockWorld() {
    m_stopChunkGeneration = true;
    m_chunkGenerationThread.join();
}

void BlockWorld::unloadChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    auto it = std::find(m_chunksLoaded.begin(), m_chunksLoaded.end(), chunkPosition);
    if (it != m_chunksLoaded.end()) {
        m_chunksLoaded.erase(it);
    }
}

void BlockWorld::loadChunk(glm::vec2 chunkPosition) {
    if(!this->chunkLoaded(chunkPosition)){
        std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
        m_chunksLoaded.push_back(chunkPosition);
    }
}

bool BlockWorld::chunkLoaded(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    return std::find(m_chunksLoaded.begin(), m_chunksLoaded.end(), chunkPosition) != m_chunksLoaded.end();
}

bool BlockWorld::chunkIsBusy(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_busyChunks);
    return std::find(m_chunksBusy.begin(), m_chunksBusy.end(), chunkPosition) != m_chunksBusy.end();
}

void BlockWorld::removeBusyChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_busyChunks);
    auto it = std::find(m_chunksBusy.begin(), m_chunksBusy.end(), chunkPosition);
    if (it != m_chunksBusy.end()) {
        m_chunksBusy.erase(it);
    }
}

void BlockWorld::addBusyChunk(glm::vec2 chunkPosition) {
    if(!this->chunkIsBusy(chunkPosition)){
        std::lock_guard<std::mutex> locker(m_busyChunks);
        m_chunksBusy.push_back(chunkPosition);
    }
}

void BlockWorld::deleteChunk(glm::vec2 chunkPosition) {
    if(this->chunkExists(chunkPosition)){
        std::lock_guard<std::mutex> locker(m_chunkDeleteMutex);
        m_deletingQueue.push_back(chunkPosition);
    }
}

Chunk &BlockWorld::getChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkMutex);
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


void BlockWorld::chunkGenerationLoop() {
    while(!m_stopChunkGeneration){
        m_chunkQueueMutex.lock();
        if(m_chunkGenerationQueue.size() > 0){
            glm::vec2 chunkPosition = m_chunkGenerationQueue.capBottom();
            m_chunkQueueMutex.unlock();

            this->unloadChunk(chunkPosition); //Prevent main thread from drawing unfinished chunk

            m_chunkMutex.lock();
            Chunk* chunk = &m_chunks[chunkPosition.x][chunkPosition.y];
            m_chunkMutex.unlock();

            m_terrainGenerator.generate(*chunk, chunkPosition); // ~+~ MAAAAAAAGIC ~+~

            m_chunkMeshMutex.lock();
            m_chunkMeshQueue.add(chunkPosition);
            m_chunkMeshMutex.unlock();

            this->loadChunk(chunkPosition); //Give it back to the main thread
        }else{
            m_chunkQueueMutex.unlock();
        }
    }
}

void BlockWorld::chunkMeshLoop(int windowIndex) {
    AM::WindowHandler::getSharedWindow(windowIndex)->makeContextCurrent();
    while(!m_stopChunkGeneration){
        m_chunkMeshMutex.lock();
        if(m_chunkMeshQueue.size() > 0){
            glm::vec2 chunkPos = m_chunkMeshQueue.capBottom(); //Get position of the chunkmesh to generate
            m_chunkMeshMutex.unlock();

            if(this->chunkExists(chunkPos)){
                this->addBusyChunk(chunkPos);
                m_chunkMutex.lock();
                Chunk* chunk = &m_chunks[chunkPos.x][chunkPos.y];
                m_chunkMutex.unlock();
                chunk->regenerateChunkMesh();
                chunk->uploadChunkMesh();
                glFinish();
                this->removeBusyChunk(chunkPos);
            }
        }else{
            m_chunkMeshMutex.unlock();
        }
    }
}

void BlockWorld::chunkManagementThread(int windowIndex) {
    AM::WindowHandler::getSharedWindow(windowIndex)->makeContextCurrent();
    while(!m_stopChunkGeneration){
        m_chunkDeleteMutex.lock();
        if(m_deletingQueue.size() > 0){
            glm::vec2 chunkPos = m_deletingQueue.at(0); //Get position of the chunk to delete
            m_deletingQueue.erase(m_deletingQueue.begin());
            m_chunkDeleteMutex.unlock();

            this->chunkIsBusy(chunkPos);

            if(this->chunkExists(chunkPos)){
                m_chunkMutex.lock();
                m_chunks.at(chunkPos.x).erase(chunkPos.y);
                m_chunkMutex.unlock();
            }

            m_chunkMeshMutex.lock();
            m_chunkMeshQueue.remove(chunkPos);
            m_chunkMeshMutex.unlock();

            m_chunkQueueMutex.lock();
            m_chunkGenerationQueue.remove(chunkPos);
            m_chunkQueueMutex.unlock();

            this->unloadChunk(chunkPos);
            this->removeBusyChunk(chunkPos);
        }else{
            m_chunkDeleteMutex.unlock();
        }
    }
}

int BlockWorld::loadedChunkAmount() {
    std::lock_guard<std::mutex> locker(m_loadedChunkMutex);
    return m_chunksLoaded.size();
}

void BlockWorld::draw(AM::Camera& cam, World& world) {
    std::lock_guard<std::mutex> locker(m_drawingMutex);
    std::lock_guard<std::mutex> locker2(m_chunkMutex);
    std::lock_guard<std::mutex> locker1(m_loadedChunkMutex);

    for (const glm::vec2 &chunkPos : m_chunksLoaded) {
        Chunk* chunk = &m_chunks[chunkPos.x][chunkPos.y];

        if(chunk->getChunkMesh().getVerticeAmount() > 0 && !this->chunkIsBusy(chunkPos)){
            m_chunkBatch.push(chunk, chunkPos);
        }
    }

    m_chunkBatch.draw(m_chunkShader, cam, world);
}

const std::deque<glm::vec2> &BlockWorld::getLoadedChunks() {
    return m_chunksLoaded;
}

Block BlockWorld::getBlock(glm::vec3 worldPosition) {
    return Block();
}

void BlockWorld::setBlock(glm::vec3 worldPosition, Block block) {
    glm::vec2 chunkPos = getChunkPosition(worldPosition);
    if(this->chunkExists(chunkPos))
    m_chunkMutex.lock();
    glm::vec3 chunkOffset = getChunkOffset(worldPosition);
    AM::Logger::info(glm::to_string(chunkOffset));
    m_chunks[chunkPos.x][chunkPos.y].setBlock(chunkOffset, block);
    m_chunkMutex.unlock();
    std::lock_guard<std::mutex> locker(m_chunkMeshMutex);
    m_chunkMeshQueue.addPriority(chunkPos);
}

void BlockWorld::generateChunk(glm::vec2 chunkPosition) {
    std::lock_guard<std::mutex> locker(m_chunkQueueMutex);
    m_chunkGenerationQueue.add(chunkPosition);
}








