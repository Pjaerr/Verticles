#include "Panel.h"

/*! The default constructor.*/
Panel::Panel()
{
}

/*! Sets up this panel at a given position with a given width and height and a 
*	given colour.
*/
Panel::Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	m_panel = sf::RectangleShape(size);
	m_panel.setFillColor(colour);
	m_panel.setPosition(pos);
}

/*! sf::Drawable virtual draw function.*/
void Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_panel);
}
