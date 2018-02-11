#include "Key.h"


Key::Key(std::string name, sf::Vector2f position)
{
	m_name = name;
	m_position = position;
}

Key::Key()
{

}

void Key::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rekt = sf::RectangleShape(sf::Vector2f(50, 50));
	target.draw(rekt);
}