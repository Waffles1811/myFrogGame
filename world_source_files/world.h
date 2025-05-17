//
// Created by Essos on 7/05/2025.
//

#ifndef LITTLEGAME_WORLD_H
#define LITTLEGAME_WORLD_H
#include "abstractFactory.h"
#include "hitbox.h"
namespace world {
    class world {
        std::vector<std::shared_ptr<entity>> entities;
        std::shared_ptr<player> playerchar;
        std::shared_ptr<abstractFactory> factory;

    public:
        world(std::shared_ptr<abstractFactory>);
        void setup();
        void time_up(float time);
        void processInputs(movement);

    };
}
#endif //LITTLEGAME_WORLD_H
