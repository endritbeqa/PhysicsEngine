//
// Created by endrit on 05.12.24.
//

#ifndef PHYSICSENGINE_EULER_H
#define PHYSICSENGINE_EULER_H

#include "memory"

class Euler{
public:

    Euler(){}

    template<typename object>
    void step(std::shared_ptr<object> obj, double dt) {
        typename object::Derivative step = obj->calculateDerivative(*obj)*dt;
        obj->updateState(step);
    }
};

#endif //PHYSICSENGINE_EULER_H
