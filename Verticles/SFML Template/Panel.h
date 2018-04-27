#pragma once

#include <SFML/Graphics.hpp>

class Panel : public sf::Drawable
{
private:
	sf::RectangleShape m_panel;
	bool m_isActive = true;

public:
	Panel();
	Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color colour);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void m_setActive(bool isActive);
};