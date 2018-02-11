#pragma once
#include "Ball.h"
#include "SFML\Graphics.hpp"
#include <array>
#include "Key.h"

/*! \file Control.h
* The class that handles keyboard input and the application of force within the correct
* correct direction depending upon where the Ball is in relation to the key that was pressed.
*/

class Control
{
	public:
		/*!
			Stores a reference to the ball currently being used in the game and
			then sets up the keys array.
		*/
		Control(Ball& ball);

		//! The function that calls checkKeyboardInput(); to be used within Game.
		void controlPlayer();

		//! Returns the array of Key objects corresponding to (QWERTYUIOP).
		std::array<Key, 10> getKeys(); //Returns the array of key objects.

	private:
		//! A reference to the ball being used within the game.
		const Ball *m_ballRef;

		//! Checks to see if any of the keys have been pressed (QWERTYUIOP) and then call applyForceToPlayer with that key.
		void checkKeyboardInput();

		/*Works out and apply the force needed to the player depending upon the key being pressed.*/
		void applyForceToPlayer(Key key); 

		//! An array of Key objects corresponding to (QWERTYUIOP).
		std::array<Key, 10> m_keys = {};
};