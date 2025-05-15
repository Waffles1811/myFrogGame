//
// Created by peasant 1 on 7/05/2025.
//

#include "entity.h"

#include <utility>

world::entity::entity(std::shared_ptr<world::rectHitbox> _hitbox, float _x, float _y) : hitbox(std::move(_hitbox)), x(_x), y(_y){}
world::entity::entity(float _x, float _y) : x(_x), y(_y){}

void world::entity::setpCam(std::shared_ptr<entitycamera> newCam){
    positionCamera = std::move(newCam);
}

float world::entity::getXCoord() const {
    return x;
}
float world::entity::getYCoord() const {
    return y;
}

std::shared_ptr<world::rectHitbox> world::entity::getHitbox() {
    return hitbox;
}

void world::entity::setXCoord(float _x) {
    x = _x;
}
void world::entity::setYCoord(float _y) {
    y = _y;
}
