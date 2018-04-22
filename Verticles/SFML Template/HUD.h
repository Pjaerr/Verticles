#pragma once

#include <SFML/Graphics.hpp>

class HUD : public sf::Drawable
{
private:
	sf::RectangleShape m_textPanel;
	sf::Text m_ballsText;
	sf::Text m_platformsText;


	//USE FLOAT RECT FOR BUTTON

public:
	HUD(sf::Font * font);

	void m_update(std::string ballsText, std::string platformsText);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};