#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Game.h"

int main()
{
	Game game = Game(600, 400);
	game.startGame();

	return 0;
}