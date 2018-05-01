#include "DataManager.h"

/*! The default constructor.*/
DataManager::DataManager()
{
}

/*! The deconstructor that deallocates memory that was allocated for the font and
*	for the texture map.
*/
DataManager::~DataManager()
{
	delete m_font;

	//Iterate through the map and delete the memory at each position.

	std::map<std::string, sf::Texture*>::iterator it = m_textures.begin();

	if (it != m_textures.end())
	{
		delete it->second;
	}
}

/*! Sets m_font to be a new sf::Font loaded from the given filePath.*/
void DataManager::m_setFont(std::string filePath)
{
	m_font = new sf::Font();

	m_font->loadFromFile(filePath);
}

/*! Returns the m_font.*/
sf::Font* DataManager::m_getFont()
{
	return m_font;
}

/*! Returns a pointer to a texture at a given name in the m_textures map only if it
*	exists.
*/
sf::Texture* DataManager::m_getTexture(std::string name)
{
	if (m_textures.find(name) != m_textures.end())
	{
		return m_textures.at(name);
	}
}

/*! Add a texture pointer to the m_textures map with the key being a given name.*/
void DataManager::m_addTexture(std::string name, std::string filePath)
{
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, new sf::Texture));
	m_textures.at(name)->loadFromFile(filePath);
}
