#include "game.h"
int main() {
    game theGame = game();
    theGame.setup();
    theGame.main_game_loop();
    return 0;
}
