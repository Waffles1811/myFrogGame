#include "viewEntity.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <iostream>

repr::viewEntity::viewEntity(std::string& _type, std::shared_ptr<concreteCamera> _camera, float _scale)
                                : type(_type), camera(std::move(_camera)), scale(_scale) {
    texture = std::unique_ptr<sf::Texture>(new sf::Texture());
    if (!texture->loadFromFile("assets/" +  _type + "/" + _type + "_default.png")) {
        throw std::runtime_error(
                _type + " texture file failed to load.\nPlease ensure"
                                                     " assets/" +  _type + "/" + _type + "_default.png is present");
    }
    spriteRect = sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y);
    sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite(*texture, spriteRect));
    sprite->setScale(scale, scale);
    xOffset = yOffset = 0;
}

void repr::viewEntity::initialize(std::shared_ptr<concreteAnimationObserver> _obs) {
    animationHandling = std::unique_ptr<repr::animationHandler>(
            new animationHandler(type, std::move(_obs), shared_from_this()));

}

void repr::viewEntity::defaultTexture(){
    if (!texture->loadFromFile("assets/" +  type + "/" + type + "_default.png")) {
        throw std::runtime_error(
                type + " texture file failed to load.\nPlease ensure"
                        " assets/" +  type + "/" + type + "_default.png is present");
    }
    spriteRect.top = spriteRect.left = xOffset = yOffset = 0;
    spriteRect.width = texture->getSize().x;
    spriteRect.height = texture->getSize().y;
    sprite->setTextureRect(spriteRect);
}

sf::Sprite repr::viewEntity::getSprite(float xDimension, float yDimension, float time) {
    float x = camera->getXcoord(xDimension);
    float y = camera->getYcoord(yDimension);
    if (animationHandling) {
        animationHandling->updateAnimation(time);
    }
    sprite->setPosition(x + xOffset * scale, y + yOffset * scale);
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

void repr::viewEntity::setOffsets(int _xOffset, int _yOffset) {
    xOffset = _xOffset;
    yOffset = _yOffset;
}


repr::animationHandler::animationHandler(std::string & type, std::shared_ptr<concreteAnimationObserver> _obs,
                                         const std::shared_ptr<viewEntity>& _sprite)
    : animationObserver(std::move(_obs)) {
    sprite = _sprite;
    inAnimation = false;
    timeSinceLastFrame = 0.0;
    xOffset = curX = curY = curFrame = 0;
    visualXOffset = visualYOffsets = {};
    std::ifstream file("assets/" + type + "/" + type +"_animations.JSON");
    animation_data = json::parse(file);
}



void repr::animationHandler::updateAnimation(float time) {
    if (animationObserver) {
        animation newAnimation = animationObserver->getAnimation();
        if (newAnimation == animation::none) {
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
        case animation::none:
            animationName = "this isn't supposed to be reachable";
            break;
    }
    auto data = animation_data[animationName];
    std::string filename = data["file"];
    frameDurations.erase(frameDurations.begin(), frameDurations.end());
    frameDurations = data["frameDurations"].get<std::vector<float>>();
    visualXOffset = data["displayXOffset"];
    visualYOffsets = data["displayYOffset"];
    curX = data["startXOffset"];
    curY = data["startYOffset"];
    xOffset = data["xOffset"];
    curFrame = 0;
    inAnimation = true;
    sprite.lock()->setTexture(filename, xOffset, 16);
    sprite.lock()->setTextureBox(curX, curY);
    sprite.lock()->setOffsets(visualXOffset, visualYOffsets);
}

void repr::animationHandler::continueAnimation(float time){
    if (not inAnimation){
        return;
    }
    time *= 1000;
    if (curFrame > frameDurations.size()-1){
        stopAnimation();
    }
    if (timeSinceLastFrame > frameDurations[curFrame]){
        timeSinceLastFrame = 0.0;
        curFrame++;
        curX += xOffset;
        sprite.lock()->setTextureBox(curX, curY);
    } else {
        timeSinceLastFrame += time;
    }
}

void repr::animationHandler::stopAnimation() {
    sprite.lock()->defaultTexture();
    inAnimation = false;
}

