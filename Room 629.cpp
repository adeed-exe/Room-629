#include "pch.h"
#include "game.h"

int main() {
	srand(static_cast<unsigned>(time(NULL)));
	Game game;

	while (game.running()) {
		game.update();
		game.render();
	}
}