/* Created by David Klostermann on 24.06.2017. */
#ifndef ROOT_WORLD_H
#define ROOT_WORLD_H

#include "world/world/blockworld.h"
#include "entity/player/player.h"

class World : public BlockWorld {
private:
    Player m_protagonist;
    int m_playerViewDistance = 4;

    void updateLoadedChunks();
public:
    World() {};
    void update();

    Player& getPlayer();

    void setViewDistance(int viewDistance);
    int getViewDistance();

};


#endif
