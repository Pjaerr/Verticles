#include "Text.h"

/*! The default constructor.*/
Text::Text()
{
}

/*! Creates an instance of sf::Text with the given text and font. It then sets up
*	the text, scaling it to (0.01, 0.01) so as to show up correctly within the sf::View
*	that is used for Box2D.
*/
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

/*! Sets the string of the sf::Text m_text to the given std::string.*/
void Text::m_setText(std::string text)
{
	m_text.setString(text);
}

/*! The sf::Drawable virtual draw function.*/
void Text::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_text);
}
