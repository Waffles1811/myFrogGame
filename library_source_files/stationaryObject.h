#ifndef LITTLEGAME_STATIONARYOBJECT_H
#define LITTLEGAME_STATIONARYOBJECT_H
#include "entity.h"
namespace world {
    class stationaryObject : public entity{ // meant to be a wall or floor
        std::string type;
    public:
        stationaryObject(std::string _type, float xCoord, float YCoord, float hitboxXCoord, float hitboxYCoord);
        void timeUp(float time) override;
    };
}
#endif //LITTLEGAME_STATIONARYOBJECT_H
