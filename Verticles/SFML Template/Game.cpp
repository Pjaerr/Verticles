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

	b2Vec2 worldSize = b2Vec2(8, 6);


	//sf::View set at (0,0) with a size of the physical world size.
	m_view = sf::View(sf::Vector2f(4.0f, 3.0f), sf::Vector2f(worldSize.x, worldSize.y));

	m_level = new Level(worldSize);

	m_window->setView(m_view);

	m_backgroundTexture = new sf::Texture();

	if (m_backgroundTexture->loadFromFile("./resources/Textures/HealthyWater.jpg"))
	{
		m_backgroundShape = sf::RectangleShape(sf::Vector2f(worldSize.x, worldSize.y));
		m_backgroundShape.setOrigin(m_backgroundShape.getGlobalBounds().width / 2, m_backgroundShape.getGlobalBounds().height / 2);
		m_backgroundShape.setPosition(worldSize.x / 2, worldSize.y / 2);
		m_backgroundShape.setTexture(m_backgroundTexture);
	}
	else
	{
		std::cout << "Failed to load background texture." << std::endl;
	}
}

Game::~Game()
{
	delete m_window;
	delete m_level;
	delete m_backgroundTexture;
}

/*!
*	The Start function is called once before the game loop has been started, just after the initialisation
*	of the clock. This should be used to implement the initialisation of objects, variables, references etc
*	that are needed for the game itself and not the flow of the program.
*/
void Game::Start()
{
	m_level->m_addLevel("./resources/Levels/level1.txt", "level1");
	m_level->m_addLevel("./resources/Levels/level2.txt", "level2");
	m_level->m_addLevel("./resources/Levels/level3.txt", "level3");
	m_level->m_addLevel("./resources/Levels/level4.txt", "level3");
	m_level->m_addLevel("./resources/Levels/level5.txt", "level5");
	m_level->m_addLevel("./resources/Levels/level6.txt", "level6");
	m_level->m_addLevel("./resources/Levels/level7.txt", "level7");

	m_level->m_startLevel("level1");
}

/*!
*	The Update function gets called every frame and gets given the time since it was last called.
*	This function should essentially be used as the	game loop wherein any game behaviour that isn't 
*	related to the drawing of objects should be implemented.
*/
void Game::Update(float fElapsedTime)
{
	m_level->m_hud->m_updateMousePosition(m_window);

	/*Temporary way to resume/pause the game.*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_level->m_resume();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		m_level->m_pause();
	}

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
	m_window->draw(m_backgroundShape);
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
			else if (event.type == event.MouseMoved)
			{
				m_level->m_hud->m_updateMousePosition(m_window);
			}
			else if (event.type == event.MouseButtonPressed)
			{
				m_level->m_hud->m_mouseClicked();
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

