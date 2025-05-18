#include "view.h"
using namespace repr;
view::view() : window(std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1200, 900),
                                                                             "celeste"))){
    window->setVerticalSyncEnabled(true);

}

void view::makeframe(float xDimension, float yDimension) {
    for(auto & entity : entities){
        window->draw(entity->getSprite(xDimension, yDimension)); // draws sprites
    }
    window->display(); // ends frame
    window->clear();   // clears window for next frame (internally, not on screen)
}

void view::addentity(std::shared_ptr<viewEntity> _entity) {
    entities.push_back(_entity);
}
