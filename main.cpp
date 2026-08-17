#include <ctime>
#include <cstdlib>
#include "Game.h"

int main() {
    srand((unsigned)time(0));
    Game game;
    game.run();
    return 0;
}
