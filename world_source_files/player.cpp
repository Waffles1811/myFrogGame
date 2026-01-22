//
// Created by Jon Snow on 11/05/2025.
//

#include "player.h"
#include <cmath>
#include <iostream>
#include <utility>
enum player_physics{ // divide things by 100.0 if they have "time" in their name bc no floats allowed
    walkSpeed = 400,
    walkAcceleration = 900,
    walkSlowdown = 1500,
    jumpSpeed = 500,
    jumpTime = 25,
    jumpingGravity = 600,
    downwardsGravity = 1500,
    dashSpeed = 700,
};

world::player::player() : entity(0, 0) {
    hitbox = std::make_shared<world::rectHitbox>(55, 35, 0, 0, false);
    type = objectID::player;
}

world::player::player(float x, float y) : entity(x, y) {
    hitbox = std::make_shared<world::rectHitbox>(55, 35, 0, 0, false);
    type = objectID::player;
}

void world::player::initialize(){
    std::weak_ptr<player> this_pointer = shared_from_this();
    movement = std::make_shared<playerMovement>(this_pointer);
    inputHandling = std::make_shared<inputHandler>(movement);
    collisionFixer = std::make_shared<collisionHandler>(movement, this_pointer, x, y);
    animationHandling = std::make_shared<animationHandler>();
}

void world::player::timeUp(float time) {
    movement->timeUp(time);

    hitbox->setX(x);
    hitbox->setY(y);
}

void world::player::processInput(enum movement input) {
    inputHandling->processInput(input);
}

void world::player::handleCollision(int id, const std::shared_ptr<entity>& hitObject) {
    collisionFixer->handleCollision(id, hitObject);
}

void world::player::reset() {
    movement->reset();
}

void world::player::setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                       std::shared_ptr<world::orientationObserver> _orientobserver) {
    animationHandling->setAnimationCameras(_animobserver, _orientobserver);
}

const std::shared_ptr<world::animationHandler> &world::player::getAnimationHandling() const {
    return animationHandling;
}

void world::player::fall() {
    movement->fall();
}

void world::player::releaseWall(){
    movement->noWall();
}


void world::inputHandler::processInput(enum movement input) {
    switch (input){
        case movement::moveRight:
            movement.lock()->goRight();
            break;
        case movement::faceDown:
            movement.lock()->faceDown();
            break;
        case movement::moveLeft:
            movement.lock()->goLeft();
            break;
        case movement::faceUp:
            movement.lock()->faceUp();
            break;
        case movement::jump:
            movement.lock()->jump();
            break;
        case movement::stopJump:
            movement.lock()->stopJump();
            break;
        case movement::dash:
            movement.lock()->dash();
            break;
        case movement::wallCling:
            movement.lock()->clingToWall();
            break;

        case movement::stopRight:
            movement.lock()->stopRight();
            break;
        case movement::stopDown:
            movement.lock()->stopDown();
            break;
        case movement::stopLeft:
            movement.lock()->stopLeft();
            break;
        case movement::stopUp:
            movement.lock()->stopUp();
            break;
        case movement::stopCling:
            movement.lock()->releaseWall();
            break;
    }
}

world::inputHandler::inputHandler(std::weak_ptr<playerMovement> _movement) : movement(_movement) {}

void world::playerMovement::timeUp(float time) {
    if (not grounded and not (wallClinging and touchingWall)){
        if (jumping) {
            ySpeed -= jumpingGravity * time;
        } else {
            if (ySpeed < 0.0f) {
                player_entity.lock()->getAnimationHandling()->processAnimation("fall");
            }
            ySpeed -= downwardsGravity * time;
        }
    } else if ((goingRight or goingLeft) and grounded and not (wallClinging and touchingWall)){
            player_entity.lock()->getAnimationHandling()->processAnimation("walk");
        }
    
    if (grounded){
        wallClingTime = 3.0f;
        if (not inDash){
            canDash = true;
        }
    }

    if (goingLeft and xSpeed > -walkSpeed){
        xSpeed -= walkAcceleration * time;
        if (xSpeed > 0.0f){
            xSpeed -= 0.5f * walkSlowdown *time;
        }
    }
    else if (goingRight and xSpeed < walkSpeed){
        xSpeed += walkAcceleration * time;
        if (xSpeed < 0.0f){
            xSpeed += 0.5f * walkSlowdown * time;
        }
    }
    else if (not goingLeft and xSpeed < -100.0f){
        xSpeed += walkSlowdown * time;
    }
    else if (not goingRight and xSpeed > 100.0f){
        xSpeed -= walkSlowdown * time;
    }
    else if (xSpeed < 100.0f and xSpeed > -100.0f){
        xSpeed = 0.0f;
    }

    if (jumping){
        //ySpeed = jumpSpeed;
        jumpingTime -= time;
        if (jumpingTime < 0.0f){
            jumping = false;
        }
    }

    if (inDash){
        xSpeed = dashSpeed * cos(-dashDirection/4.0f*3.14159f);
        ySpeed = dashSpeed * sin(-dashDirection/4.0f*3.14159f);
        dashTime -= time;
        if (dashTime < 0.0f){
            endDash();
        }
    }

    if (coyoteTime>0.0f){
        coyoteTime -= time;
    }

    if (jumpBufferTime > 0.0f){
        jumpBufferTime -= time;
    }

    if (wallClinging and touchingWall){
        xSpeed = 0.0f;
        if (facingUp){
            player_entity.lock()->getAnimationHandling()->processAnimation("wall_walk");
            ySpeed = 200.0f;
            grounded = false;
        } else if (facingDown and not grounded){
            ySpeed = -200.0f;
        } else{
            ySpeed = 0.0f;
        }
        wallClingTime -= time;
        if (wallClingTime < 0.0f){
            wallClinging = false;
        }
    }
    player_entity.lock()->getAnimationHandling()->timeUp(time);
    player_entity.lock()->setCoords( player_entity.lock()->getXCoord() + time * xSpeed,
                                     player_entity.lock()->getYCoord() + time * ySpeed);
}

void world::playerMovement::goLeft() {
    if (not (wallClinging and touchingWall)){
        goingLeft = true;
        goingRight = false;
        facingLeft = true;
        player_entity.lock()->getAnimationHandling()->turn(true);
    }
}

void world::playerMovement::goRight(){
    if (not (wallClinging and touchingWall)){
        goingLeft = false;
        goingRight = true;
        facingLeft = false;
        player_entity.lock()->getAnimationHandling()->turn(false);
    }
}

void world::playerMovement::stopLeft(){
    goingLeft = false;
    if (grounded) {
        player_entity.lock()->getAnimationHandling()->processAnimation("default");
    }
}

void world::playerMovement::stopRight(){
    goingRight = false;
    if (grounded) {
        player_entity.lock()->getAnimationHandling()->processAnimation("default");
    }
}

void world::playerMovement::boinkHead() {
    ySpeed = 0;
    inDash = false;
}

void world::playerMovement::hitWall(float length, bool left) {
    if ((left and not goingRight) or (not left and not goingLeft)){
        xSpeed = 0;
        touchingWall = true;
        player_entity.lock()->setXCoord(length);
        if (wallClinging){
            player_entity.lock()->getHitbox()->changeDimensions(23.0f*2.5f, 16.0f*2.5f);
        }
    } else if ((left and not facingLeft) or (not left and facingLeft)){
        touchingWall = false;
    } 
    if ((left and inDash and  2 < dashDirection and 5 > dashDirection) or (not left and inDash and (dashDirection == 7 or dashDirection == 0 or dashDirection == 1))){
        inDash = false;
    }
}

void world::playerMovement::noWall() {
    touchingWall = false;
    if (wallClinging){
        player_entity.lock()->getHitbox()->changeDimensions(23.0f*2.5f, 16.0f*2.5f);
    }
}

void world::playerMovement::clingToWall() {
    if (wallClingTime > 0) {
        wallClinging = true;
        player_entity.lock()->getHitbox()->changeDimensions(16.0f * 2.5f, 23.0f * 2.5f);
        if (touchingWall){
            if (grounded){
                    player_entity.lock()->getAnimationHandling()->processAnimation("touch_wall");
                    player_entity.lock()->getAnimationHandling()->setAnimationBlock(0.350);
                    player_entity.lock()->setCoords( player_entity.lock()->getXCoord(),
                            player_entity.lock()->getYCoord() + 7.0f*2.5f);  //player moves up a bit for hitbox
            }
            player_entity.lock()->getHitbox()->changeDimensions(16.0f * 2.5f, 23.0f * 2.5f);
            player_entity.lock()->getAnimationHandling()->newDefaultAnim("default_wall_cling");
            player_entity.lock()->getAnimationHandling()->processAnimation("default_wall_cling");
        }
    }
}

void world::playerMovement::releaseWall() {
    wallClinging = false;
    player_entity.lock()->getAnimationHandling()->newDefaultAnim("default");
    if (touchingWall){
        player_entity.lock()->getHitbox()->changeDimensions(23.0f*2.5f, 16.0f*2.5f);
    }
}

void world::playerMovement::faceUp(){
    facingUp = true;
}

void world::playerMovement::faceDown(){
    facingDown = true;
}

void world::playerMovement::stopUp(){
    if (wallClinging and touchingWall){
        player_entity.lock()->getAnimationHandling()->processAnimation("default_wall_cling");
    }
    facingUp = false;
    
}

void world::playerMovement::stopDown(){
    facingDown = false;
}

void world::playerMovement::jump(){
    if (grounded or coyoteTime>0){
        jumping = true;
        jumpingTime = (float) jumpTime/100.0;
        grounded = false;
        ySpeed = jumpSpeed;
        player_entity.lock()->getAnimationHandling()->processAnimation("jump");
    } else {
        jumpBufferTime = 0.1;
    }
}

void world::playerMovement::stopJump() {
    jumping = false;
}

void world::playerMovement::land(float height) {
    if (ySpeed < 0) {
        if (jumpBufferTime > 0){
            player_entity.lock()->setYCoord(height+1);
            ySpeed = 0;
            grounded = true;
            jump();
        }
        else {
            if (not grounded) {
                ySpeed = 0;
                grounded = true;
                canDash = true;
                player_entity.lock()->setYCoord(height + 0.1);
                player_entity.lock()->getAnimationHandling()->processAnimation("land");
            }
        }
    }
    if (inDash){
        if (dashDirection == 2){
            inDash = false;
        } else if (dashDirection == 1){
            dashDirection = 0;
        } else if (dashDirection == 3){
            dashDirection = 4;
        }
    }
}

void world::playerMovement::fall() {
    if (grounded){
        grounded = false;
        coyoteTime = 0.1;
    }
}

void world::playerMovement::dash(){
    if (not canDash){
        return;
    }
    jumping = false;
    canDash = false;
    inDash = true;
    dashTime = 0.3;
    if (facingUp){
        grounded = false;
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

void world::playerMovement::endDash(){
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

world::playerMovement::playerMovement(std::weak_ptr<player> _player_entity) : player_entity(_player_entity) {
    grounded = goingLeft = goingRight = facingUp = facingDown = canDash = inDash = wallClinging = jumping = touchingWall = false;
    dashTime = wallClingTime = coyoteTime = jumpingTime = xSpeed = ySpeed = 0.0;
    dashDirection = 0.0;
}

void world::playerMovement::reset() {
    grounded = goingLeft = goingRight = facingUp = facingDown = canDash = inDash = wallClinging = touchingWall = false;
    dashTime = wallClingTime = coyoteTime = 0.0;
    dashDirection = 0.0;
}


void world::collisionHandler::handleCollision(int id, const std::shared_ptr<entity>& hitObject) {
    id = hitObject->handleCollision(id); // for object that allow you to go through them or sum
    switch (id) {
        case 0:
            //movement.lock()->fall();
            //movement.lock()->noWall();
            break;
        case 1: // from above
            movement.lock()->land(hitObject->getHitbox()->getUpY() + player_entity.lock()->getHitbox()->height);
            break;
        case 2: // from below
            movement.lock()->boinkHead();
            break;
        case 3: // left (off player)
            movement.lock()->hitWall(hitObject->getHitbox()->getRightX(), true);
            break;
        case 4: // right (off player)
            movement.lock()->hitWall(hitObject->getHitbox()->getLeftX()
                                     - player_entity.lock()->getHitbox()->length, false);
            break;
        case 5:
            respawn();
            break;
        default:
            break;
    }
}

world::collisionHandler::collisionHandler(std::weak_ptr<playerMovement> _movement, std::weak_ptr<player> _player_entity
        , float _xRespawnPoint, float _yRespawnPoint) : movement(std::move(_movement)),
            player_entity(std::move(_player_entity)), xRespawnPoint(_xRespawnPoint), yRespawnPoint(_yRespawnPoint){}

void world::collisionHandler::respawn() {
    player_entity.lock()->setXCoord(xRespawnPoint);
    player_entity.lock()->setYCoord(yRespawnPoint);
    player_entity.lock()->reset();
}


void world::animationHandler::timeUp(float time){
    blockNewAnimationTimer -= time;
}


void world::animationHandler::processAnimation(std::string animation) {
    if (blockNewAnimationTimer < 0){
        observer->startAnimation(animation);
    }
}

void world::animationHandler::setAnimationCameras(std::shared_ptr<world::animationObserver> _observer,
                                                  std::shared_ptr<world::orientationObserver> _obs) {
    observer = _observer;
    orientationObserver = _obs;
}

world::animationHandler::animationHandler() : blockNewAnimationTimer(-1) {}

void world::animationHandler::turn(bool direction) {
    orientationObserver->turn(direction);
}

void world::animationHandler::setAnimationBlock(float time){
    blockNewAnimationTimer = time;
}

void world::animationHandler::newDefaultAnim(std::string name){
    observer->changeDefaultAnimation(name);
}
