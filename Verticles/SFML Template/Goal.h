#pragma once
#include "SFML\Graphics.hpp"
#include "Body.h"


/*!\class Goal
*	\brief The object that acts as a goal within the game world.
*/
class Goal : public Body, public sf::Drawable
{
private:
	sf::CircleShape m_circle; //!< The object drawn to represent the goal.

	/*! \brief Initialises the sprite as per the texture file path and this object's dynamic body.
	*	\param textureFilePath The path to the texture this object's sprite should use.
	*/
	void m_setupSprite(sf::Texture* texture);

	/*! Functionality overridden from Body::onCollisionEnter(Body * otherBody)*/
	void onCollisionEnter(Body * otherBody);

	/*! Functionality overridden from Body::onCollisionExit(Body * otherBody)*/
	void onCollisionExit(Body * otherBody);
public:
	/*! \brief Intialises the static body and calls the m_setupSprite function.
	*	\param textureFilePath The path to the texture this object's sprite should use.
	*	\param pos The x and y position this object will start at.
	*	\param fRadius The width and height of this object's sprite.
	*	\param world Pointer to the b2World being used to manage the physics.
	*/
	Goal(sf::Texture* texture, b2Vec2 pos, float fRadius, b2World * world);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};