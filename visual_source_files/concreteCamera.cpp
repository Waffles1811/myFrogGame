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
    return curAnimation;
}

void repr::concreteAnimationObserver::startAnimation(animation newAnimation) {
    if (curAnimation != newAnimation){
        curAnimation = newAnimation;
    }
}

repr::concreteAnimationObserver::concreteAnimationObserver() {
    curAnimation = animation::none;
}

void repr::concreteAnimationObserver::stopAnimation() {
    curAnimation = animation::none;
}

void repr::concreteOrientationObserver::turn(bool direction) {
    facingLeft = direction;
}

repr::concreteOrientationObserver::concreteOrientationObserver() {
    facingLeft = false;
}

bool repr::concreteOrientationObserver::getDirection() {
    return facingLeft;
}
