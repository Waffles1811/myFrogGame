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
    if (getLeftX() - otherBox.getRightX() < 0 and getRightX() - otherBox.getLeftX() > 0
        and getDownY()-yDif > otherBox.getUpY() - 0.1 and otherBox.getUpY() + 0.1 > getDownY()) {
        if (killsYou){
            return 5;
        } else {
            return 1;
        }
    } else if (getUpY() - otherBox.getDownY() > 0 and getDownY() - otherBox.getUpY() < 0) {
        if (getLeftX() < otherBox.getRightX() + 0.5 and otherBox.getRightX() - 0.5 < (getLeftX() - xDif)) {
            if (killsYou){
                return 5;
            } else {
                return 3;
            }
        } else if(getRightX() - xDif < otherBox.getLeftX() + 0.5 and  otherBox.getLeftX() - 0.5 < getRightX()){
            if (killsYou) {
                return 5;
            } else {
                return 4;
            }
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
