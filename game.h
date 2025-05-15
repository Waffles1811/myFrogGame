//
// Created by A Song of Ice and Fire on 7/05/2025.
//

#ifndef LITTLEGAME_GAME_H
#define LITTLEGAME_GAME_H
#include <memory>
#include "library_source_files/world.h"
#include "library_source_files/singletons.h"
#include "view.h"
#include "concreteFactory.h"
class game {
private:
    std::unique_ptr<world::world> world;
    std::shared_ptr<repr::view> playerView;
    std::unique_ptr<world::stopwatchFactory> stopwatchInc;
public:
    game();
    void setup();
    void main_game_loop();
    void processInputs();
};


#endif //LITTLEGAME_GAME_H
