
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Game Window");

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				window.close();
			}
		}

		window.clear();

		window.display();

	}

	return 0;
}