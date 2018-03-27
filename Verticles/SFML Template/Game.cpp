#include "Game.h"

/*!
*	Initialises the sf::RenderWindow, with a given width and height, that is then used to draw all 
*	other sf::Drawable objects in the game. It stores the given width and height in case they are 
*	needed later. Finally, it sets up an sf::View using the given width and height multiplied by
*	0.01 to get the window dimensions as meters for use with Box2D.
*/
Game::Game(float fWidth, float fHeight, std::string name)
{
	m_window = new sf::RenderWindow(sf::VideoMode(fWidth, fHeight), name);

	m_iWindowWidth = fWidth;
	m_iWindowHeight = fHeight;

	//The physical world in meters for conversion between SFML coordinates and Box2D coordinates.
	m_physicalWorldSize = sf::Vector2f(fWidth * 0.01f, fHeight * 0.01f);

	//sf::View set at (0,0) with a size of the physical world size.
	m_view = sf::View(sf::Vector2f(0.0f, 0.0f), m_physicalWorldSize);

	m_window->setView(m_view);
}

Game::~Game()
{
	delete m_window;
	delete m_testBall;
	delete m_testPlatform;
}

/*!
*	The Start function is called once before the game loop has been started, just after the initialisation
*	of the clock. This should be used to implement the initialisation of objects, variables, references etc
*	that are needed for the game itself and not the flow of the program.
*/
void Game::Start()
{
	m_physics = Physics(b2Vec2(0.0f, 10.0f), 7, 5); //Setup the Physics object, creating the b2World.

	m_testBall = new Ball("./resources/Textures/ball.png", b2Vec2(0.0f, -3.0f), 0.1f, m_physics.getWorld());
	m_testPlatform = new Platform(b2Vec2(0.0f, 0.0f), b2Vec2(4.0f, 0.5f), 4.0f, m_physics.getWorld());
}

/*!
*	The Update function gets called every frame and gets given the time since it was last called.
*	This function should essentially be used as the	game loop wherein any game behaviour that isn't 
*	related to the drawing of objects should be implemented.
*/
void Game::Update(float fElapsedTime)
{
	/*Temporary way to exit window.*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window->close();
	}

	m_physics.updateWorld(fElapsedTime); //Calls b2World::Step() with the given elapsedTime.
	m_testBall->m_update();
}

/*!
*	The Render function is called every frame much like the Update function, however it should only be used to
*	to draw things using the sf::RenderWindow.
*/
void Game::Render()
{
	m_window->draw(*m_testBall);
	m_window->draw(*m_testPlatform);
}


/*!
*	Initiates and handles the game loop; This function should be the only externally called function. 
*	it will start the game loop, in which the other functions (Start, Update and Render) will be called.
*/
void Game::m_run()
{
	sf::Event event; //Used when handling SFML events.

	float fFrameTime = 1.0f / 60.0f; //60 FPS.

	m_clock = sf::Clock(); //Initialise the SFML Clock.

	Start(); //Run any initialisation code.

	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				m_window->close();
			}
		}

		float fElapsedTime = m_clock.getElapsedTime().asSeconds(); //Elapsed time in seconds.

		if (fElapsedTime > fFrameTime) //Lock Update calls to 60 frames per second.
		{
			Update(fElapsedTime); //Call the Update function with the elapsed time every frame.
			m_clock.restart();
		}

		m_window->clear();
		Render(); //Call the Render function every frame.
		m_window->display();
	}
}

