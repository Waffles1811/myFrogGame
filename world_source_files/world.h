//
// Created by Essos on 7/05/2025.
//

#ifndef LITTLEGAME_WORLD_H
#define LITTLEGAME_WORLD_H
#include "abstractFactory.h"
namespace world {
    class world {
    protected:
        std::vector<std::shared_ptr<entity>> entities;
        std::shared_ptr<player> playerchar;
        std::shared_ptr<abstractFactory> factory;


    public:
        world(std::shared_ptr<abstractFactory>);
        void setup();
        void time_up(float time);
        void processInputs(movement);
        void loadRoom(std::vector<saveFileObject>);
    };
}
#endif //LITTLEGAME_WORLD_H
