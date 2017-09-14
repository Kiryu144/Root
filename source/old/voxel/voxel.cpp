/* Created by David Klostermann on 03.06.2017. */
#include "voxel.h"

Voxel::Voxel() {
    m_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
}

Voxel::Voxel(glm::tvec4<float> color) {
    m_color = color;
}

void Voxel::setColor(glm::tvec4<float> color) {
    m_color = color;
}

glm::tvec4<float> Voxel::getColor() const {
    return m_color;
}
