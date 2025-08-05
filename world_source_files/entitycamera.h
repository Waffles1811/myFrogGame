//
// Created by D&D on 7/05/2025.
//

#ifndef LITTLEGAME_ENTITYCAMERA_H
#define LITTLEGAME_ENTITYCAMERA_H
#include <map>
#include <string>
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

        virtual void startAnimation(std::string anim) = 0;
    };

    class orientationObserver {
        /* left = true, right = false */
    public:
        orientationObserver() = default;
        virtual void turn(bool direction) = 0;
    };
}

#endif //LITTLEGAME_ENTITYCAMERA_H
