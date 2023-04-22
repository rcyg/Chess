#include "Piece.h"
#include "Game.h"

int main(void) {
	Game Chess;
	while (Chess.window.isOpen()) {
		Chess.Run();
	}
}

 