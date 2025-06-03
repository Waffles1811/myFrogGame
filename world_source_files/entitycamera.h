//
// Created by D&D on 7/05/2025.
//

#ifndef LITTLEGAME_ENTITYCAMERA_H
#define LITTLEGAME_ENTITYCAMERA_H
#include <map>
enum class animation{
    jump,
    land,
    fall,
    walk,
    none
};

namespace world {
    class entitycamera {
    public:
        entitycamera() = default;
        virtual ~entitycamera() = default;

        virtual void updateCoords(float _x, float _y) = 0;
    };

    class animationObserver {
    public:
        animationObserver() = default;
        virtual ~animationObserver() = default;

        virtual void startAnimation(animation) = 0;
    };

    class orientationObserver {
        /* left = true, right = false */
    public:
        orientationObserver() = default;
        virtual void turn(bool direction) = 0;
    };
}

#endif //LITTLEGAME_ENTITYCAMERA_H
