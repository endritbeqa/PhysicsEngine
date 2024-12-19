#include "include/core/objects/3D/RigitBody.h"

RigitBody::RigitBody() {}

RigitBody::RigitBody(Vector3 pos, Vector3 vel, double m): Object3(pos,vel,m) {}


RigitBody::Derivative RigitBody::calculateDerivative(RigitBody body) {
    Quaternion qOmega = Quaternion(0, body.angularVelocity);//omega symbol is used in physics to represent angular velocity
    return RigitBody::Derivative(
            body.velocity,
            qOmega*body.rotation,
            body.force,
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