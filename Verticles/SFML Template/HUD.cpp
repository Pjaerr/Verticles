#include "HUD.h"
#include <iostream>

HUD::HUD(sf::Font * font)
{
	m_ballsText = sf::Text("0/0", *font);
	m_platformsText = sf::Text("0/0", *font);


	//PROBABLY CONVERT THIS MESS INTO A FUNCTION THAT TAKES A TEXT REFERENCE

	m_ballsText.setCharacterSize(14);
	m_ballsText.setScale(0.01f, 0.01f);
	m_ballsText.setStyle(sf::Text::Bold);
	m_ballsText.setPosition(sf::Vector2f(7, 0));
	m_ballsText.setFillColor(sf::Color::White);

	m_platformsText.setCharacterSize(14);
	m_platformsText.setScale(0.01f, 0.01f);
	m_platformsText.setStyle(sf::Text::Bold);
	m_platformsText.setPosition(sf::Vector2f(6.8, 0.5));
	m_platformsText.setFillColor(sf::Color::White);

	m_textPanel = sf::RectangleShape(sf::Vector2f(2, 0.8));
	m_textPanel.setFillColor(sf::Color::Color(0, 0, 0, 100));
	m_textPanel.setPosition(sf::Vector2f(6.7, 0));


	m_controlsText = sf::Text("WASD to move || LEFT and RIGHT to rotate || UP and DOWN to scale || ENTER to place", *font);

	m_controlsText.setCharacterSize(14);
	m_controlsText.setScale(0.01f, 0.01f);
	m_controlsText.setStyle(sf::Text::Bold);
	m_controlsText.setPosition(sf::Vector2f(1.0f, 5.65f));
	m_controlsText.setFillColor(sf::Color::White);

	m_controlsPanel = sf::RectangleShape(sf::Vector2f(8.0f, 0.9f));
	m_controlsPanel.setFillColor(sf::Color::Color(0, 0, 0, 100));
	m_controlsPanel.setPosition(sf::Vector2f(0.0f, 5.5f));


	platformPlacementButton = sf::Rect<float>(sf::Vector2f(0.0f, 5.5f), sf::Vector2f(1.5f, 0.9f));
	platformPlacementBox.setPosition(sf::Vector2f(0.0f, 5.5f));
	platformPlacementBox.setSize(sf::Vector2f(1.3f, 0.9f));
	platformPlacementBox.setFillColor(sf::Color::Red);

	platformPlacementText = sf::Text("Place a Platform", *font);
	platformPlacementText.setPosition(0.1f, 5.65f);

	platformPlacementText.setCharacterSize(14);
	platformPlacementText.setScale(0.01f, 0.01f);
	platformPlacementText.setStyle(sf::Text::Bold);


	m_menuPanel = sf::RectangleShape(sf::Vector2f(8.0f, 6.0f));
	m_menuPanel.setFillColor(sf::Color::Color(0, 0, 0, 180));
	m_menuPanel.setPosition(sf::Vector2f(0.0f, 0.0f));

	m_menuPlayButton = sf::Rect<float>(sf::Vector2f(3.3f, 1.75f), sf::Vector2f(1.5f, 0.5f));
	m_menuPlayBox.setPosition(sf::Vector2f(3.3f, 1.75f));
	m_menuPlayBox.setSize(sf::Vector2f(1.5f, 0.5f));
	m_menuPlayBox.setFillColor(sf::Color::Red);

	m_menuPlayText = sf::Text("Play", *font);
	m_menuPlayText.setPosition(3.85f, 1.9f);

	m_menuPlayText.setCharacterSize(16);
	m_menuPlayText.setScale(0.01f, 0.01f);
	m_menuPlayText.setStyle(sf::Text::Bold);

	m_titleText = sf::Text("Verticles", *font);

	m_titleText.setPosition(3.2f, 0.5f);

	m_titleText.setCharacterSize(48);
	m_titleText.setScale(0.01f, 0.01f);
	m_titleText.setStyle(sf::Text::Bold);

}

void HUD::m_update(std::string ballsText, std::string platformsText)
{
	m_ballsText.setString("Balls: " + ballsText);
	m_platformsText.setString("Platforms: " + platformsText);
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_textPanel);
	target.draw(m_ballsText);
	target.draw(m_platformsText);

	if (!m_showControls)
	{
		target.draw(platformPlacementBox);
		target.draw(platformPlacementText);
	}
	

	if (m_showControls)
	{
		target.draw(m_controlsPanel);
		target.draw(m_controlsText);
	}

	if (!m_gameStarted)
	{
		target.draw(m_menuPanel);
		target.draw(m_menuPlayBox);
		target.draw(m_menuPlayText);
		target.draw(m_titleText);
	}
}

void HUD::m_updateMousePosition(sf::RenderWindow * relativeTo)
{
	m_mousePos = relativeTo->mapPixelToCoords(sf::Mouse::getPosition(*relativeTo));
}

void HUD::m_mouseClicked()
{
	if (platformPlacementButton.contains(m_mousePos))
	{
		m_platformPlacementButtonIsPressed = true;
	}
	else if(m_menuPlayButton.contains(m_mousePos) && m_gameStarted == false)
	{
		m_menuPlayButtonIsPressed = true;
	}
}
