#include "view.h"
using namespace repr;
view::view() : window(std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1920, 1080),
                                                                             "froggie jumping", sf::Style::Fullscreen))), entities(11){
    window->setVerticalSyncEnabled(true);
}

void view::makeFrame(float xDimension, float yDimension, float time) {
    for(auto & layerVector : entities){
        for (auto & entity : layerVector) {
            window->draw(entity->getSprite(xDimension, yDimension, time)); // draws sprites
        }
    }
    for (auto & button : buttons){
        window->draw(button->getSprite(xDimension, yDimension, time)); // draws sprites
    }

    window->display(); // ends frame
    window->clear();   // clears window for next frame (internally, not on screen)
}

void view::addEntity(std::shared_ptr<viewEntity> _entity, int layer) {
    entities[layer].push_back(_entity);
}

void view::addButton(std::shared_ptr<button> newButton) {
    buttons.push_back(newButton);
}

void view::reset() {
    entities.clear();
    buttons.clear();
    for (int index = 0; index <= 10 ; index++){
        entities.push_back({});
    }
}
