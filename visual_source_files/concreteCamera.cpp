//
// Created by Tyrion on 11/05/2025.
//

#include "concreteCamera.h"


void repr::concreteCamera::updateCoords(const float _x, const float _y) {
    model->updatePosition(_x, -_y);
}

repr::concreteCamera::concreteCamera(std::shared_ptr<viewEntity> _model) : model(_model) {}


void repr::concreteAnimationObserver::startAnimation(std::string newAnimation) {
    if (curAnimation != newAnimation){
        std::cout << newAnimation << std::endl;
        model->startAnimation(newAnimation);
        curAnimation = newAnimation;
    }
}

repr::concreteAnimationObserver::concreteAnimationObserver(std::shared_ptr<viewEntity> _model) : model(_model) {
    curAnimation == "default";
}

void repr::concreteAnimationObserver::stopAnimation() {
    curAnimation == "default";
    model->startAnimation(curAnimation);
}

void repr::concreteOrientationObserver::turn(bool direction) {
    if (facingLeft != direction){
        model->changeOrientation();
        facingLeft = direction;
    }
}

repr::concreteOrientationObserver::concreteOrientationObserver(std::shared_ptr<viewEntity> _model) : model(_model) {
    facingLeft = false;
}

bool repr::concreteOrientationObserver::getDirection() {
    return facingLeft;
}
