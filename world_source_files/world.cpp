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

void world::world::setup() {
    playerchar = factory->producePlayer();
    std::string type = "kevin";
    entities.push_back(factory->produceObject(type));
}

void world::world::processInputs(movement id) {
    playerchar->processInput(id);
}

