//
// Created by jensp on 4/06/2025.
//

#include "button.h"

repr::button::button(std::string &_type, std::string &folder, float scale) : viewEntity(_type, folder, nullptr, scale) {
    if (_type == "saveButton"){
        type = buttonType::save;
    }
}

bool repr::button::getClicked(float x, float y) {
    if (sprite->getPosition().x < x and sprite->getPosition().x + spriteRect.width > x
    and sprite->getPosition().y < y and sprite->getPosition().y + spriteRect.height > y){
        return true;
    }
    return false;
}

buttonType repr::button::getType() {
    return type;
}


sf::Sprite repr::button::getSprite(float xDimension, float yDimension, float time) {
    return *sprite;
}


