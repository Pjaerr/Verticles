#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class DataManager
{
private:
	sf::Font * m_font; //!< The font this game should use.

	std::map<std::string, sf::Texture *> m_textures; //!< Textures used and their corresponding names.

public:
	DataManager(); //!< The default constructor.
	~DataManager(); //!< The deconstructor.

	/*! \brief Sets the font the DataManager should store a pointer to.
	*	\param filePath The file path containing the font file.
	*/
	void m_setFont(std::string filePath);

	sf::Font* m_getFont(); //!< Returns the font that this DataManager stores.

	/*! \brief Returns a Texture pointer if found within the m_textures map.
	*	\param name The corresponding name/key of the texture within the m_textures map.
	*/
	sf::Texture* m_getTexture(std::string name);

	/*! \brief Creates a texture pointer within m_textures.
	*	\param name The name of the texture, used to get the texture.
	*	\param filePath The file path containing the texture file.
	*/
	void m_addTexture(std::string name, std::string filePath);

};