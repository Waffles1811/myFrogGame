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


animation repr::concreteAnimationObserver::getAnimation() {
    if (changed){
        changed = false;
        return curAnimation;
    }
    else {
        return animation::none;
    }
}

void repr::concreteAnimationObserver::startAnimation(animation newAnimation) {
    if (curAnimation != newAnimation){
        curAnimation = newAnimation;
        changed = true;
    }
}

repr::concreteAnimationObserver::concreteAnimationObserver() {
    curAnimation = animation::none;
    changed = false;
}
