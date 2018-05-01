#pragma once

#include <SFML\Graphics.hpp>
#include "Level.h"

/*! \file Game.h
* Game.h is the basis for the 'program flow'. It is intended to be reusable as a class
* that handles the window and the program flow such as Updating and Rendering the game.
* The Game class shouldn't directly manage any part of the game itself (eg. character jumping),
* instead, this functionality should stay within the Start() and Update() functions, and be abstracted
* out into other objects relevant to the game itself.
*/


/*!\class Game
*	\brief The basis for the 'program flow'.

*	The class is intended to be reusable as it only handles the window and program
*	flow such as updating and rendering the game. The Game class doesn't directly manage
*	any part of the game itself, it simply holds the functionality that gets initiated via the object
*	that it is a part of. 
*/
class Game
{
	public:
		/*! \brief Initialises the Game class, creating a window of a given width and height.*/
		/*!
		\param width The width of the window.
		\param height The height of the window.
		\param name The title of the window.
		*/
		Game(float fWidth, float fHeight, std::string name);

		/*!\brief Cleans up any pointers.*/
		~Game();

		/*! \brief Starts the game loop which calls the other functions.*/
		void m_run();
		
	private:
		sf::RenderWindow * m_window = nullptr; //!< The window used for the game.
		sf::Clock m_clock; //!< The clock used to track the time that has elapsed.
		sf::View m_view; //!< Responsible for scaling to any aspect ratio and mapping box2D coordinates to sfml coordinates.
		int m_iWindowWidth;	//!< The width of the window.
		int m_iWindowHeight; //!< The height of the window.

		sf::RectangleShape m_backgroundShape;
		sf::Texture * m_backgroundTexture;

		/*! \brief The Update function gets called every frame and holds the elapsed time since it was last called.*/
		void Update(float fElapsedTime);

		/*! \brief The Start function is called once before the game loop is started.*/
		void Start();

		/*! \brief The Render function is called every frame and should be used exclusively for the drawing of objects.*/
		void Render();

		Level * m_level; //!< The level object that controls all of the 'Verticles' game.
};