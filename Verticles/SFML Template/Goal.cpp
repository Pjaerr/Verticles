#include "Goal.h"

/*! Sets up the static body as a circle using the given position and radius. Passed in
a pointer to this object so that collisions can be managed in here as opposed to the static body
itself. It also sets this Body's tag to be "Goal" so that this specific object can be referenced when
a collision occurs.*/
Goal::Goal(std::string textureFilePath, b2Vec2 pos, float fRadius, b2World * world)
{
	setupBodyAsCircle(b2_staticBody, pos, fRadius, world, this, true); //Setup the body as a sensor.

	m_setTag("Goal");

	m_setupSprite(textureFilePath);
}

/*! Initialises the sprite as per the texture file path and this object's static body's
* position, rotation and radius.*/
void Goal::m_setupSprite(std::string textureFilePath)
{
	m_texture = sf::Texture();

	if (!m_texture.loadFromFile(textureFilePath))
	{
		std::cout << "Cannot read file at " << textureFilePath << std::endl;
		return;
	}

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(getPosition().x, getPosition().y); //Set to same position as the dynamic body.
	m_sprite.setScale(getRadius(), getRadius()); //Set to the same radius as the dynamic body.
	m_sprite.setOrigin(getRadius() * 0.5f, getRadius() * 0.5f); //Set origin to center of the sprite.

																//Set to the same rotation as the dynamic body.
	float rot = -getRotation() * RAD2DEG;
	m_sprite.setRotation(rot);

	circle = sf::CircleShape(getRadius());
	circle.setPosition(getPosition().x, getPosition().y);
	circle.setOrigin(getRadius() * 0.5f, getRadius() * 0.5f);
	circle.setFillColor(sf::Color::Red);
}

/*! The virtual draw function taken from sf::Drawable.*/
void Goal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle);
}

/*! Functionality overridden from Body::onCollisionEnter(Body * otherBody)*/
void Goal::onCollisionEnter(Body * otherBody)
{
	circle.setFillColor(sf::Color::Blue);
}

/*! Functionality overridden from Body::onCollisionExit(Body * otherBody)*/
void Goal::onCollisionExit(Body * otherBody)
{
	circle.setFillColor(sf::Color::Red);
}