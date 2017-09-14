/* Created by David Klostermann on 18.06.2017. */
#ifndef ROOT_CHUNKBATCH_H
#define ROOT_CHUNKBATCH_H

#include <stack>
#include "world/chunk/chunk.h"

class World;

class ChunkBatch {
private:
    std::stack<Chunk*> m_chunks;
    std::stack<glm::vec2> m_chunkPositions;
public:
    void push(Chunk* chunk, glm::vec2 chunkPosition);
    void draw(AM::Shader* shader, AM::Camera& cam, World& world);
};

#endif
