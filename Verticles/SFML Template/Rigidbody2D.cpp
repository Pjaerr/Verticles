#include "Rigidbody2D.h"
#include <iostream>

/*!
*	When passed a reference to a b2FixtureDef, it will set that fixture's density, friction and restitution to be
*	equal to the const member variables for those respective values. It does not set the shape associated with the fixture,
*	that must set after making a call to this function.
*/
void Rigidbody2D::setupFixtureAttributes(b2FixtureDef &fixture)
{
	fixture.density = mk_fDensity;
	fixture.friction = mk_fFriction;
	fixture.restitution = mk_fRestitution;
}

/*! Returns, as an sf::Vector2f, the position of this object's b2Body.*/
sf::Vector2f Rigidbody2D::getPosition()
{
	return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y);
}

/*!
*	Applies a linear impulse force to the b2Body that this object uses with the given
*	x and y. It reverses the y value to make the application of force more readable when
*	called externally.
*/
void Rigidbody2D::applyForce(float x, float y)
{
	m_body->ApplyLinearImpulse(b2Vec2(x, -y), m_body->GetWorldCenter(), false);
}