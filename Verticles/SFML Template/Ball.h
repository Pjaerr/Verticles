#include "Body.h"
#include <iostream>
#include <SFML\Graphics.hpp>

/*! \file Ball.h
* The class that controls the balls that fall when a level begins. These are lightweight
* dynamic bodies that have a starting position and will fall as per gravity at the start of a level.
*/

class Ball : public sf::Drawable,  public Body
{
	private:
		sf::Sprite m_sprite; //!< The sprite that is drawn when this object is passed into window.draw()
		sf::Texture m_texture; //!< The texture applied to the sprite.

		sf::CircleShape circle;

		/*! \brief Initialises the sprite as per the texture file path and this object's dynamic body.
		*	\param textureFilePath The path to the texture this object's sprite should use.
		*/
		void m_setupSprite(std::string textureFilePath);

	public:
		/*! \brief Intialises the dynamic body and calls the m_setupSprite function.
		*	\param textureFilePath The path to the texture this object's sprite should use.
		*	\param pos The x and y position this object will start at.
		*	\param fRadius The width and height of this object's sprite.
		*	\param world Pointer to the b2World being used to manage the physics.
		*/
		Ball(std::string textureFilePath, b2Vec2 pos, float fRadius, b2World * world);

		/*! \brief Sets the position and rotation of this object's sprite to that of the body.*/
		void m_update();

		/*! \brief The virtual draw function taken from sf::Drawable.*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};