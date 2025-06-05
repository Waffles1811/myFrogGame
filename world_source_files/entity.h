//
// Created by peasant 2 on 7/05/2025.
//

#ifndef LITTLEGAME_ENTITY_H
#define LITTLEGAME_ENTITY_H
#include <memory>
#include <vector>
#include <string>
#include "../json.hpp"
#include "entitycamera.h"
#include "hitbox.h"
using json = nlohmann::json;
class saveFileObject;

enum objectID : int32_t {
    player,
    kevin,
    rockWall
};

namespace world {
    class entity {
    protected:
        float x;
        float y;
        objectID type;
        std::shared_ptr<entitycamera> positionCamera;
        std::shared_ptr<world::rectHitbox> hitbox;

    public:
        entity(std::shared_ptr<world::rectHitbox> _hitbox, float _x, float _y);
        entity(float _x, float _y);
        float getXCoord() const;
        float getYCoord() const;
        objectID getID() const;
        void setXCoord(float _x);
        void setYCoord(float _y);
        std::shared_ptr<world::rectHitbox> getHitbox();
        void setpCam(std::shared_ptr<entitycamera> newCam);
        virtual void timeUp(float time) = 0;
        virtual int handleCollision(int id);
        void toSaveFileObject(std::vector<saveFileObject>&);
    };
}

class saveFileObject {
private:
    float x, y, scale;
    int id, layer;
public:
    saveFileObject(float, float, float, int, int);
    saveFileObject(float, float, float, int, objectID);
    saveFileObject(float, float, int);
    saveFileObject(float, float, objectID);
    saveFileObject() = default;

    float getX() const;
    float getY() const;
    float getScale() const;
    int getId() const;
    int getLayer() const;
    int objectIDToInt(objectID);
};

#endif //LITTLEGAME_ENTITY_H
