#include "Button.h"
#include <iostream>

/*! Default Constructor*/
Button::Button()
{
}

/*! Sets up the button at a given position, with a given width, height and colour.*/
Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	m_pos = pos;
	m_size = size;

	m_button = sf::Rect<float>(pos, size);
	m_boundingBox.setPosition(pos);
	m_boundingBox.setSize(size);
	m_boundingBox.setFillColor(colour);
}

/*! Creates a Text object that will be drawn at the center of this button.*/
void Button::m_setText(std::string text, int iCharacterSize, sf::Font * font)
{
	m_text = Text(text, iCharacterSize, sf::Vector2f(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f), font);
}

/*! Sets a function that should be called when the button is clicked. The onClickFunc argument will
*	need to be passed in via std::function() and may need to be bound to a class via 'this' if not referencing
*	the function via an instance of a class.
*/
void Button::m_setOnClickEvent(std::function<void()> onClickFunc)
{
	m_onClickFunc = onClickFunc;
}

/*! Checks to see if the button has been clicked, assuming mousePos references the actual cursor positon
*	relative to the window. If it has been clicked, it will call the onClickFunc that was previously assigned.
*/
void Button::m_listenForClickEvent(sf::Vector2f mousePos)
{
	if (m_button.contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (m_onClickFunc != nullptr)
		{
			m_onClickFunc();
		}	
	}
}

/*! sf::Drawable virtual draw function.*/
void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_boundingBox);
	target.draw(m_text);
}
