#include "Ball.h"

/*! Sets up the dynamic body as a circle using the given position and radius. Passed in
a pointer to this object so that collisions can be managed in here as opposed to the dynamic body
itself.*/
Ball::Ball(sf::Texture * texture, b2Vec2 pos, float fRadius, b2World * world)
{
	m_setupBodyAsCircle(b2_dynamicBody, pos, fRadius, world, this, false);

	m_setTag("Ball");

	m_setupTexture(texture);
}

/*! Functionality overridden from Body::onCollisionEnter(Body * otherBody)*/
void Ball::onCollisionEnter(Body * otherBody)
{
	if (otherBody->m_tag == "Goal")
	{
		m_bHasHitGoal = true;
	}
}

/*! Functionality overridden from Body::onCollisionExit(Body * otherBody)*/
void Ball::onCollisionExit(Body * otherBody)
{
	
}

/*! Initialises the sprite as per the texture file path and this object's dynamic body's 
* position, rotation and radius.
*/
void Ball::m_setupTexture(sf::Texture * texture)
{
	m_circle = sf::CircleShape(m_fGetRadius());
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());

	//Set to the same rotation as the dynamic body.
	float rot = -m_fGetRotation() * RAD2DEG;
	m_circle.setRotation(rot);

	m_circle.setPosition(m_getPosition().x, m_getPosition().y);

	m_circle.setTexture(texture);
}

/*! Sets the position and rotation of this object's sprite to that of the body.*/
void Ball::m_update()
{
	m_circle.setPosition(m_getPosition().x, m_getPosition().y);
	m_circle.setRotation(m_fGetRotation());
}

/*! The virtual draw function taken from sf::Drawable.*/
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_circle);
}