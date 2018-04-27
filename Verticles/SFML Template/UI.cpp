#include "UI.h"
#include <iostream>

UI::UI(sf::Font * font)
{
	m_font = font;

	m_ballsText = Text("0/0", 14, sf::Vector2f(7, 0.1f), font);
	m_platformsText = Text("0/0", 14, sf::Vector2f(6.9f, 0.6f), font);
	m_controlsText = Text("WASD to move || LEFT and RIGHT to rotate || UP and DOWN to scale || SPACEBAR to place", 14, sf::Vector2f(4.5f, 5.7f), font);
	m_titleText = Text("Verticles", 48, sf::Vector2f(3.5f, 0.5f), font);

	m_textPanel = Panel(sf::Vector2f(6.7f, 0.0f), sf::Vector2f(2.0f, 0.8f), sf::Color::Color(0, 0, 0, 100));
	m_controlsPanel = Panel(sf::Vector2f(0.0f, 5.5f), sf::Vector2f(8.0f, 0.9f), sf::Color::Color(0, 0, 0, 100));
	m_menuPanel = Panel(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8.0f, 6.0f), sf::Color::Color(0, 0, 0, 180));

	m_platformPlacementButton = Button(sf::Vector2f(0.0f, 5.5f), sf::Vector2f(1.5f, 0.5f), sf::Color::Red);
	m_platformPlacementButton.m_setText("Place a Platform", 14, m_font);

	m_menuPlayButton = Button(sf::Vector2f(3.3f, 1.75f), sf::Vector2f(1.5f, 0.5f), sf::Color::Red);
	m_menuPlayButton.m_setText("Play", 16, m_font);

	m_pauseButton = Button(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.8f, 0.5f), sf::Color::Red);
	m_pauseButton.m_setText("Start", 14, font);


	m_endScreenPanel = Panel(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8.0f, 6.0f), sf::Color::Color(0, 0, 0, 180));
	m_endScreenText = Text("You Win!", 48, sf::Vector2f(3.5f, 0.5f), font);

	m_endScreenLossButton = Button(sf::Vector2f(3.3f, 1.75f), sf::Vector2f(1.5f, 0.5f), sf::Color::Red);
	m_endScreenLossButton.m_setText("Try Again", 16, m_font);

	m_endScreenWinButton = Button(sf::Vector2f(3.3f, 1.75f), sf::Vector2f(1.5f, 0.5f), sf::Color::Red);
	m_endScreenWinButton.m_setText("Next Level", 16, m_font);

	m_resetLevelButton = Button(sf::Vector2f(0.0f, 0.6f), sf::Vector2f(0.8f, 0.5f), sf::Color::Red);
	m_resetLevelButton.m_setText("Reset", 14, font);
}

void UI::m_updateText(std::string ballsText, std::string platformsText)
{
	m_ballsText.m_setText("Balls: " + ballsText);
	m_platformsText.m_setText("Platforms: " + platformsText);
}

void UI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_showMainMenu)
	{
		target.draw(m_menuPanel);
		target.draw(m_titleText);
		target.draw(m_menuPlayButton);
	}
	else 
	{
		if (m_showControls)
		{
			target.draw(m_controlsPanel);
			target.draw(m_controlsText);
		}
		else
		{
			target.draw(m_platformPlacementButton);
		}

		target.draw(m_textPanel);
		target.draw(m_platformsText);
		target.draw(m_ballsText);
		target.draw(m_pauseButton);
		target.draw(m_resetLevelButton);


		if (m_showEndScreenWin)
		{
			target.draw(m_endScreenPanel);
			target.draw(m_endScreenText);
			target.draw(m_endScreenWinButton);
		}
		else if (m_showEndScreenLoss)
		{
			target.draw(m_endScreenPanel);
			target.draw(m_endScreenText);
			target.draw(m_endScreenLossButton);
		}

	}
}

void UI::m_updateMousePosition(sf::RenderWindow * relativeTo)
{
	m_mousePos = relativeTo->mapPixelToCoords(sf::Mouse::getPosition(*relativeTo));
}

void UI::m_mouseClicked()
{
	m_menuPlayButton.m_listenForClickEvent(m_mousePos);

	m_resetLevelButton.m_listenForClickEvent(m_mousePos);

	m_platformPlacementButton.m_listenForClickEvent(m_mousePos);
	m_pauseButton.m_listenForClickEvent(m_mousePos);

	if (m_showEndScreenWin)
	{
		m_endScreenWinButton.m_listenForClickEvent(m_mousePos);
	}
	else if (m_showEndScreenLoss)
	{
		m_endScreenLossButton.m_listenForClickEvent(m_mousePos);
	}
}
