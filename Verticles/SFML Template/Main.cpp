#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Game.h"

int main()
{
	Game game = Game(800, 600, "Verticles");
	game.run();

	return 0;
}