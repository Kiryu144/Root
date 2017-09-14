/* Created by David Klostermann on 14.06.2017. */
#ifndef ROOT_IBLOCKACCESSIBLE_H
#define ROOT_IBLOCKACCESSIBLE_H

#include "world/block/block.h"
#include <GLM/common.hpp>


class IBlockAccessible {
public:
    virtual Block getBlock(glm::vec3 position) = 0;
    virtual void setBlock(glm::vec3 position, Block block) = 0;
    virtual bool blockExists(glm::vec3 position) = 0;
};

#endif
