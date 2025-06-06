#include "viewEntity.h"
#include <iostream>
#include <fstream>
#include <utility>

repr::viewEntity::viewEntity(std::string& _type, std::string& folder,
                             std::shared_ptr<concreteCamera> _camera, float _scale)
                                : type(_type), camera(std::move(_camera)), scale(_scale) {
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

void repr::viewEntity::initialize(std::shared_ptr<concreteAnimationObserver> _obs,
                                  std::shared_ptr<concreteOrientationObserver> orobs) {
    animationHandling = std::unique_ptr<repr::animationHandler>(
            new animationHandler(type, std::move(_obs), shared_from_this()));
    orientationObserver = orobs;
}

void repr::viewEntity::defaultTexture(){
    if (!texture->loadFromFile("assets/" +  type + "/" + type + "_default.png")) {
        throw std::runtime_error(
                type + " texture file failed to load.\nPlease ensure"
                        " assets/" +  type + "/" + type + "_default.png is present");
    }
    spriteRect.top = spriteRect.left = rightXOffset = yOffset = 0;
    spriteRect.width = texture->getSize().x;
    spriteRect.height = texture->getSize().y;
    sprite->setTextureRect(spriteRect);
    leftXOffset = spriteRect.width;
 }

sf::Sprite repr::viewEntity::getSprite(float xDimension, float yDimension, float time) {
    float x = camera->getXcoord(xDimension);
    float y = camera->getYcoord(yDimension);
    if (animationHandling) {
        animationHandling->updateAnimation(time);
    }
    if (orientationObserver) {
        if (orientationObserver->getDirection() != curDirection) {
            curDirection = orientationObserver->getDirection();
            sprite->scale(-1, 1);
        }
    }
    if (curDirection) {
        sprite->setPosition(x + leftXOffset * scale , y + yOffset * scale);
    } else {
        sprite->setPosition(x + rightXOffset * scale, y + yOffset * scale);
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


repr::animationHandler::animationHandler(std::string & type, std::shared_ptr<concreteAnimationObserver> _obs,
                                         const std::shared_ptr<viewEntity>& _sprite)
    : animationObserver(std::move(_obs)) {
    sprite = _sprite;
    inAnimation = repeatingAnimation = false;
    timeSinceLastFrame = 0.0;
    xOffset = curX = curY = curFrame = 0;
    std::ifstream file("assets/" + type + "/" + type +"_animations.JSON");
    animation_data = json::parse(file);
    curAnimation = animation::none;
}



void repr::animationHandler::updateAnimation(float time) {
    if (animationObserver) {
        animation newAnimation = animationObserver->getAnimation();
        if (newAnimation == animation::none){
            if (inAnimation){
                repeatingAnimation = false;
                if (curFrame > 1) {
                    continueAnimation(time);
                } else {
                    stopAnimation();
                }
            }
        } else if (newAnimation == curAnimation) {
            continueAnimation(time);
        } else {
            startAnimation(newAnimation);
        }
    }
}

void repr::animationHandler::startAnimation(animation type){
    std::string animationName;
    switch (type){
        case animation::jump:
            animationName = "jump";
            break;
        case animation::land:
            animationName = "land";
            break;
        case animation::fall:
            animationName = "fall";
            break;
        case animation::walk:
            animationName = "walk";
            break;
        case animation::none:
            animationName = "this isn't supposed to be reachable";
            break;
    }
    auto data = animation_data[animationName];
    std::string filename = data["file"];
    frameDurations.erase(frameDurations.begin(), frameDurations.end());
    frameDurations = data["frameDurations"].get<std::vector<float>>();
    curX = data["startXOffset"];
    curY = data["startYOffset"];
    xOffset = data["xOffset"];
    repeatingAnimation = data ["repeating"];
    curFrame = 0;
    inAnimation = true;
    sprite.lock()->setTexture(filename, xOffset, data["ySize"]);
    sprite.lock()->setTextureBox(curX, curY);
    sprite.lock()->setOffsets(data["LDisplayXOffset"], data["RDisplayXOffset"], data["displayYOffset"]);
    curAnimation = type;
    timeSinceLastFrame = 0;
}

void repr::animationHandler::continueAnimation(float time){
    if (not inAnimation){
        return;
    }
    time *= 1000;
    timeSinceLastFrame += time;
    if (timeSinceLastFrame > frameDurations[curFrame]){
        timeSinceLastFrame = 0.0;
        curFrame++;
        curX += xOffset;
        sprite.lock()->setTextureBox(curX, curY);
    } else if (curFrame > frameDurations.size()-1){
        if (repeatingAnimation){
            startAnimation(curAnimation);
        } else {
            stopAnimation();
        }
    }
}

void repr::animationHandler::stopAnimation() {
    sprite.lock()->defaultTexture();
    curAnimation = animation::none;
    animationObserver->stopAnimation();
    inAnimation = false;
}

