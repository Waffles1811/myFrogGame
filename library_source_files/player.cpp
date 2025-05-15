//
// Created by Jon Snow on 11/05/2025.
//

#include "player.h"
#include <cmath>
#include <iostream>
enum player_consts{
    walkSpeed = 400,
    walkAcceleration = 700,
    walkSlowdown = 1500,
    jumpSpeed = 450,
    gravity = 1000,
    dashSpeed = 700
};

world::player::player() : entity(0, 0) {
    hitbox = std::make_shared<world::rectHitbox>(48.7, 60.1, false);
    xSpeed = ySpeed = dashTime = dashDirection = 0;
    grounded = goingRight = goingLeft = inDash = facingUp = facingDown = false;
    canDash = true;
}

void world::player::timeUp(float time) {
    if (not grounded){
        ySpeed -= gravity * time;
    }
    if (goingLeft and xSpeed > -walkSpeed){
        xSpeed -= walkAcceleration * time;
    }
    else if (goingRight and xSpeed < walkSpeed){
        xSpeed += walkAcceleration * time;
    }
    if (not goingLeft and xSpeed < -0.01){
        xSpeed += walkSlowdown * time;
    }
    else if (not goingRight and xSpeed > 0.01){
        xSpeed -= walkSlowdown * time;
    }
    if (xSpeed < 0.1 and xSpeed > -0.1){
        xSpeed = 0;
    }
    if (inDash){
        xSpeed = dashSpeed * cos(-dashDirection/4.0*3.14159);
        ySpeed = dashSpeed * sin(-dashDirection/4.0*3.14159);
        grounded = false;
        dashTime -= time;
        if (dashTime < 0){
            endDash();
        }
    }

    if (wallClinging and touchingWall){
        xSpeed = 0;
        if (facingUp){
            ySpeed = 200;
        } else if (facingDown){
            ySpeed = -200;
        } else{
            ySpeed = 0;
        }
        wallClingTime -= time;
        if (wallClingTime < 0){
            wallClinging = false;
        }
    }

    x += time * xSpeed;
    y += time * ySpeed;

    hitbox->setX(x);
    hitbox->setY(y);

    if (y < -600){ // hard coded to float at bottom of screen for now
        land(-600);
    }
    positionCamera->updateCoords(x, y);
}

void world::player::die() {
    return; // add respawning later
}

void world::player::goLeft() {
    goingLeft = true;
    goingRight = false;

}

void world::player::goRight(){
    goingLeft = false;
    goingRight = true;

}

void world::player::stopLeft(){
    goingLeft = false;
}

void world::player::stopRight(){
    goingRight = false;
}

void world::player::hitWall(float length, bool left) {
    if (left and not goingRight){
        xSpeed = 0;
        touchingWall = true;
        x = length;
    } else if (not left and not goingLeft){
        xSpeed = 0;
        touchingWall = true;
        x = length;
    }
}

void world::player::noWall() {
    touchingWall = false;
}

void world::player::clingToWall() {
    if (wallClingTime > 0) {
        wallClinging = true;
    }
}

void world::player::releaseWall() {
    wallClinging = false;
}

void world::player::faceUp(){
    facingUp = true;
}

void world::player::faceDown(){
    facingDown = true;
}

void world::player::stopUp(){
    facingUp = false;
}

void world::player::stopDown(){
    facingDown = false;
}

void world::player::jump(){
    if (grounded){
        ySpeed += jumpSpeed;
    }
    grounded = false;
}

void world::player::land(float height) {
    if (ySpeed < 0) {
        y = height;
        ySpeed = 0;
        grounded = true;
        canDash = true;
        wallClingTime = 3;
    }
}

void world::player::fall() {
    grounded = false;
}

void world::player::dash(){
    if (not canDash){
        return;
    }
    canDash = false;
    grounded = false;
    inDash = true;
    dashTime = 0.3;
    if (facingUp){
        if (goingLeft){
            dashDirection = 5.0;
        }
        else if (goingRight){
            dashDirection = 7.0;
        }
        else {
            dashDirection = 6.0;
        }
    }
    else if (facingDown){
        if (goingLeft){
            dashDirection = 3.0;
        }
        else if (goingRight){
            dashDirection = 1.0;
        }
        else {
            dashDirection = 2.0;
        }
    }
    else if (goingRight){
        dashDirection = 0.0;
    }
    else{
        dashDirection = 4.0;
    }
}

void world::player::endDash(){
    inDash = false;
    if (ySpeed > 0){
        ySpeed = 300;
    }
    if (goingRight and xSpeed > 1){
        xSpeed = 400;
    }
    else if (goingLeft and xSpeed < -1){
        xSpeed = -400;
    }
    else if (xSpeed > 1){
        xSpeed = 150;
    }
    else if (xSpeed < -1){
        xSpeed = -150;
    }
}


