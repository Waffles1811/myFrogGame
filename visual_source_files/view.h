#ifndef LITTLEGAME_VIEW_H
#define LITTLEGAME_VIEW_H
#include "memory"
#include <map>
#include "viewEntity.h"
namespace repr {
    class view {
        std::vector<std::shared_ptr<viewEntity>> entities;
    public:
        std::unique_ptr<sf::RenderWindow> window;


        view();
        void addentity(std::shared_ptr<viewEntity>);
        void makeframe(float xDimension, float yDimension);
    };
}

#endif //LITTLEGAME_VIEW_H
