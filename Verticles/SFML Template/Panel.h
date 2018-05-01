#pragma once

#include <SFML/Graphics.hpp>

/*! /class Panel
*	\brief sf::RectangleShapes that have pre-defined attributes.
*
*	A simple sf::RectangleShape that has pre-defined attributes so as to
*	make it work better as a Panel and reduce duplicate code.
*/
class Panel : public sf::Drawable
{
private:
	sf::RectangleShape m_panel; //!< The rectangle to be drawn to the screen.

public:
	Panel(); //!< The default constructor.

	/*! \brief Sets up this panel.
	*	\param pos The position to place this panel at, origin is top left.
	*	\param size The width and height of this panel.
	*	\param colour The colour of this panel.
	*/
	Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color colour);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};