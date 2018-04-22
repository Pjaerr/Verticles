#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
	delete m_font;
	
	std::map<std::string, sf::Texture*>::iterator it = m_textures.begin();

	if (it != m_textures.end())
	{
		delete it->second;
	}
}

void DataManager::m_setFont(std::string filePath)
{
	m_font = new sf::Font();

	m_font->loadFromFile(filePath);
}

sf::Font* DataManager::m_getFont()
{
	return m_font;
}

sf::Texture* DataManager::m_getTexture(std::string name)
{
	if (m_textures.find(name) != m_textures.end())
	{
		return m_textures.at(name);
	}
}

void DataManager::m_addTexture(std::string name, std::string filePath)
{
	m_textures.insert(std::pair<std::string, sf::Texture*>(name, new sf::Texture));
	m_textures.at(name)->loadFromFile(filePath);
}
