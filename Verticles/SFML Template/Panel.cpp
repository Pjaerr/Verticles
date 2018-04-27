#include "Panel.h"

Panel::Panel()
{
}

Panel::Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	m_panel = sf::RectangleShape(size);
	m_panel.setFillColor(colour);
	m_panel.setPosition(pos);
}

void Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_isActive)
	{
		target.draw(m_panel);
	}
}

void Panel::m_setActive(bool isActive)
{
	m_isActive = isActive;
}
