#pragma once

#include <SFML/Graphics.hpp>

class Text : public sf::Drawable
{

private:
	sf::Text m_text;

	bool m_isActive = true;

public:
	Text();

	Text(std::string text, int iCharacterSize, sf::Vector2f pos, sf::Font * font);

	void m_setId(std::string id);

	void m_setText(std::string text);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void m_setActive(bool isActive);

	std::string m_id;

};