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

void repr::viewEntity::defaultTexture(){
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
 }

sf::Sprite repr::viewEntity::getSprite(float xDimension, float yDimension, float time) {
    if (animationHandling) {
        animationHandling->updateAnimation(time);
    }
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
        sprite->setPosition(sprite->getPosition().x + rightXOffset * scale, sprite->getPosition().y);
    } else {
        sprite->setPosition(sprite->getPosition().x + leftXOffset * scale , sprite->getPosition().y);
    }
    sprite->scale(-1, 1);
    curDirection = !curDirection;
}

void repr::viewEntity::updatePosition(float newX, float newY){
    if (curDirection) {
        sprite->setPosition(newX + leftXOffset * scale , newY + yOffset * scale);
    } else {
        sprite->setPosition(newX + rightXOffset * scale, newY + yOffset * scale);
    }
}

void repr::viewEntity::startAnimation(std::string anim) {
    animationHandling->startAnimation(anim);
}

void repr::viewEntity::initialiseAnimations(std::shared_ptr<animationLibrary> _library) {
    animationHandling = std::make_unique<animationHandler>(type, shared_from_this(), _library);

}

repr::animationHandler::animationHandler(std::string & _type, const std::shared_ptr<viewEntity> _sprite,
                                         std::shared_ptr<animationLibrary> _library) : library(_library){
    sprite = _sprite;
    inAnimation = repeatingAnimation = false;
    timeSinceLastFrame = 0.0;
    xOffset = curX = curY = curFrame = 0;
    curAnimation = "default";
    type = _type;
}



void repr::animationHandler::updateAnimation(float time) {
    if (curAnimation == "default"){ // if the animation should end we'll complete it first (unless if another animation has been started)
        if (inAnimation){
            repeatingAnimation = false;
            if (curFrame > 1) {
                continueAnimation(time);
            } else {
                stopAnimation();
            }
        }
    } else {
        if (inAnimation) {
            continueAnimation(time);
        }
    }
}


void repr::animationHandler::startAnimation(std::string animType){
    if (animType != "fall" and animType != "land" and animType != "walk" and animType != "jump"){
        curAnimation = animType;
    }
    else {
        auto data = library->getAnimation(type, animType);
        std::string filename = data["file"];
        frameDurations.erase(frameDurations.begin(), frameDurations.end());
        frameDurations = data["frameDurations"].get<std::vector<float>>();
        curX = data["startXOffset"];
        curY = data["startYOffset"];
        xOffset = data["xOffset"];
        repeatingAnimation = data["repeating"];
        curFrame = 0;
        inAnimation = true;
        sprite.lock()->setTexture(filename, xOffset, data["ySize"]);
        sprite.lock()->setTextureBox(curX, curY);
        sprite.lock()->setOffsets(data["LDisplayXOffset"], data["RDisplayXOffset"], data["displayYOffset"]);
        curAnimation = animType;
        timeSinceLastFrame = 0;
    }
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
            startAnimation(curAnimation);
        } else {
            stopAnimation();
        }
    }
}

void repr::animationHandler::stopAnimation() {
    sprite.lock()->defaultTexture();
    inAnimation = false;
}

