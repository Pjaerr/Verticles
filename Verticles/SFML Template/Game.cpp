#include "Game.h"

/*!
*	Initialises the sf::RenderWindow, with a given width and height, that is then used to draw all 
*	other sf::Drawable objects in the game. It stores the given width and height in case they are 
*	needed later. Finally, it sets up an sf::View using the given width and height multiplied by
*	0.01 to get the window dimensions as meters for use with Box2D.
*/
Game::Game(float width, float height, std::string name)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), name);

	m_iWindowWidth = width;
	m_iWindowHeight = height;

	//! The physical world in meters for conversion between SFML coordinates and Box2D coordinates.
	m_physicalWorldSize = sf::Vector2f(width * 0.01f, height * 0.01f);

	//! sf::View set at (0,0) with a size of the physical world size.
	m_view = sf::View(sf::Vector2f(0.0f, 0.0f), m_physicalWorldSize);

	m_window->setView(m_view);
}

Game::~Game()
{
	delete m_window;
	delete m_ball;
}


/*(Note for devlog/report etc) Any code not specific to the Game class itself should be written inside of the Start(), Update() or
Render() functions depending upon its purpose or desired run-time. This is to ensure that the Game class is as re-usable as possible 
in different scenarios. So even if the game I am making didn't use a Ball class or anything to do with Box2D such as a b2World object,
the Game class here could still be used easily without having to deconstruct the layout of the class, at which point it would probably
be more efficient to just remake the class alltogether.*/

/*!
*	The Start function is called once before the game loop has been started, just after the initialisation
*	of the clock. This should be used to implement the initialisation of objects, variables, references etc
*	that are needed for the game itself and not the flow of the program.
*/
void Game::Start()
{
	physics = Physics(b2Vec2(0.0f, 10.0f), 7, 5); //! Setup the Physics object, creating the b2World.

	//! Setup the ball.
	m_ball = new Ball(sf::Vector2f(0.0f, 0.0f), 0.02f, 0.0f, physics.getWorld());
	m_ball->setupTextureFromFile("./resources/Textures/ball.png");
}

/*!
*	The Update function gets called every frame and gets given the time since it was last called.
*	This function should essentially be used as the	game loop wherein any game behaviour that isn't 
*	related to the drawing of objects should be implemented.
*/
void Game::Update(float elapsedTime)
{
	physics.updateWorld(elapsedTime); //! Calls b2World::Step() with the given elapsedTime.

	m_ball->update(); //! Keep the Ball sprite in sync with its b2Body.

	/*Temporary force testing (WILL BE MOVED TO CONTROL.CPP)*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_ball->applyForce(0.0f, 0.5f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_ball->applyForce(0.5f, 0.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_ball->applyForce(-0.5f, 0.0f, 0.0f);
	}
	/*Temporary force testing (WILL BE MOVED TO CONTROL.CPP)*/
}

/*!
*	The Render function is called every frame much like the Update function, however it should only be used to
*	to draw things using the sf::RenderWindow.
*/
void Game::Render()
{
	m_window->draw(*m_ball);
}


/*!
*	Initiates and handles the game loop; This function should be the only externally called function. 
*	it will start the game loop, in which the other functions (Start, Update and Render) will be called.
*/
void Game::run()
{
	sf::Event event; //! Used when handling SFML events.

	float fFrameTime = 1.0f / 60.0f; //! 60 FPS.

	clock = sf::Clock();

	Start(); //! Call the Start function once.

	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				m_window->close();
			}
		}

		float fElapsedTime = clock.getElapsedTime().asSeconds(); //! Elapsed time in seconds.

		if (fElapsedTime > fFrameTime) //! Lock Update calls to 60 frames per second.
		{
			Update(fElapsedTime); //! Call the Update function with the elapsed time every frame.
			clock.restart();
		}

		m_window->clear();
		Render(); //! Call the Render function every frame.
		m_window->display();
	}
}

