#ifndef PHYSICSENGINE_FORCE_H
#define PHYSICSENGINE_FORCE_H

#include <memory>
#include "math/include/Vector3.h"
#include "Physics/include/core/objects/3D/Object3.h"
#include "vector"

enum ForceType{
    Unary,
    N_ary,
    Spatial_Interaction
};

class Force {
public:
    ForceType type;
    std::vector<std::shared_ptr<Object3>> objects;

    Force(){};
    virtual ~Force() {};
    virtual void apply()=0;
};


#endif //PHYSICSENGINE_FORCE_H
