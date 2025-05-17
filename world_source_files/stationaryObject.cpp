//
// Created by Sansa on 13/05/2025.
//

#include "stationaryObject.h"

void world::stationaryObject::timeUp(float time) {
    positionCamera->updateCoords(x, y);
}

world::stationaryObject::stationaryObject(std::string _type, float xCoord, float yCoord,
                                          float hitboxXCoord, float hitboxYCoord) : entity(xCoord, yCoord)  {
    hitbox = std::make_shared<world::rectHitbox>(hitboxXCoord, hitboxYCoord, false);
    hitbox->setX(xCoord);
    hitbox->setY(yCoord);
}
