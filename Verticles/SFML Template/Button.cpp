#include "Button.h"
#include <iostream>

Button::Button()
{
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	m_pos = pos;
	m_size = size;

	m_button = sf::Rect<float>(pos, size);
	m_boundingBox.setPosition(pos);
	m_boundingBox.setSize(size);
	m_boundingBox.setFillColor(colour);
}

void Button::m_setId(std::string id)
{
	m_id = id;
}

void Button::m_setText(std::string text, int iCharacterSize, sf::Font * font)
{
	m_text = Text(text, iCharacterSize, sf::Vector2f(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f), font);
}

void Button::m_setOnClickEvent(std::function<void()> onClickFunc)
{
	m_onClickFunc = onClickFunc;
}

void Button::m_listenForClickEvent(sf::Vector2f mousePos)
{
	if (m_isActive)
	{
		if (m_button.contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (m_onClickFunc != nullptr)
			{
				m_onClickFunc();
			}
			
		}
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_isActive)
	{
		target.draw(m_boundingBox);
		target.draw(m_text);
	}
}

void Button::m_setActive(bool isActive)
{
	m_isActive = isActive;
}
