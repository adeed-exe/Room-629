#include "pch.h"
#include "game.h"

int main() {
	srand(static_cast<unsigned>(time(NULL)));
	game g;

	while (g.running()) {
		g.update();
		g.render();
	}
}