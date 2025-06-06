#include "hitbox.h"
void world::hitbox::setX(float _x) {
    x = _x+xOffset;
}
void world::hitbox::setY(float _y){
    y = _y+yOffset;
}

world::hitbox::hitbox(float _xOffset, float _yOffset) : x(0), y(0), xOffset(_xOffset), yOffset(_yOffset) {}

world::rectHitbox::rectHitbox(float _length, float _height, float _x_offset, float _y_offset, bool _killsYou)
    : hitbox(_x_offset, _y_offset), length(_length), height(_height), killsYou(_killsYou) {}

int world::rectHitbox::detectCollision(world::rectHitbox& otherBox, float xDif, float yDif) {
    // beneath player
    point point1 = point(getLeftX()+0.1*length, getDownY()-0.25);
    point point2 = point(getRightX()-0.1*length, getDownY()-0.25);
    if (point1.checkInHitbox(otherBox) or point2.checkInHitbox(otherBox)){
        if (killsYou){
            return 5;
        } else {
            return 1;
        }
    }
    //above player
    point1 = point(getLeftX()+0.1*length, getUpY()+0.25);
    point2 = point(getRightX()-0.1*length, getUpY()+0.25);
    if (point1.checkInHitbox(otherBox) or point2.checkInHitbox(otherBox)){
        if (killsYou){
            return 5;
        } else {
            return 2;
        }
    }
    // left of player
    point1 = point(getLeftX()-0.25, getUpY());
    point2 = point(getLeftX()-0.25, getDownY());
    if (point1.checkInHitbox(otherBox) or point2.checkInHitbox(otherBox)){
        if (killsYou){
            return 5;
        } else {
            return 3;
        }
    }
    // right of player
    point1 = point(getRightX()+0.25, getUpY());
    point2 = point(getRightX()+0.25, getDownY());
    if (point1.checkInHitbox(otherBox) or point2.checkInHitbox(otherBox)){
        if (killsYou){
            return 5;
        } else {
            return 4;
        }
    }

    return 0;
}

float world::rectHitbox::getLeftX(){
    return x;
}
float world::rectHitbox::getRightX(){
    return x + length;
}
float world::rectHitbox::getUpY(){
    return y;
}
float world::rectHitbox::getDownY(){
    return y - height;
}

world::point::point(float _x, float _y) : x(_x), y(_y) {}

bool world::point::checkInHitbox(world::rectHitbox & hitbox) {
    if (x > hitbox.getLeftX() and x < hitbox.getRightX() and y < hitbox.getUpY() and y > hitbox.getDownY()){
        return true;
    } else {
        return false;
    }
}
