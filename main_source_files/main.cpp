#include "levelEditorApp.h"
int main() {
    if (true) {
        game theGame = game();
        theGame.setup();
        theGame.main_game_loop();
    } else {
        levelEditorApp theGame = levelEditorApp();
        theGame.main_game_loop();
    }
    return 0;
}
