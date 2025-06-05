//
// Created by Westeros on 7/05/2025.
//

#include "world.h"

#include <utility>
world::world::world(std::shared_ptr<abstractFactory> _factory) : factory(std::move(_factory)) {}

void world::world::time_up(float time) {
    for (auto & i : entities){
        i->timeUp(time);
    }
    float oldPlayerX = playerchar->getXCoord();
    float oldPlayerY = playerchar->getYCoord();
    playerchar->timeUp(time);
    for (auto & i : entities){
        int result = playerchar->getHitbox()->detectCollision(*i->getHitbox(), playerchar->getXCoord() - oldPlayerX,
                                                                                  playerchar->getYCoord() - oldPlayerY);
        playerchar->handleCollision(result, i);
    }
}

void world::world::processInputs(movement id) {
    playerchar->processInput(id);
}

void world::world::loadRoom(std::vector<saveFileObject> objects) {
    entities.clear();
    std::string type;
    for (auto i : objects){
        switch (i.getId()) {
            case objectID::player:
                if (playerchar) {
                    playerchar->setXCoord(i.getX());
                    playerchar->setYCoord(i.getY());
                } else {
                    playerchar = factory->producePlayer(i.getX(), i.getY(), i.getLayer(), i.getScale());
                }
                break;
            case objectID::kevin:
                type = "kevin";
                entities.push_back(factory->produceObject(type, i.getX(), i.getY(), i.getLayer(), i.getScale()));
                break;
            case objectID::rockWall:
                type = "rockWall";
                entities.push_back(factory->produceWall(type, i.getX(), i.getY(), i.getLayer(), i.getScale()));
                break;
        }
    }
    if (not playerchar){
        playerchar = factory->producePlayer(0, 0, 9, 2.5);
    }
}


