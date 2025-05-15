//
// Created by D&D on 7/05/2025.
//

#ifndef LITTLEGAME_ENTITYCAMERA_H
#define LITTLEGAME_ENTITYCAMERA_H
#include <map>
namespace world {
    class entitycamera {
    public:
        entitycamera() = default;
        virtual ~entitycamera() = default;

        virtual void updateCoords(float _x, float _y) = 0;
    };
}

#endif //LITTLEGAME_ENTITYCAMERA_H
