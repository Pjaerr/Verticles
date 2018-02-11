#include "Control.h"

Control::Control(Ball& ball)
{
	m_ballRef = &ball; //Store a constant reference to the ball.

	/*Initialise the keys.*/
	m_keys[0] = Key("Q", sf::Vector2f(0.0f, 0.0f));
	m_keys[1] = Key("W", sf::Vector2f(0.0f, 0.0f));
	m_keys[2] = Key("E", sf::Vector2f(0.0f, 0.0f));
	m_keys[3] = Key("R", sf::Vector2f(0.0f, 0.0f));
	m_keys[4] = Key("T", sf::Vector2f(0.0f, 0.0f));
	m_keys[5] = Key("Y", sf::Vector2f(0.0f, 0.0f));
	m_keys[6] = Key("U", sf::Vector2f(0.0f, 0.0f));
	m_keys[7] = Key("I", sf::Vector2f(0.0f, 0.0f));
	m_keys[8] = Key("O", sf::Vector2f(0.0f, 0.0f));
	m_keys[9] = Key("P", sf::Vector2f(0.0f, 0.0f));
}

std::array<Key, 10> Control::getKeys()
{
	return m_keys;
}