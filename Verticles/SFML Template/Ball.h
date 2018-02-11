#include <SFML\Graphics.hpp>
#include "Rigidbody2D.h"


/*! \file Ball.h
* The class that acts as the Ball within the game. It exists as a sprite which is a Rigidbody2D and
* can be moved around via the use of Rigidbody2D::applyForce() which will be carried out via the 
* Control class that makes use of keyboard input.
*/

class Ball : public sf::Sprite, public Rigidbody2D
{
	public:
		/*! \brief Initialises the ball with a given position, radius and orientation.
		*
		*
		*	The constructor for the Ball will setup the Rigidbody2D on this class as well
		*	as the sprite associated with this class.
		*/
		/*!
		\param position The position the Ball's sf::Sprite and Rigidbody2D will start at.
		\param radius The radius that the Rigidbody2D will set the Box2D body to.
		\param orientation The rotation that the Ball's sf::Sprite and Rigidbody2D will start at.
		\param world A reference to the Box2D world so that the body can be created.
		*/
		Ball(const sf::Vector2f& position, const float radius, const float orientation, b2World * world);
		
		/**Sets the position of this ball (ie. its sf::CircleShape setPosition()) to be
		equal to the current position of the Rigidbody2D and the rotation of this ball to be
		equal to the -current rotation of the Rigidbody2D*/

		/*! \brief Keeps both the Ball's sf::Sprite and Rigidbody2D up to date.
		*	
		*
		*	Sets the position of this Ball's sf::Sprite to be equal to the current position of the
		*	Rigidbody2D and the rotation of this Ball's sf::Sprite to be equal to the current rotation
		*	of the Rigidbody2D.
		*/
		void update();
	
	private:
		//! The radius of the Rigidbody2D::m_body associated with this object.
		float m_radius;
}