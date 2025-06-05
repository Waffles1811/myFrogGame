//
// Created by jensp on 4/06/2025.
//

#ifndef LITTLEGAME_BUTTON_H
#define LITTLEGAME_BUTTON_H
#include "viewEntity.h"
enum buttonType{
    save
};
namespace repr {
    class button : public viewEntity {
        buttonType type;
    public:
        button(std::string& type, std::string &folder, float scale);
        bool getClicked(float x, float y);
        buttonType getType();
        sf::Sprite getSprite(float xDimension, float yDimension, float time) override;

    };
}

#endif //LITTLEGAME_BUTTON_H
