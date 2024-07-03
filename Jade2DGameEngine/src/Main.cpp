#include "./Game/Game.h"

int main( int argc, char* argv[] ) {

    Game game;

    game.Inicialize();

    game.Run();

    game.Destroy();

    return 0;
}
