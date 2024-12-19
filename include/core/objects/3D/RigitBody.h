#ifndef PHYSICSENGINE_RIGITBODY_H
#define PHYSICSENGINE_RIGITBODY_H

#include <vector>
#include "include/math/Matrix3.h"
#include "include/math/Quaternion.h"
#include "Object3.h"

class RigitBody : public Object3{
public:

    RigitBody();

    RigitBody(Vector3 pos, Vector3 vel, double m);

    Matrix3 IBody;
    Matrix3 IBodyInv;
    Quaternion rotation;
    Vector3 linearMomentum;
    Vector3 angularMomentum;
    Matrix3 Iinverse;
    Vector3 angularVelocity;
    //TODO look if i need to use this for touque and other stuff and what to use forceAccum of object for
    Vector3 force;
    Vector3 torque;

    struct Derivative{
    public:

        Vector3 velocity;
        Quaternion quaternionDerivative;
        Vector3 force;
        Vector3 torque;

        Derivative operator+(const Derivative& d){
            return Derivative(
                    velocity+d.velocity,
                    quaternionDerivative+d.quaternionDerivative,
                    force+d.force,
                    torque+d.torque
                    );
        }


        Derivative operator*(double d){
            return Derivative(
                    velocity*d,
                    quaternionDerivative*d,
                    force*d,
                    torque*d
            );
        }

    };

    RigitBody::Derivative calculateDerivative();
    RigitBody::Derivative calculateDerivative(RigitBody body);
    void updateState(Derivative d);
    RigitBody calculateState(Derivative d);

};


#endif //PHYSICSENGINE_RIGITBODY_H
