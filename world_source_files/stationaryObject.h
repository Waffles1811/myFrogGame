#ifndef LITTLEGAME_STATIONARYOBJECT_H
#define LITTLEGAME_STATIONARYOBJECT_H

#include "object.h"
namespace world {
    class stationaryObject : public object{ // meant to be a wall or floor
    public:
        stationaryObject(std::string _type, float xCoord, float YCoord, float hitboxXCoord, float hitboxYCoord);
        void timeUp(float time) override;
        int handleCollision(int id) override;
    };
}
#endif //LITTLEGAME_STATIONARYOBJECT_H
