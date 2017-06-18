/* Created by David Klostermann on 03.06.2017. */
#include "block.h"

Block::Block() : m_exists(false), m_solid(false) {

}

Block::Block(const Block &block) : m_exists(block.exists()), m_solid(block.isSolid()) {
    m_voxel = block.getVoxel();
}

Block::Block(Voxel voxel)  : m_exists(true), m_solid(true) {
    m_voxel = voxel;
}

Voxel Block::getVoxel() const {
    return m_voxel;
}

void Block::setVoxel(Voxel voxel) {
    m_voxel = voxel;
}

bool Block::exists() const {
    return m_exists;
}

bool Block::isSolid() const {
    return m_solid;
}



