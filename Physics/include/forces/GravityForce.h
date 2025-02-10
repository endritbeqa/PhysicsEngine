//
// Created by endrit on 12.11.24.
//

#ifndef PHYSICSENGINE_GRAVITYFORCE_H
#define PHYSICSENGINE_GRAVITYFORCE_H

#include "Force.h"

class GravityForce : public Force{
public:
    Vector3 direction;

    GravityForce();
    GravityForce(Vector3 direction);
    void apply() override;

};


#endif //PHYSICSENGINE_GRAVITYFORCE_H
