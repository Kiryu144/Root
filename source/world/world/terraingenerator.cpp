/* Created by David Klostermann on 18.06.2017. */
#include "terraingenerator.h"

TerrainGenerator::TerrainGenerator(double seed) {
    m_terrainNoise = PerlinNoise(seed);
}

void TerrainGenerator::generate(Chunk &chunk, glm::vec2 chunkPosition) {
    glm::vec3 vec3ChunkPos = glm::vec3(chunkPosition.x, 0, chunkPosition.y);
    //https://stackoverflow.com/questions/24417122/cliffs-terrain-generation-in-minecraft-like-game
    for(int x = 0;x < 16; x++){
        for(int z = 0; z < 16; z++){
            glm::vec3 worldPosition = glm::vec3(x, 0, z) + (vec3ChunkPos * glm::vec3(16));
            float y = m_terrainNoise.noise(worldPosition.x/50.0f, worldPosition.z/50.0f) * 32;

            chunk.setBlock(glm::vec3(x, std::round(y), z), Block(Voxel(glm::vec4(0, 0.75, 0, 1)))); //TODO: Performance?
            for(int i = 1; i < 10; i++){
                chunk.setBlock(glm::vec3(x, std::round(y) - i, z), Block(Voxel(glm::vec4(211/255.0f, 211/255.0f, 211/255.0f, 1))));
            }
        }
    }
}
