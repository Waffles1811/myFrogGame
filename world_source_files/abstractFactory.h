//
// Created by Azor Ahai on 11/05/2025.
//

#ifndef LITTLEGAME_ABSTRACTFACTORY_H
#define LITTLEGAME_ABSTRACTFACTORY_H
#include "player.h"
#include "stationaryObject.h"
namespace world {
    class abstractFactory {
    public:
        virtual entity *produceEntity() = 0;

        virtual std::shared_ptr<player> producePlayer(float x, float y, int layer, float scale) = 0;
        virtual std::shared_ptr<stationaryObject> produceObject(std::string& type, float x, float y, int layer, float scale) = 0;
        virtual std::shared_ptr<stationaryObject> produceWall(std::string& type, float x, float y, int layer, float scale) = 0;

    };
}

#endif //LITTLEGAME_ABSTRACTFACTORY_H
