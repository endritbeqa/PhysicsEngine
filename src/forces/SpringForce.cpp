//
// Created by endrit on 12.11.24.
//

#include "include/forces/SpringForce.h"

SpringForce::SpringForce(){
    type = N_ary;
    springConstant = 1.0;
    dampeningConstant = 0.3;
    length = 1.0;
};
SpringForce::SpringForce(float ks, float kd, float l){
    type = N_ary;
    springConstant = ks;
    dampeningConstant =kd;
    length = l;
};


void SpringForce::add_objects(std::shared_ptr<Object3> obj1, std::shared_ptr<Object3> obj2) {
    objects.push_back(obj1);
    objects.push_back(obj2);
}

void SpringForce::apply() {
    Vector3 l = objects[0]->position - objects[1]->position;
    Vector3 l_dt = objects[0]->velocity - objects[0]->velocity;
    float l_norm = l.norm();

    float coeff = -(springConstant * (l_norm - length) + (dampeningConstant * l_dt.dot(l)) / l_norm);
    Vector3 fa = l * (coeff / l_norm);

    objects[0]->forceAccum = objects[0]->forceAccum + fa;
    objects[1]->forceAccum = objects[1]->forceAccum - fa;
}




void SpringForce::apply(Object3 &obj1, Object3 &obj2) {
    Vector3 l = obj1.position - obj2.position;
    Vector3 l_dt = obj1.velocity - obj2.velocity;
    float l_norm = l.norm();

    float coeff  =-(springConstant*(l_norm-length) + (dampeningConstant*l_dt.dot(l))/l_norm);
    Vector3 fa = l*(coeff/l_norm);
    obj1.forceAccum = obj1.forceAccum + fa;
    obj2.forceAccum = obj2.forceAccum - fa;
}



