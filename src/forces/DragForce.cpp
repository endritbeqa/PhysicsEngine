//
// Created by endrit on 12.11.24.
//

#include "include/forces/DragForce.h"

DragForce::DragForce(float x) {
    type = Unary;
    Cd = x;
}

void DragForce::apply() {

}