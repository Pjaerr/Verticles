#pragma once

#include <SFML/Graphics.hpp>

class HUD : public sf::Drawable
{
private:
	sf::RectangleShape m_textPanel;
	sf::Text m_ballsText;
	sf::Text m_platformsText;

	sf::Rect<float> platformPlacementButton;
	sf::RectangleShape platformPlacementBox;
	sf::Text platformPlacementText;

	sf::RectangleShape m_controlsPanel;
	sf::Text m_controlsText;


	//BUTTONS COULD BE THEIR OWN CLASS

	sf::RectangleShape m_menuPanel;

	sf::Rect<float> m_menuPlayButton;
	sf::RectangleShape m_menuPlayBox;
	sf::Text m_menuPlayText;

	sf::Text m_titleText;

	sf::Vector2f m_mousePos;
public:
	HUD(sf::Font * font);

	void m_update(std::string ballsText, std::string platformsText);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void m_updateMousePosition(sf::RenderWindow * relativeTo);
	void m_mouseClicked();

	bool m_platformPlacementButtonIsPressed = false;

	bool m_showControls = false;

	bool m_menuPlayButtonIsPressed = false;

	bool m_gameStarted = false;

};