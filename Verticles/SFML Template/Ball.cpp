#include "Ball.h"
#include <iostream>

Ball::Ball(const sf::Vector2f& position, const float radius, const float orientation, b2World * world)
{
	/*Setup Rigidbody2D associated with this Ball*/
	b2BodyDef bodyDef;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.type = b2_dynamicBody; //Set this body def as a dynamic body.

	m_body = world->CreateBody(&bodyDef); //Initialise the body belonging to this Rigidbody2D via the world.
	m_body->SetUserData(this); //Store a pointer to this object to be used when involved in a contact.

	circleShape.m_radius = radius; //Setup the shape of the body. In this case, a circle with a radius.

	setupFixtureAttributes(fixtureDef); //Setup density, friction and restitution.
	fixtureDef.shape = &circleShape;
	
	/*Setup the sf::Sprite associated with this object.*/
	setPosition(position);
	setOrigin(radius, radius);
	setRotation(-orientation);
}

void Ball::update()
{
	b2Vec2 position = m_body->GetPosition();
	setPosition(position.x, position.y);

	float angle = -m_body->GetAngle() * RAD2DEG;
	setRotation(angle);
}