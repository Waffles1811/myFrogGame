#include "hitbox.h"
void world::hitbox::setX(float _x) {
    x = _x;
}
void world::hitbox::setY(float _y){
    y = _y;
}

world::rectHitbox::rectHitbox(float _length, float _height, bool _killsYou)
    : hitbox(), length(_length), height(_height), killsYou(_killsYou) {}

int world::rectHitbox::detectCollision(world::rectHitbox& otherBox, float xDif, float yDif) {
    if (getLeftX() - otherBox.getRightX() < 0 and getRightX() - otherBox.getLeftX() > 0
        and getDownY()-yDif > otherBox.getUpY() - 0.25 and otherBox.getUpY() + 0.25 > getDownY()) {
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
