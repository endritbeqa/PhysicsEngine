//
// Created by endrit on 12.11.24.
//

#include "Physics/include/forces/DragForce.h"

DragForce::DragForce(double x) {
    type = Unary;
    Cd = x;
}

void DragForce::apply() {

}