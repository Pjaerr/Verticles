#include "Rigidbody2D.h"

/*When passed a reference to a b2FixtureDef, it will set that fixture's density, friction and restitution to be
equal to the const member variables for those respective values. It does not set the shape associated with the fixture,
that must set after making a call to this function.*/
void Rigidbody2D::setupFixtureAttributes(b2FixtureDef &fixture)
{
	fixture.density = mk_fDensity;
	fixture.friction = mk_fFriction;
	fixture.restitution = mk_fRestitution;
}

sf::Vector2f Rigidbody2D::getPosition()
{
	return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y);
}

void Rigidbody2D::applyForce(float x, float y, float intensity)
{

}