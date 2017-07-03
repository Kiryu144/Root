/* Created by David Klostermann on 24.06.2017. */
#include "world.h"


World::World() {
    m_sunVbo.vertices.upload(standardmesh::model_plane);
    m_sunVbo.uv.upload(standardmesh::model_plane_uv);
    m_skyVBO = &ResourceManager::vbo3D.get("sphere_vertices");

    m_sunTexture = new AM::Texture("./sun.png");
    m_skyTexture = &ResourceManager::textures.get("sky");

    m_sunShader = &ResourceManager::shaders.get("billboard texture");
    m_skyShader = &ResourceManager::shaders.get("sky");
}


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
    m_time += AM::DeltaTime::getDeltaTime();
    if(m_time >= m_maxTime){
        m_time -= m_maxTime;
    }
    float angle = M_PI*2 * this->getTimeNormalized();
    m_lightDirection = glm::vec3(0, sin(angle), cos(angle));


    this->updateLoadedChunks();
    m_protagonist.update();

    this->drawSky();
    this->drawSun();
    this->draw(m_protagonist.getCamera(), *this); //Drawing the blockworld
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

void World::drawSky() {
    m_skyShader->bind();

    m_skyShader->setUniform("projection", m_protagonist.getCamera().getProjection());
    m_skyShader->setUniform("view", m_protagonist.getCamera().getView());
    m_skyShader->setUniform("transformation", AM::Transformation(AM::Position(glm::vec3(0, 50, 0)), AM::Quaternion(), AM::Scale(glm::vec3(6000))).getMatrix());
    m_skyShader->setUniform("time", m_time/m_maxTime);

    m_skyTexture->bind();

    m_skyVBO->bind(0);

    glDrawArrays(GL_TRIANGLES, 0, m_skyVBO->getVerticeAmount());
}

void World::drawSun() {
    m_sunTexture->bind();

    m_sunShader->bind();
    m_sunShader->setUniform("projection", m_protagonist.getCamera().getProjection());
    m_sunShader->setUniform("view", m_protagonist.getCamera().getView());
    m_sunShader->setUniform("transformation", AM::Transformation(AM::Position((m_lightDirection * glm::vec3(-5000, 5000, -5000)) + m_protagonist.getTransformation().getPosition().get()), AM::Quaternion(), AM::Scale(glm::vec3(0.25))).getMatrix());
    m_sunShader->setUniform("normalizedWindowSize", AM::WindowHandler::getWindow()->getSize() / glm::vec2(AM::WindowHandler::getWindow()->getSize().x)); //TODO: Check that shit

    m_sunVbo.vertices.bind(0);
    m_sunVbo.uv.bind(1);

    glDrawArrays(GL_TRIANGLES, 0, standardmesh::model_plane.size());
}

float World::getTimeNormalized() {
    return m_time/m_maxTime;
}

float World::getAmbientLight() {
    return m_ambientLight;
}

glm::vec3 World::getLightDirection() {
    return m_lightDirection;
}


