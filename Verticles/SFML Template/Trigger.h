#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class Trigger
{
	/**works like the Rigidbody2D class in that the body is set through the constructor
	the only difference being it doesn't need to use any of the density, friction or
	restitution, it just sets the fixture.isSensor to true.*/
	public:
		Trigger();
		sf::Vector2f getPosition(); //returns position of the body.
	
	protected:
		b2Body *body;
}