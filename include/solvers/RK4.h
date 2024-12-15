#ifndef PHYSICSENGINE_RK4_H
#define PHYSICSENGINE_RK4_H

#include <functional>
#include <memory>

class RK4{
public:
    RK4(){}

    template<typename object>
    void step(std::shared_ptr<object> obj, double t, double dt) {

        typename object::Derivative a = obj->calculateDerivative(*obj, dt);
        typename object::Derivative b = obj->calculateDerivative(obj->calculateState(a * (0.5 * dt)), 0.5 * dt);
        typename object::Derivative c = obj->calculateDerivative(obj->calculateState(b * (0.5 * dt)), 0.5 * dt);
        typename object::Derivative d = obj->calculateDerivative(obj->calculateState(c * dt),   dt);
        typename object::Derivative step = (a + b*2 + c*2 +d)*(1.0/6.0);

        obj->updateState(step);
    }

};

#endif //PHYSICSENGINE_RK4_H
