#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Ball.h"
#include "Level.h"


class Game
{
	public:
		Game(float width, float height);
		~Game();
		
	private:
		sf::Texture * m_textures[1]; //Convert to a texture map.


		sf::RenderWindow * window;
		
		sf::Clock clock;
		
		sf::View view;
		
		b2World *world;
		
		int points;
		
		float maxTimeInSeconds;
		
		Ball ball;
		//Level level;
		
		
		void startGame();
};