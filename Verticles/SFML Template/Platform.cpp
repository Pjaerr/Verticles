#include "Platform.h"

/*! Sets up the static body as a box using the given position and size. Passed in
a pointer to this object so that collisions can be managed in here as opposed to the dynamic body
itself.*/
Platform::Platform(b2Vec2 pos, b2Vec2 size, float fRotation, b2World * world)
{
	setupBodyAsBox(b2_staticBody, pos, size, fRotation, world, this, false);
	m_setupRect();
}

/*! Initialises the sprite as per the texture file path and this object's static body's
* position, rotation and radius.
*/
void Platform::m_setupRect()
{
	m_rect = sf::RectangleShape(sf::Vector2f(getSize().x, getSize().y)); //Set to the same size as the static body.
	m_rect.setPosition(getPosition().x, getPosition().y); //Set to same position as the static body.
	m_rect.setOrigin(getSize().x * 0.5f, getSize().y * 0.5f); //Set origin to center of the rectangle.

	//Set to the same rotation as the static body.
	float rot = getRotation() * RAD2DEG;

	m_rect.setRotation(rot);

	m_rect.setFillColor(sf::Color::Green);
}

/*! The virtual draw function taken from sf::Drawable.*/
void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_rect);
}

void Platform::onCollisionEnter(Body * otherBody)
{
	
}

void Platform::onCollisionExit(Body * otherBody)
{
	
}