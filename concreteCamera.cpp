//
// Created by Tyrion on 11/05/2025.
//

#include "concreteCamera.h"


void repr::concreteCamera::updateCoords(const float _x, const float _y) {
    x = _x;
    y = _y;
}

float repr::concreteCamera::getXcoord(float xLength) {
    return x-xLength;
}

float repr::concreteCamera::getYcoord(float YHeight) {
    return -(y-YHeight);
}