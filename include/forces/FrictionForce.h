//
// Created by endrit on 12.11.24.
//

#ifndef PHYSICSENGINE_FRICTIONFORCE_H
#define PHYSICSENGINE_FRICTIONFORCE_H

#include "include/math/Vector3.h"
#include "Force.h"


class FrictionForce : public Force{
public:
    float mu;

    FrictionForce(float frictionCoefficient);

    void apply() override;


};

#endif //PHYSICSENGINE_FRICTIONFORCE_H