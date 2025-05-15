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
        switch (result) {
            case 0:
                if (playerchar->getYCoord()>-600) {
                    playerchar->fall();
                }
                playerchar->noWall();
                break;
            case 1: // from above
                playerchar->land(i->getYCoord()+60.1);
                break;
            case 2: // from below
                break;
            case 3: // left (off player)
                playerchar->hitWall(i->getXCoord() + i->getHitbox()->length, true);
                break;
            case 4: // right (off player)
                playerchar->hitWall(i->getXCoord()-playerchar->getHitbox()->length, false);
                break;
            case 5:
                playerchar->die();
            default:
                break;
        }
    }
}

void world::world::setup() {
    playerchar = factory->producePlayer();
    std::string type = "kevin";
    entities.push_back(factory->produceObject(type));
}

// vv movement related functions
void world::world::goLeft(){playerchar->goLeft();}
void world::world::goRight(){playerchar->goRight();}
void world::world::stopLeft(){playerchar->stopLeft();}
void world::world::stopRight(){playerchar->stopRight();}
void world::world::faceUp(){playerchar->faceUp();}
void world::world::faceDown(){playerchar->faceDown();}
void world::world::stopUp(){playerchar->stopUp();}
void world::world::stopDown(){playerchar->stopDown();}
void world::world::jump(){playerchar->jump();}
void world::world::dash(){playerchar->dash();}
void world::world::clingToWall(){playerchar->clingToWall();}
void world::world::releaseWall(){playerchar->releaseWall();}
