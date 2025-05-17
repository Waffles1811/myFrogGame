#include "viewEntity.h"
#include <iostream>
sf::Sprite repr::viewEntity::getSprite(float xDimension, float Ydimension) {
    float x = camera->getXcoord(xDimension);
    float y = camera->getYcoord(Ydimension);
    sprite->setPosition(x, y);
    return *sprite;
}

repr::viewEntity::viewEntity(std::string& _type, std::shared_ptr<concreteCamera> _camera, float scale)
                                : type(_type), camera(_camera) {
    texture = std::unique_ptr<sf::Texture>(new sf::Texture());
    if (!texture->loadFromFile("assets/" +  _type + "/" + _type + "_default.png")) {
        throw std::runtime_error(
                _type + " texture file failed to load.\nPlease ensure"
                                                     " assets/" +  _type + "/" + _type + "_default.png is present");
    }
    sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite(*texture));
    sprite->setScale(scale, scale);
}
