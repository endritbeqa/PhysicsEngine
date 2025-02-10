//
// Created by endrit on 06.12.24.
//

#ifndef PHYSICSENGINE_SOLVER_H
#define PHYSICSENGINE_SOLVER_H

class Solver {
public:
    template<typename object>
    void step(object &obj, double dt);

};


#endif //PHYSICSENGINE_SOLVER_H
