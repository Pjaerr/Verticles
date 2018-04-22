#include "Goal.h"

/*! Sets up the static body as a circle using the given position and radius. Passed in
a pointer to this object so that collisions can be managed in here as opposed to the static body
itself. It also sets this Body's tag to be "Goal" so that this specific object can be referenced when
a collision occurs.*/
Goal::Goal(sf::Texture* texture, b2Vec2 pos, float fRadius, b2World * world)
{
	m_setupBodyAsCircle(b2_staticBody, pos, fRadius, world, this, true); //Setup the body as a sensor.

	m_setTag("Goal");

	m_setupSprite(texture);
}

/*! Initialises the sprite as per the texture file path and this object's static body's
* position, rotation and radius.*/
void Goal::m_setupSprite(sf::Texture* texture)
{
	m_circle = sf::CircleShape(m_fGetRadius());

	m_circle.setOrigin(m_fGetRadius(), m_fGetRadius());

	m_circle.setPosition(m_getPosition().x, m_getPosition().y);
	
	m_circle.setRotation(m_fGetRotation());

	m_circle.setTexture(texture);
}

/*! The virtual draw function taken from sf::Drawable.*/
void Goal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_circle);
}

/*! Functionality overridden from Body::onCollisionEnter(Body * otherBody)*/
void Goal::onCollisionEnter(Body * otherBody)
{
}

/*! Functionality overridden from Body::onCollisionExit(Body * otherBody)*/
void Goal::onCollisionExit(Body * otherBody)
{
	
}