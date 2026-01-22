//
// Created by jensp on 4/06/2025.
//

#include "levelEditor.h"

#include <cmath>
#include <bits/stdc++.h>
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

std::pair<float, float> world::levelEditor::processRClick(float x, float y, int layer) {
    for (int j = 0; j < entities.size() ; j++){
        auto i = entities[j];
        if (i->getLayer() <= layer and i->getHitbox()->getLeftX() < x and i->getHitbox()->getRightX() > x and
        i->getHitbox()->getUpY() > y and i->getHitbox()->getDownY() < y){
            entities.erase(entities.begin() + j);
            return {i->getHitbox()->length, i->getHitbox()->height};
        }
    }
    return {0, 0};
}

