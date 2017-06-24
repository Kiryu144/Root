/* Created by David Klostermann on 24.06.2017. */
#ifndef ROOT_PLAYER_H
#define ROOT_PLAYER_H

#include "entity/entity.h"

class Player : public Entity {
private:
    AM::Camera m_playerCamera;
public:
    Player();
    AM::Camera& getCamera();

    void update();

};

#endif
