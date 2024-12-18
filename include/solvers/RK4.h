#ifndef PHYSICSENGINE_RK4_H
#define PHYSICSENGINE_RK4_H

#include <functional>
#include <memory>

class RK4{
public:
    RK4(){}

    template<typename state>
    void step(std::shared_ptr<state> obj, double dt) {

        typename state::Derivative k1 = obj->calculateDerivative() ;
        state y1 = obj->calculateState(k1 * (0.5 * dt));
        typename state::Derivative k2 = y1.calculateDerivative();
        state y2 = obj->calculateState(k2 * (0.5 * dt));
        typename state::Derivative k3 = y2.calculateDerivative();
        state y3 = obj->calculateState(k3 * dt);
        typename state::Derivative k4 = y3.calculateDerivative() ;

        typename state::Derivative step = (k1 + k2 * 2 + k3 * 2 + k4) * (dt / 6.0);

        obj->updateState(step);



        /*typename state::Derivative a = obj->calculateDerivative(*obj)*dt;
        typename state::Derivative b = obj->calculateDerivative(obj->calculateState(a * (0.5 * dt)))*(0.5 * dt);
        typename state::Derivative c = obj->calculateDerivative(obj->calculateState(b * (0.5 * dt)))*(0.5 * dt);
        typename state::Derivative d = obj->calculateDerivative(obj->calculateState(c * dt)) * dt;
        typename state::Derivative step = (a + b * 2 + c * 2 + d) * (1.0 / 6.0);

        obj->updateState(step);
    */

    }

};

#endif //PHYSICSENGINE_RK4_H
