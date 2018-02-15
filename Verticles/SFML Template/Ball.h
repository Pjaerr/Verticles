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
		/*! \brief Initialises the ball with a given position, radius and orientation.*/
		/*!
		\param position The position the Ball's sf::Sprite and Rigidbody2D will start at.
		\param radius The radius that the Rigidbody2D will set the Box2D body to.
		\param orientation The rotation that the Ball's sf::Sprite and Rigidbody2D will start at.
		\param world A reference to the Box2D world so that the body can be created.
		*/
		Ball(const sf::Vector2f& position, const float radius, const float orientation, b2World * world);

		/*! \brief Keeps both the Ball's sf::Sprite and Rigidbody2D up to date.*/
		void update();

		/*! \brief Sets m_texture to the image located at the given file path.*/
		/*!
		\param filePath The file path of the image to be loaded into the sf::Texture
		*/
		void setupTextureFromFile(std::string filePath);
	
	private:
		float m_radius; //!< The radius of the Rigidbody2D::m_body associated with this object.

		sf::Texture m_texture; //!< The texture this sprite uses when assigned via setupTextureFromFile()
};