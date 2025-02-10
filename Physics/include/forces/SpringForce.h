//
// Created by endrit on 12.11.24.
//

#ifndef PHYSICSENGINE_SPRING_H
#define PHYSICSENGINE_SPRING_H

#include "Force.h"

class SpringForce : public Force{
public:
    double springConstant;
    double dampeningConstant;
    double length;

    SpringForce();
    SpringForce(double springConstant,double dampeningConstant, double length);

    void add_objects(std::shared_ptr<Object3> obj1, std::shared_ptr<Object3> obj2);
    void apply();
    void apply(Object3 &obj1, Object3& obj2);
};




#endif //PHYSICSENGINE_SPRING_H
