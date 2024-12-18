//
// Created by endrit on 15.12.24.
//

#ifndef PHYSICSENGINE_RIDGITBODY_H
#define PHYSICSENGINE_RIDGITBODY_H

#include <vector>
#include "include/math/Matrix3.h"
#include "include/math/Quaternion.h"
#include "Particle.h"

class RidgitBody{
public:

    double mass;

    Matrix3 IBody;
    Matrix3 IBodyInv;

    Vector3 translation;
    Matrix3 rotation;
    //Quaternion rotation;

    Vector3 linearMomentum;
    Vector3 angularMomentum;

    Matrix3 Iinverse;
    Vector3 linearVelocity;
    Vector3 angularVelocity;

    Vector3 force;
    Vector3 torque;

    RidgitBody();

    struct Derivative{
    public:

        Vector3 velocity;
        Matrix3 rotationDerivative;
        Vector3 force;
        Vector3 torque;



        Derivative operator+(const Derivative&& d){
            return Derivative();
        }

        Derivative operator*(const Derivative&& d){
            return Derivative();
        }

        Derivative operator+(const Derivative& d){
            return Derivative(
                    velocity+d.velocity,
                    rotationDerivative*d.rotationDerivative,
                    force+d.force,
                    torque+d.torque
                    );
        }

        Derivative operator*(const Derivative& d){
            return Derivative();
        }

        Derivative operator*(double d){
            return Derivative();
        }

    };

    RidgitBody::Derivative calculateDerivative(RidgitBody body);
    void updateState(Derivative d);
    RidgitBody calculateState(Derivative d);

};


#endif //PHYSICSENGINE_RIDGITBODY_H
