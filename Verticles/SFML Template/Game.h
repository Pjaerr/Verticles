#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Ball.h"

class Game
{
	public:
		Game(float width, float height);
		~Game();
		void startGame();
		
	private:
		//Box2D Stuff
		const b2Vec2 mk_gravity = b2Vec2(0.0f, 200.0f);
		b2World *m_world;
		void update(float timestep);

		//SFML Stuff
		sf::RenderWindow * m_window;
		sf::Clock clock;
		sf::View view;
		
		//My Stuff
		Ball * m_ball;
		int points;
		float maxTimeInSeconds;
		//Level level;
		int GameLoop();
};