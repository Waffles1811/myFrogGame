#include "viewEntity.h"
#include <iostream>
#include <fstream>
#include <utility>

repr::viewEntity::viewEntity(std::string& _type, std::string& folder, float _scale)
                                : type(_type), scale(_scale) {
    texture = std::unique_ptr<sf::Texture>(new sf::Texture());
    if (!texture->loadFromFile("assets/" +  folder + "/" + _type + "_default.png")) {
        throw std::runtime_error(
                _type + " texture file failed to load.\nPlease ensure"
                                                     " assets/" +  folder + "/" + _type + "_default.png is present");
    }
    spriteRect = sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y);
    sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite(*texture, spriteRect));
    sprite->setScale(scale, scale);
    leftXOffset = rightXOffset = yOffset = 0;
    curDirection = false;
}

sf::Sprite repr::viewEntity::getSprite(float xDimension, float yDimension, float time) {
    if (animationHandling) {
        animationHandling->updateAnimation(time);
    }
    calcLocation();
    return *sprite;
}

void repr::viewEntity::setTextureBox(int newX, int newY) {
    spriteRect.left=newX;
    spriteRect.top=newY;
    sprite->setTextureRect(spriteRect);
}

void repr::viewEntity::setTexture(std::string &_texture, float newLength, float newHeight) {
    std::string fileName = "assets/" + type + "/" + _texture;
    if (!texture->loadFromFile(fileName)) {
        throw std::runtime_error(type + " texture file failed to load.\nPlease ensure " + fileName + " is present");
    }
    spriteRect.width = newLength;
    spriteRect.height = newHeight;
    sprite->setTextureRect(spriteRect);
}

void repr::viewEntity::setOffsets(int _leftXOffset, int _rightXOffset, int _yOffset) {
    leftXOffset = spriteRect.width - _leftXOffset;
    rightXOffset = _rightXOffset;
    yOffset = _yOffset;
}

void repr::viewEntity::changeOrientation(){
    if (curDirection) {
        sprite->setPosition(sprite->getPosition().x + rightXOffset * scale, sprite->getPosition().y + yOffset * scale);
    } else {
        sprite->setPosition(sprite->getPosition().x + leftXOffset * scale , sprite->getPosition().y + yOffset * scale);
    }
    sprite->scale(-1, 1);
    curDirection = !curDirection;
}

void repr::viewEntity::updatePosition(float newX, float newY){
    x = newX;
    y = newY;
}

void repr::viewEntity::startAnimation(std::string anim) {
    animationHandling->startAnimation(anim);
}

void repr::viewEntity::initialiseAnimations(std::shared_ptr<animationLibrary> _library) {
    animationHandling = std::make_unique<animationHandler>(type, shared_from_this(), _library);

}

void repr::viewEntity::setNewDefaultAnim(std::string newDefaultAnim){
    animationHandling->setNewDefault(newDefaultAnim);
}

void repr::viewEntity::calcLocation(){
    if (curDirection) {
        sprite->setPosition(x + leftXOffset * scale , y + yOffset * scale);
    } else {
        sprite->setPosition(x + rightXOffset * scale, y + yOffset * scale);
    }
}

repr::animationHandler::animationHandler(std::string & _type, const std::shared_ptr<viewEntity> _sprite,
                                         std::shared_ptr<animationLibrary> _library) : library(_library), wallAnimations(false), defaultAnim("default"){
    sprite = _sprite;
    repeatingAnimation = false;
    timeSinceLastFrame = 0.0;
    xOffset = curX = curY = curFrame = 0;
    curAnimation = "default";
    type = _type;
    frameDurations = {1000000};
}



void repr::animationHandler::updateAnimation(float time) { 
    continueAnimation(time);
}


void repr::animationHandler::startAnimation(std::string animType){
    auto data = library->getAnimation(type, animType);
    std::string filename = data["file"]; // file with the spritesheet
    frameDurations.erase(frameDurations.begin(), frameDurations.end());
    frameDurations = data["frameDurations"].get<std::vector<float>>(); // how long every frame should stay on screen
    curX = data["startXOffset"]; // where in the spritesheet the animation starts, frame (from zero) * frame width (for horizontal spritesheet)
    curY = data["startYOffset"]; // where in the spritesheet the animation starts, frame (from zero) * frame height (for vertical spritesheet)
    xOffset = data["xOffset"]; // width of one frame
    repeatingAnimation = data["repeating"]; // wether or not the animation should repeat when finished
    curFrame = 0;
    sprite.lock()->setTexture(filename, xOffset, data["ySize"]); // ySize is how high the sprite is
    sprite.lock()->setTextureBox(curX, curY);
    sprite.lock()->setOffsets(data["LDisplayXOffset"], data["RDisplayXOffset"], data["displayYOffset"]);
    // some animations have some extra space somewhere because the thing is moving around, sprite is kept in correct position by these
    // LDisplay if for if thing is facing left and RDisplay is for facing right
    timeSinceLastFrame = 0;
    curAnimation = animType;
}

void repr::animationHandler::continueAnimation(float time){
    time *= 1000;
    timeSinceLastFrame += time;
    if (timeSinceLastFrame > frameDurations[curFrame]){ // after a while we go to next frame
        timeSinceLastFrame = 0.0;
        curFrame++;
        curX += xOffset;
        sprite.lock()->setTextureBox(curX, curY);
    }
    if (curFrame > frameDurations.size()-1){ // if last frame has passed
        if (repeatingAnimation){
            curX -= curFrame * xOffset;
            curFrame = 0;
            sprite.lock()->setTextureBox(curX, curY);
        } else {
            stopAnimation();
        }
    }
}

void repr::animationHandler::stopAnimation() {
    defaultTexture();
}

void repr::animationHandler::setNewDefault(std::string newDefaultAnim){
    if (curAnimation == defaultAnim){
        defaultAnim = newDefaultAnim;
        startAnimation(defaultAnim);
    } else {
        defaultAnim = newDefaultAnim;
    }
}


void repr::animationHandler::defaultTexture(){
    /*
    if (!texture->loadFromFile("assets/" +  type + "/" + type + "_default.png")) {
        throw std::runtime_error(
                type + " texture file failed to load.\nPlease ensure"
                        " assets/" +  type + "/" + type + "_default.png is present");
    }
    spriteRect.width = texture->getSize().x;
    if (curDirection) {
        sprite->setPosition(sprite->getPosition().x - (leftXOffset-spriteRect.width) * scale, sprite->getPosition().y - yOffset * scale);
    } else {
        sprite->setPosition(sprite->getPosition().x - rightXOffset * scale, sprite->getPosition().y - yOffset * scale);

    }
    spriteRect.top = spriteRect.left = rightXOffset = yOffset = 0;
    spriteRect.height = texture->getSize().y;
    sprite->setTextureRect(spriteRect);
    leftXOffset = spriteRect.width;
    */
   startAnimation(defaultAnim);
}