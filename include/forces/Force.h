//
// Created by endrit on 11.11.24.
//

#ifndef PHYSICSENGINE_FORCE_H
#define PHYSICSENGINE_FORCE_H

#include "../math/Vector3.h"
#include "../core/Object3.h"

class Force {
public:
    virtual ~Force() = default;

    // Calculate the force vector given the state of the object
    virtual Vector3 calculate(const Object3& object, float time) const = 0;
};


#endif //PHYSICSENGINE_FORCE_H
