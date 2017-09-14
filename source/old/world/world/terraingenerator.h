/* Created by David Klostermann on 18.06.2017. */
#ifndef ROOT_TERRAINGENERATOR_H
#define ROOT_TERRAINGENERATOR_H

#include "world/chunk/chunk.h"

#include <PERLIN/PerlinNoise.hpp>

class TerrainGenerator {
private:
    double m_seed;

    PerlinNoise m_terrainNoise;
public:
    TerrainGenerator(double seed);
    void generate(Chunk& chunk, glm::vec2 chunkPosition);
};


#endif
