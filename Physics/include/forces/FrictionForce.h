//
// Created by endrit on 12.11.24.
//

#ifndef PHYSICSENGINE_FRICTIONFORCE_H
#define PHYSICSENGINE_FRICTIONFORCE_H

#include "Force.h"


class FrictionForce : public Force{
public:
    double mu;

    FrictionForce(double frictionCoefficient);

    void apply() override;


};

#endif //PHYSICSENGINE_FRICTIONFORCE_H
