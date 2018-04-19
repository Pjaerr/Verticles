#include "Ball.h"

/*! Sets up the dynamic body as a circle using the given position and radius. Passed in
a pointer to this object so that collisions can be managed in here as opposed to the dynamic body
itself.*/
Ball::Ball(std::string textureFilePath, b2Vec2 pos, float fRadius, b2World * world)
{
	m_setupBodyAsCircle(b2_dynamicBody, pos, fRadius, world, this, false);

	m_setTag("Ball");

	m_setupSprite(textureFilePath);
}

/*! Functionality overridden from Body::onCollisionEnter(Body * otherBody)*/
void Ball::onCollisionEnter(Body * otherBody)
{
	if (otherBody->m_tag == "Goal")
	{
		m_bHasHitGoal = true;
		circle.setFillColor(sf::Color::Magenta);
		std::cout << "Ball has touched a goal" << std::endl;
	}
	else
	{
		circle.setFillColor(sf::Color::Blue);
	}
	
}

/*! Functionality overridden from Body::onCollisionExit(Body * otherBody)*/
void Ball::onCollisionExit(Body * otherBody)
{
	circle.setFillColor(sf::Color::Red);
}

/*! Initialises the sprite as per the texture file path and this object's dynamic body's 
* position, rotation and radius.
*/
void Ball::m_setupSprite(std::string textureFilePath)
{
	m_texture = sf::Texture();

	if (!m_texture.loadFromFile(textureFilePath))
	{
		std::cout << "Cannot read file at " << textureFilePath << std::endl;
		return;
	}

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_getPosition().x, m_getPosition().y); //Set to same position as the dynamic body.
	m_sprite.setScale(m_fGetRadius(), m_fGetRadius()); //Set to the same radius as the dynamic body.
	m_sprite.setOrigin(m_fGetRadius() * 0.5f, m_fGetRadius() * 0.5f); //Set origin to center of the sprite.

	//Set to the same rotation as the dynamic body.
	float rot = -m_fGetRotation() * RAD2DEG; 
	m_sprite.setRotation(rot);

	circle = sf::CircleShape(m_fGetRadius());
	circle.setPosition(m_getPosition().x, m_getPosition().y);
	circle.setOrigin(m_fGetRadius() * 0.5f, m_fGetRadius() * 0.5f);
	circle.setFillColor(sf::Color::Red);
}

/*! Sets the position and rotation of this object's sprite to that of the body.*/
void Ball::m_update()
{
	//m_sprite.setPosition(getPosition().x, getPosition().y);

	float angle = m_fGetRotation();

	//m_sprite.setRotation(angle);

	circle.setPosition(m_getPosition().x, m_getPosition().y);

	circle.setRotation(angle);
}

/*! The virtual draw function taken from sf::Drawable.*/
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle);
}