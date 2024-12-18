


#include "include/core/objects/3D/RidgitBody.h"

RidgitBody::Derivative RidgitBody::calculateDerivative(RidgitBody body) {
    return RidgitBody::Derivative(
            body.linearVelocity,
            ToCrossMatrix(body.angularMomentum)*body.rotation,
            body.force,
            body.torque);
}