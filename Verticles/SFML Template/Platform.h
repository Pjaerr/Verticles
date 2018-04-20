#pragma once

#include "Body.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*!\class Platform
*	\brief The class that acts as a static collidable platform in the game world.
*/
class Platform : public Body, public sf::Drawable
{
	private:
		sf::RectangleShape m_rect; //!< The shape drawn the the screen.

		/*! \brief Initialises the sprite as per the texture file path and this object's dynamic body.
		*	\param textureFilePath The path to the texture this object's sprite should use.
		*/
		void m_setupRect();

		/*OVERRIDEN FUNCTIONALITY FROM BODY.H*/
		void onCollisionEnter(Body * otherBody);
		void onCollisionExit(Body * otherBody);

	public:
		/*! \brief Intialises the dynamic body and calls the m_setupSprite function.
		*	\param textureFilePath The path to the texture this object's sprite should use.
		*	\param pos The x and y position this object will start at.
		*	\param size The width and height of this object's sprite.
		*	\param world Pointer to the b2World being used to manage the physics.
		*/
		Platform(b2Vec2 pos, b2Vec2 size, float fRotation, b2World * world);

		~Platform();

		/*! \brief The virtual draw function taken from sf::Drawable.*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
