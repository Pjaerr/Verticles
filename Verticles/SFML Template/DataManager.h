#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class DataManager
{
private:
	sf::Font * m_font;

	std::map<std::string, sf::Texture *> m_textures;

public:
	DataManager();
	~DataManager();

	void m_setFont(std::string filePath);

	sf::Font* m_getFont();

	sf::Texture* m_getTexture(std::string name);

	void m_addTexture(std::string name, std::string filePath);

};