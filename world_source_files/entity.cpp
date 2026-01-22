//
// Created by peasant 1 on 7/05/2025.
//

#include "entity.h"

#include <utility>

world::entity::entity(std::shared_ptr<world::rectHitbox> _hitbox, float _x, float _y)
        : hitbox(std::move(_hitbox)), x(_x), y(_y){}
world::entity::entity(float _x, float _y) : x(_x), y(_y){}

void world::entity::setpCam(std::shared_ptr<entitycamera> newCam, int _layer){
    positionCamera = std::move(newCam);
    positionCamera->updateCoords(x, y);
    layer = _layer;
}

float world::entity::getXCoord() const {
    return x;
}
float world::entity::getYCoord() const {
    return y;
}

objectID world::entity::getID() const {
    return type;
}

std::shared_ptr<world::rectHitbox> world::entity::getHitbox() {
    return hitbox;
}

void world::entity::setXCoord(float _x) {
    x = _x;
    if (positionCamera){
        positionCamera->updateCoords(x, y);
    }
}
void world::entity::setYCoord(float _y) {
    y = _y;
    if (positionCamera){
        positionCamera->updateCoords(x, y);
    }
}

void world::entity::setCoords(float _x, float _y){
    x = _x;
    y = _y;
    if (positionCamera){
        positionCamera->updateCoords(x, y);
    }
}

int world::entity::handleCollision(int id) {
    return id;
}

int world::entity::getLayer() const {
    return layer;
}


saveFileObject::saveFileObject(float _x, float _y, float _scale, int _layer, int _id)
        : x(_x), y(_y), scale(_scale), layer(_layer), id(_id){}

saveFileObject::saveFileObject(float _x, float _y, int _id) :  x(_x), y(_y), scale(1), layer(0), id(_id){}

saveFileObject::saveFileObject(float _x, float _y, objectID _id) :  x(_x), y(_y), scale(1), layer(0), id(objectIDToInt(_id)) {}

saveFileObject::saveFileObject(float _x, float _y, float _scale, int _layer, objectID _id)
        : x(_x), y(_y), scale(_scale), layer(_layer), id(objectIDToInt(_id)) {}

float saveFileObject::getX() const {
    return x;
}

float saveFileObject::getY() const {
    return y;
}

float saveFileObject::getScale() const {
    return scale;
}

int saveFileObject::getId() const {
    return id;
}

int saveFileObject::getLayer() const {
    return layer;
}

int saveFileObject::objectIDToInt(objectID id) {
    switch (id) {
        case objectID::player:
            return 0;
        case objectID::kevin:
            return 1;
        case objectID::rockWall:
            return 2;
        default:
            return -1;
    }
}


