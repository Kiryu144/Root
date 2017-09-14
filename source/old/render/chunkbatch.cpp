/* Created by David Klostermann on 18.06.2017. */
#include "chunkbatch.h"
#include "world/world/world.h"

void ChunkBatch::push(Chunk *chunk, glm::vec2 chunkPosition) {
    if(chunk != nullptr){
        m_chunks.push(chunk);
        m_chunkPositions.push(chunkPosition);
    }
}

void ChunkBatch::draw(AM::Shader *shader, AM::Camera& cam, World& world) {
    if(m_chunks.size() == 0){
        return;
    }

    AM::Transformation transformation;

    shader->bind();
    shader->setUniform("projection", cam.getProjection());
    shader->setUniform("view", cam.getView());
    shader->setUniform("lightDirection", world.getLightDirection());
    shader->setUniform("lightColor", glm::vec3(1, 1, 1));
    shader->setUniform("ambientStrenght", world.getAmbientLight());

    while(m_chunks.size() > 0){
        Chunk* chunk = m_chunks.top();
        glm::vec2 chunkPosition = m_chunkPositions.top();

        transformation.pos().set(glm::vec3(chunkPosition.x * 16, 0, chunkPosition.y * 16));
        shader->setUniform("transformation", transformation.getMatrix()); //TODO: Only pass position

        chunk->getChunkMesh().getVerticeVBO().bind(0);
        chunk->getChunkMesh().getNormalVBO().bind(1);
        chunk->getChunkMesh().getColorVBO().bind(2);

        glDrawArrays(GL_TRIANGLES, 0, chunk->getChunkMesh().getVerticeAmount());

        m_chunks.pop();
        m_chunkPositions.pop();
    }
}
