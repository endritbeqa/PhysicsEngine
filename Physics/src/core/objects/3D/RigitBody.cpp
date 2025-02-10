#include "Physics/include/core/objects/3D/RigitBody.h"

RigitBody::RigitBody() = default;

RigitBody::RigitBody(Vector3 pos, Vector3 vel, double m): Object3(pos,vel,m) {}


RigitBody::Derivative RigitBody::calculateDerivative() {
    Quaternion qOmega = Quaternion(0, angularVelocity);//omega symbol is used in physics to represent angular velocity
    return RigitBody::Derivative(
            velocity,
            qOmega*rotation,
            forceAccum,
            torque);
}


RigitBody::Derivative RigitBody::calculateDerivative(RigitBody body) {
    Quaternion qOmega = Quaternion(0, body.angularVelocity);//omega symbol is used in physics to represent angular velocity
    return RigitBody::Derivative(
            body.velocity,
            qOmega*body.rotation,
            body.forceAccum,
            body.torque);
}

void RigitBody::updateState(RigitBody::Derivative d) {
    position = position + d.velocity;
    rotation = rotation + d.quaternionDerivative;
    linearMomentum = linearMomentum + d.force;
    angularMomentum = angularMomentum + d.torque;

    velocity = linearMomentum / mass;
    Matrix3 qMatrix = rotation.toMatrix();
    Matrix3 qMatrixTranspose = qMatrix.transpose();
    Iinverse = qMatrix*IBodyInv*qMatrixTranspose;
    angularVelocity = IBodyInv * angularMomentum;
}


RigitBody RigitBody::calculateState(RigitBody::Derivative d) {
    RigitBody body = *this;
    body.position = body.position + d.velocity;
    body.rotation = body.rotation + d.quaternionDerivative;
    body.linearMomentum = body.linearMomentum + d.force;
    body.angularMomentum = body.angularMomentum + d.torque;

    body.velocity = body.linearMomentum / body.mass;
    Matrix3 qMatrix = body.rotation.toMatrix();
    Matrix3 qMatrixTranspose = qMatrix.transpose();
    Iinverse = qMatrix*body.IBodyInv*qMatrixTranspose;
    body.angularVelocity = body.IBodyInv * body.angularMomentum;

    return body;
}