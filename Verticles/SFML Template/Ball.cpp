#include "Ball.h"
#include <iostream>

/*!
*	The Ball constructor sets up the Rigidbody2D that this class inherits from. This, in turn, sets up
*	the b2Body that this object uses. The constructor also sets up the sf::Sprite that this object uses.
*/
Ball::Ball(const sf::Vector2f& position, const float radius, const float orientation, b2World * world)
{
	/*Setup Rigidbody2D associated with this Ball*/
	b2BodyDef bodyDef;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.type = b2_dynamicBody; //! Set this body def as a dynamic body.

	m_body = world->CreateBody(&bodyDef); //! Initialise the body belonging to this Rigidbody2D via the world.
	m_body->SetUserData(this); //! Store a pointer to this object to be used when involved in a contact.

	circleShape.m_radius = radius; //! Setup the shape of the body. In this case, a circle with a radius.

	setupFixtureAttributes(fixtureDef); //! Setup density, friction and restitution.
	fixtureDef.shape = &circleShape;
	
	/*! Setup the sf::Sprite associated with this object.*/
	setPosition(position);
	setScale(radius, radius);
	setOrigin(radius * 0.5f, radius * 0.5f);
	setRotation(-orientation);
}

/*!
*	Sets the position of this Ball's sf::Sprite to be equal to the current position of the
*	Rigidbody2D and the rotation of this Ball's sf::Sprite to be equal to the current rotation
*	of the Rigidbody2D.
*/
void Ball::update()
{
	b2Vec2 position = m_body->GetPosition(); //! Store the position of this object's b2Body

	setPosition(position.x, position.y); //! Set the position of this object's sf::Sprite to the position of its b2Body

	float angle = -m_body->GetAngle() * RAD2DEG; //! Store this object's b2Body rotation.
	setRotation(angle); //! Set the rotation of this object's sf::Sprite to the rotaqtion of its b2Body.
}

/*!
*	Takes a filePath and grabs the image at that filePath and assigns to the m_texure and
*	then sets the texure of this sf::Sprite to be m_texture.
*/
void Ball::setupTextureFromFile(std::string filePath)
{
	m_texture = sf::Texture();
	m_texture.loadFromFile(filePath); //! Load texture from filePath.
	setTexture(m_texture); //! Set this object's sf::Sprite's texture.
}