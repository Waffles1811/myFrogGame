//
// Created by peasant 2 on 7/05/2025.
//

#ifndef LITTLEGAME_ENTITY_H
#define LITTLEGAME_ENTITY_H
#include <memory>
#include <vector>
#include <string>
#include "entitycamera.h"
#include "hitbox.h"
namespace world {
    class entity {
    protected:
        float x;
        float y;
        std::shared_ptr<entitycamera> positionCamera;
        std::shared_ptr<world::rectHitbox> hitbox;

    public:
        entity(std::shared_ptr<world::rectHitbox> _hitbox, float _x, float _y);
        entity(float _x, float _y);
        float getXCoord() const;
        float getYCoord() const;
        void setXCoord(float _x);
        void setYCoord(float _y);
        std::shared_ptr<world::rectHitbox> getHitbox();
        void setpCam(std::shared_ptr<entitycamera> newCam);
        virtual void timeUp(float time) = 0;

    };
}

#endif //LITTLEGAME_ENTITY_H
