
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Verticles");

	sf::Event event;

	sf::RectangleShape rekt;

	rekt.setPosition(250, 250);
	rekt.setSize(sf::Vector2f(50.0f, 50.0f));

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
		window.draw(rekt);
		window.display();

	}

	return 0;
}