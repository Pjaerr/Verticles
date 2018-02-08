#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>


#define DEG2RAD 0.017453f;
#define RAD2DEG 57.29577f;

class Rigidbody2D
{
	public:
		sf::Vector2f getPosition(); //returns position of the body.
		void applyForce(float x, float y, float intensity);
	
	private:
		
		const float mk_fDensity = 1.0f;
		const float mk_fFriction = 0.4f;
		const float mk_fRestitution = 0.6f;

	protected:
		b2Body *m_body;
		void setupFixtureAttributes(b2FixtureDef &fixture);
};