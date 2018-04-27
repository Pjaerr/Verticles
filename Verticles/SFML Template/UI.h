#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Panel.h"

class UI : public sf::Drawable
{
private:
	//Text
	Text m_titleText;
	Text m_controlsText;
	Text m_ballsText;
	Text m_platformsText;
	

	//Panels
	Panel m_menuPanel;
	Panel m_controlsPanel;
	Panel m_textPanel;
	Panel m_endScreenPanel;
	
	sf::Vector2f m_mousePos;

	sf::Font * m_font;
public:
	UI(sf::Font * font);

	void m_updateText(std::string ballsText, std::string platformsText);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void m_updateMousePosition(sf::RenderWindow * relativeTo);
	void m_mouseClicked();

	bool m_showControls = false;
	bool m_showMainMenu = true;

	bool m_showEndScreenWin = false;
	bool m_showEndScreenLoss = false;

	//Buttons
	Button m_platformPlacementButton;
	Button m_menuPlayButton;
	Button m_pauseButton;
	Button m_resetLevelButton;

	Button m_endScreenLossButton;
	Button m_endScreenWinButton;

	Text m_endScreenText;

};