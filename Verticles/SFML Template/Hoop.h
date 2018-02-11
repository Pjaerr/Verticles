#pragma once

#include <SFML\Graphics.hpp>
#include "Trigger.h"

/*! \file Hoop.h
* A Trigger that will be randomly placed within a level and be used to 'score' points whenever
* the Ball collides with them. They do not have a physical presence within the game and simply
* act as triggers that the player can collide with.
*/

class Hoop : public sf::Sprite, public Trigger
{
	public:
		//! Sets up this hoop, placing it randomly between two limits and initialising its sf::Sprite and Trigger.
		/*!
		\param limitMin The lower limit that the chosen random position must not go below.
		\param limitMax The upper limit that the chosen random position must not go above.
		*/
		Hoop(sf::Vector2f limitMin, sf::Vector2f limitMax);
		
		//! This object is marked for deletion as a contact with the Ball has occured.
		bool m_bCanBeDestroyed;
};