/* Created by David Klostermann on 24.06.2017. */
#include "player.h"

Player::Player() {
    glm::vec2 screenSize = AM::WindowHandler::getWindow()->getSize();
    m_playerCamera.getTransformation().scl().set(glm::vec3(screenSize.x, screenSize.y, screenSize.y));
}

AM::Camera &Player::getCamera() {
    return m_playerCamera;
}

void Player::update() {
    this->m_transformation = m_playerCamera.getTransformation();
    m_playerCamera.update();
}

