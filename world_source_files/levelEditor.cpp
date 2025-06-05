//
// Created by jensp on 4/06/2025.
//

#include "levelEditor.h"

#include <cmath>
world::levelEditor::levelEditor(std::shared_ptr<abstractFactory> factory) : world(std::move(factory)){}

std::shared_ptr<world::entity> world::levelEditor::processClick(float x, float y, int layer, float scale) {
    // should add a wall in nearest slot
    float roundedX = floorf(x/50)*50; // rounds down to multiple of 50
    float roundedY = -floorf(y/50)*50; // rounds down to multiple of 50
    bool alreadyPresent = false;
    for (auto i : entities){
        if (roundedX == i->getXCoord() and roundedY == i->getYCoord()){
            alreadyPresent = true;
        }
    }
    if (not alreadyPresent){
        std::string type = "rockWall";
        entities.push_back(factory->produceWall(type, roundedX, roundedY, layer, scale));
        return entities.back();
    } else {
        return nullptr;
    }
}
