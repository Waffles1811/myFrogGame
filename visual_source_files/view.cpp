#include "view.h"
using namespace repr;
view::view() : entities(11){
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(
            sf::VideoMode(desktop.width, desktop.height),
            "Game",
            sf::Style::None));
    window->setPosition(sf::Vector2i(0, 0));  // snap to screen corner

    window->setVerticalSyncEnabled(true);
}

void view::makeFrame(float xDimension, float yDimension, float time) {
    for(auto & layerVector : entities){
        for (int entity = 0 ; entity < layerVector.size() ; entity++) {
            if (layerVector[entity].lock()){
                window->draw(layerVector[entity].lock()->getSprite(xDimension, yDimension, time)); // draws sprites
            } else {
                layerVector.erase(layerVector.begin() + entity);
            }
        }
    }
    for (int button = 0 ; button < buttons.size() ; button++) {
        if (buttons[button].lock()){
            window->draw(buttons[button].lock()->getSprite(xDimension, yDimension, time)); // draws sprites
        } else {
            buttons.erase(buttons.begin() + button);
        }
    } 

    window->display(); // ends frame
    window->clear();   // clears window for next frame (internally, not on screen)
}

void view::addEntity(std::weak_ptr<viewEntity> _entity, int layer) {
    entities[layer].push_back(_entity);
}

void view::addButton(std::weak_ptr<button> newButton) {
    buttons.push_back(newButton);
}

void view::reset() {
    entities.clear();
    buttons.clear();
    for (int index = 0; index <= 10 ; index++){
        entities.push_back({});
    }
}
