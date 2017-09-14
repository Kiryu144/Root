/* Created by David Klostermann on 03.06.2017. */
#ifndef ROOT_BLOCK_H
#define ROOT_BLOCK_H

#include "voxel/voxel.h"

class Block {
private:
    Voxel m_voxel;

    const bool m_exists; //Equals to not being air
    const bool m_solid; //If completely fills its area
public:
    Block(); //Air
    Block(const Block& block);
    Block(Voxel voxel);

    Voxel getVoxel() const;
    void setVoxel(Voxel voxel);
    bool exists() const;
    bool isSolid() const;
};


#endif
