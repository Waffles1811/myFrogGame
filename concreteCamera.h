//
// Created by Catelyn on 11/05/2025.
//

#ifndef LITTLEGAME_CONCRETECAMERA_H
#define LITTLEGAME_CONCRETECAMERA_H
#include "library_source_files/entitycamera.h"
#include "library_source_files/entity.h"

namespace world {
    class entitycamera;  // Forward declaration
}

namespace repr {
    class concreteCamera : public world::entitycamera {
        float x;
        float y;
    public:
        concreteCamera() = default;
        void updateCoords(float _x, float _y) override;
        ~concreteCamera() override = default;
        float getXcoord(float xHeight);
        float getYcoord(float Ylength);

    };
}

#endif //LITTLEGAME_CONCRETECAMERA_H
