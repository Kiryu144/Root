/* Created by David Klostermann on 24.06.2017. */
#include "world.h"

void World::updateLoadedChunks() {
    int halfViewDistance = m_playerViewDistance/2;
    glm::vec3 playerPos = m_protagonist.getTransformation().pos().get();
    glm::vec2 playerChunkPos = BlockWorld::getChunkPosition(playerPos);

    for(int r = 0; r <= halfViewDistance; r++){
        for(int offset = -r; offset <= r; offset++){
            glm::vec2 pos1 = glm::vec2(playerChunkPos.x + offset, playerChunkPos.y - r);
            glm::vec2 pos2 = glm::vec2(playerChunkPos.x + r     , playerChunkPos.y - offset);
            glm::vec2 pos3 = glm::vec2(playerChunkPos.x - offset, playerChunkPos.y + r);
            glm::vec2 pos4 = glm::vec2(playerChunkPos.x - r     , playerChunkPos.y + offset);

            if(!this->chunkExists(pos1)){
                this->generateChunk(pos1);
            }

            if(!this->chunkExists(pos2)){
                this->generateChunk(pos2);
            }

            if(!this->chunkExists(pos3)){
                this->generateChunk(pos3);
            }

            if(!this->chunkExists(pos4)){
                this->generateChunk(pos4);
            }
        }
    }

    for(const glm::vec2& loadedChunk : this->getLoadedChunks()){
        if(std::abs(loadedChunk.x - playerChunkPos.x) > halfViewDistance+2 || std::abs(loadedChunk.y - playerChunkPos.y) > halfViewDistance+2){
            this->deleteChunk(loadedChunk);
        }
    }
}

void World::update() {
    this->updateLoadedChunks();
    m_protagonist.update();
    this->draw(m_protagonist.getCamera()); //Drawing the blockworld
}

Player &World::getPlayer() {
    return m_protagonist;
}

void World::setViewDistance(int viewDistance) {
    m_playerViewDistance = viewDistance;
}

int World::getViewDistance() {
    return m_playerViewDistance;
}

