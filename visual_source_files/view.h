#ifndef LITTLEGAME_VIEW_H
#define LITTLEGAME_VIEW_H
#include "memory"
#include <map>
#include "viewEntity.h"
#include "button.h"
namespace repr {
    class view {
        std::vector<std::vector<std::weak_ptr<viewEntity>>> entities;
        std::vector<std::weak_ptr<button>> buttons;
    public:
        std::unique_ptr<sf::RenderWindow> window;

        view();
        void addEntity(std::weak_ptr<viewEntity>, int layer);
        void addButton(std::weak_ptr<button>);
        void makeFrame(float xDimension, float yDimension, float time);
        void reset();
    };
}

#endif //LITTLEGAME_VIEW_H
