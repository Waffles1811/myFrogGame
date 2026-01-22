//
// Created by jensp on 4/06/2025.
//

#ifndef LITTLEGAME_LEVELEDITOR_H
#define LITTLEGAME_LEVELEDITOR_H
#include "world.h"
namespace world {
    class levelEditor : public world::world{
    public:
        levelEditor(std::shared_ptr<abstractFactory>);
        std::shared_ptr<entity> processClick(float x, float y, int layer, float scale);
        std::pair<float, float> processRClick(float x, float y, int layer);
    };
}


#endif //LITTLEGAME_LEVELEDITOR_H
