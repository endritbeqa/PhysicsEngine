#ifndef PHYSICSENGINE_DRAG_H
#define PHYSICSENGINE_DRAG_H

#include "Force.h"

class DragForce : public Force{
public:
    double Cd;

    DragForce(double x);

    void apply() override;
};

#endif //PHYSICSENGINE_DRAG_H
