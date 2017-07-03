/* Created by David Klostermann on 24.06.2017. */
#ifndef ROOT_WORLD_H
#define ROOT_WORLD_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "world/world/blockworld.h"
#include "entity/player/player.h"
#include "render/render.h"

class World : public BlockWorld {
private:
    Player m_protagonist;
    int m_playerViewDistance = 4;

    static const int m_maxTime = 24000;
    float m_time = 3000;

    Render::URenderData m_sunVbo;
    AM::Texture* m_sunTexture;
    AM::Shader* m_sunShader;

    AM::Texture* m_skyTexture;
    AM::VBO<glm::vec3, 3>* m_skyVBO;
    AM::Shader* m_skyShader;

    float m_ambientLight = 0.75f;
    glm::vec3 m_lightDirection;

    void updateLoadedChunks();
    void drawSky();
    void drawSun();
public:
    World();
    void update();

    Player& getPlayer();

    void setViewDistance(int viewDistance);
    int getViewDistance();

    float getTimeNormalized();
    float getAmbientLight();
    glm::vec3 getLightDirection();
};


#endif
