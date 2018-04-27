#include "Text.h"

Text::Text()
{
}

Text::Text(std::string text, int iCharacterSize, sf::Vector2f pos, sf::Font * font)
{
	m_text = sf::Text(text, *font);

	m_text.setOrigin(m_text.getGlobalBounds().width * 0.3f, m_text.getGlobalBounds().height * 0.3f);

	m_text.setPosition(pos);

	m_text.setCharacterSize(iCharacterSize);
	m_text.setScale(0.01f, 0.01f);
	m_text.setStyle(sf::Text::Bold);
	m_text.setFillColor(sf::Color::White);
}

void Text::m_setId(std::string id)
{
	m_id = id;
}

void Text::m_setText(std::string text)
{
	m_text.setString(text);
}

void Text::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_isActive)
	{
		target.draw(m_text);
	}
}

void Text::m_setActive(bool isActive)
{
	m_isActive = isActive;
}
