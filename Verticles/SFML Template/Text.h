#pragma once

#include <SFML/Graphics.hpp>

/*! /class Text
*	\brief A wrapper for an sf::Text object.
*
*	A simple wrapper for an sf::Text object that allows easy scaling
*	to fit the Box2D pixels->meters conversion.
*/
class Text : public sf::Drawable
{

private:
	sf::Text m_text; //!< The actual text that will be drawn to the screen.

public:
	Text(); //!< The default constructor.

	/*! \brief The Text constructor initialises the sf::Text m_text member.
	*	\param text The string to be shown.
	*	\param iCharacterSize The size of the text.
	*	\param pos The position of the text, origin centered.
	*	\param font A pointer to the font that should be used.
	*/
	Text(std::string text, int iCharacterSize, sf::Vector2f pos, sf::Font * font);

	/*! \brief Sets the string to be shown.
	*	\param text The string to be shown.
	*/
	void m_setText(std::string text);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};