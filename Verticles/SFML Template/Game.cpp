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

	m_level = new Level();

	m_window->setView(m_view);
}

Game::~Game()
{
	delete m_window;
	delete m_level;
}

/*!
*	The Start function is called once before the game loop has been started, just after the initialisation
*	of the clock. This should be used to implement the initialisation of objects, variables, references etc
*	that are needed for the game itself and not the flow of the program.
*/
void Game::Start()
{
	std::vector<b2Vec2> entryPoints;
	entryPoints.push_back(b2Vec2(-2.0f, 0.0f));
	entryPoints.push_back(b2Vec2(2.0f, 0.0f));

	std::vector<b2Vec2> goals;
	goals.push_back(b2Vec2(0.0f, 2.0f));
	goals.push_back(b2Vec2(-2.0f, 2.0f));

	m_level->m_newLevel(10, 5, entryPoints, goals);

	m_level->m_resume();
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

	m_level->m_update(fElapsedTime);
}

/*!
*	The Render function is called every frame much like the Update function, however it should only be used to
*	to draw things using the sf::RenderWindow.
*/
void Game::Render()
{
	m_window->draw(*m_level);
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

