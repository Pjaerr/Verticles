#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "Text.h"

/*! /class Button
*	\brief Clickable buttons drawn via the sf::RenderWindow.
*	
*	A button that can be positioned and resized and takes a function
*	that will be called when the button is clicked.
*/
class Button : public sf::Drawable
{

private:
	sf::Vector2f m_pos; //!< The position of this button.
	sf::Vector2f m_size; //!< The width and height of this button.

	Text m_text; //!< The Text in the middle of the Button.

	sf::Rect<float> m_button; //!< The button used for detecting clicks.
	sf::RectangleShape m_boundingBox; //!< The box used to show the button at m_pos with m_size.

	std::function<void()> m_onClickFunc; //!< The function that will be called when this button is clicked.
	
public:
	Button(); //!< Default Constructor.

	/*! \brief Sets up the Button.
	*	\param pos The position this button should be placed, origin is the top left.
	*	\param size The width and height of this button.
	*	\param colour The colour of this Button.
	*/
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color colour);

	/*! \brief Sets the text that sits in the center of the button.
	*	\param text The string to be displayed.
	*	\param iCharacterSize The character size of the text.
	*	\param font A pointer to the font that should be used.
	*/
	void m_setText(std::string text, int iCharacterSize, sf::Font * font);

	/*! \brief Assigns a function that should be called when this button is clicked.
	*	\param onClickFunc The function that will be called. Should be passed in as an std::function(). (May need binding)
	*/
	void m_setOnClickEvent(std::function<void()> onClickFunc);

	/*! \brief Checks if a given mouse position is within the button and if so, calls onClickFunc.
	*	\param mousePos The mouse position.
	*/
	void m_listenForClickEvent(sf::Vector2f mousePos);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};