//
// Created by Catelyn on 11/05/2025.
//

#ifndef LITTLEGAME_CONCRETECAMERA_H
#define LITTLEGAME_CONCRETECAMERA_H
#include "../world_source_files/entitycamera.h"
#include "../world_source_files/entity.h"
#include "viewEntity.h"

namespace world {
    class entitycamera;  // Forward declaration
}

namespace repr {
    class concreteCamera : public world::entitycamera {
        std::shared_ptr<viewEntity> model;
    public:
        concreteCamera(std::shared_ptr<viewEntity>);
        void updateCoords(float _x, float _y) override;
        ~concreteCamera() override = default;
    };

    class concreteAnimationObserver : public world::animationObserver {
    private:
        std::string curAnimation;
        std::shared_ptr<viewEntity> model;
    public:
        concreteAnimationObserver(std::shared_ptr<viewEntity>);
        ~concreteAnimationObserver() = default;

        void startAnimation(std::string anim) override;
        void stopAnimation();
    };

    class concreteOrientationObserver : public  world::orientationObserver {
    private:
        bool facingLeft;
        std::shared_ptr<viewEntity> model;
    public:
        concreteOrientationObserver(std::shared_ptr<viewEntity>);
        void turn(bool direction) override;
        bool getDirection();
    };
}

#endif //LITTLEGAME_CONCRETECAMERA_H
