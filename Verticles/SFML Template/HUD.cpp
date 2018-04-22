#include "HUD.h"

HUD::HUD(sf::Font * font)
{
	m_ballsText = sf::Text("0/0", *font);
	m_platformsText = sf::Text("0/0", *font);

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
}
