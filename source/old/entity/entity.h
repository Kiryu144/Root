/* Created by David Klostermann on 24.06.2017. */
#ifndef ROOT_IENTITY_H
#define ROOT_IENTITY_H

#include <amethyst>

class Entity{
protected:
    AM::Transformation m_transformation;
public:
    AM::Transformation& getTransformation();

};

#endif
