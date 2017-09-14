/* Created by David Klostermann on 03.06.2017. */
#ifndef ROOT_VOXEL_H
#define ROOT_VOXEL_H

#include <GLM/common.hpp>

class Voxel {
private:
    glm::tvec4<float> m_color;
public:
    Voxel();
    Voxel(glm::tvec4<float> color);

    void setColor(glm::tvec4<float> color);
    glm::tvec4<float> getColor() const;
};


#endif
