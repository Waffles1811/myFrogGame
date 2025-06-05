//
// Created by jensp on 4/06/2025.
//

#ifndef LITTLEGAME_LEVELEDITORAPP_H
#define LITTLEGAME_LEVELEDITORAPP_H

#include "game.h"
#include <fstream>
class levelEditorApp{
private:
    std::unique_ptr<world::levelEditor> editor;
    std::shared_ptr<repr::view> playerView;
    std::vector<std::shared_ptr<repr::button>> buttons;
    std::vector<saveFileObject> objects;
    int curLayer;
    int curScale;
public:
    levelEditorApp();
    void main_game_loop();
    void processInputs();
};


#endif //LITTLEGAME_LEVELEDITORAPP_H
