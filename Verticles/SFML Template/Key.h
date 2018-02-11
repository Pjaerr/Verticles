#pragma once
#include <string>
#include <SFML/Graphics.hpp>

/*! \file Key.h
* The class used to hold information about a key. This is the key's name, and the position of the key
* within the world. The key, when targetted via window.draw() will draw itself as a box surrounding the
* m_name value.
*/

class Key : public sf::Drawable
{
public:
	//! The default Key constructor.
	Key();

	//! The Key constructor sets the name and position of this Key.
	Key(std::string name, sf::Vector2f position);

	//! The name of this key. (A, B, C etc)
	std::string m_name;

	//! The position of this key in the world. Used by Control.h when working out what force to apply to the Ball.
	sf::Vector2f m_position;

private:
	/*!
		The overridden sf::Drawable::draw() function. It will draw a box surrounding
		the name of this Key when this key is passed into a RenderWindow::draw() function.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //Should draw text surrounded by a box
};