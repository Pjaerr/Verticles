#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

/*! \file Trigger.h
* Works like a Rigidbody2D class in that the body is set through the constructor of the child class.
* The only difference being it doesn't need to use any of the density, friction or restitution as it
* will just set the fixture.isSensor to true.
*
* This class should be inherited by an object that wants to check for collisions without affecting
* other physical objects in the world.
*/

class Trigger
{
	public:
		//! Returns the position of the Box2D body on this object.
		sf::Vector2f getPosition();
	
private:

	protected:
		//! The Box2D body that is used by this object.
		b2Body *m_body;
};