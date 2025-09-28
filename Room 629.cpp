#include "PCH.h"
#include "Game.h"

int main() {
    srand(static_cast<unsigned>(time(NULL))); // Set random seed for rng

    // Run the game
    Game game;
    game.run();

    return 0;
}