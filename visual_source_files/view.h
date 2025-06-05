#ifndef LITTLEGAME_VIEW_H
#define LITTLEGAME_VIEW_H
#include "memory"
#include <map>
#include "viewEntity.h"
#include "button.h"
namespace repr {
    class view {
        std::vector<std::vector<std::shared_ptr<viewEntity>>> entities;
        std::vector<std::shared_ptr<button>> buttons;
    public:
        std::unique_ptr<sf::RenderWindow> window;

        view();
        void addEntity(std::shared_ptr<viewEntity>, int layer);
        void addButton(std::shared_ptr<button>);
        void makeFrame(float xDimension, float yDimension, float time);
        void reset();
    };
}

#endif //LITTLEGAME_VIEW_H
