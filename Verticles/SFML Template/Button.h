#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "Text.h"

class Button : public sf::Drawable
{

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	Text m_text;

	sf::Rect<float> m_button;
	sf::RectangleShape m_boundingBox;

	std::function<void()> m_onClickFunc;

	bool m_isActive = true;
	
public:
	Button();

	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color colour);

	void m_setId(std::string id);

	void m_setText(std::string text, int iCharacterSize, sf::Font * font);

	void m_setOnClickEvent(std::function<void()> onClickFunc);

	void m_listenForClickEvent(sf::Vector2f mousePos);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void m_setActive(bool isActive);

	std::string m_id;

};