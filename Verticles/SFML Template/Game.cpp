#include "Game.h"
#include <iostream>

Game::Game(float width, float height)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Verticles");

	m_world = new b2World(mk_gravity);

	m_ball = new Ball(sf::Vector2f(300.0f, 200.0f), 2, 45, m_world);
}

Game::~Game()
{
	delete(m_window);
	delete(m_ball);
}

void Game::startGame()
{
	/*TEMP*/
	sf::Texture tex = sf::Texture();
	tex.loadFromFile("./resources/Textures/ball.png");
	m_ball->setTexture(tex);
	/*TEMP*/

	GameLoop();
}

void Game::update(float timestep)
{
	/*TEMP*/
	m_world->Step(timestep, 7, 5);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_ball->applyForce(0, 100, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_ball->applyForce(-100, 100, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_ball->applyForce(100, 100, 0);
	}
	
	m_ball->update();
	/*TEMP*/
}

int Game::GameLoop()
{
	sf::Event event;

	/*TEMP*/
	float fFrameTime = 1.0f / 60.0f;
	/*TEMP*/

	clock = sf::Clock();

	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				m_window->close();
			}
		}

		/*TEMP*/
		float fElapsedTime = clock.getElapsedTime().asSeconds();

		if (fElapsedTime > fFrameTime)
		{
			update(fElapsedTime);
			clock.restart();
		}
		/*TEMP*/

		m_window->clear();
		m_window->draw(*m_ball);
		m_window->display();

	}

	return 0;
}