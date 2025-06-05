//
// Created by jensp on 17/05/2025.
//

#ifndef LITTLEGAME_OBJECT_H
#define LITTLEGAME_OBJECT_H
#include "entity.h"

namespace world {
    class object : public entity {
    protected:
        object(float x, float y);
    public:
        void timeUp(float time) override = 0;
        virtual int handleCollision(int id) override = 0;
    };
}

#endif //LITTLEGAME_OBJECT_H
