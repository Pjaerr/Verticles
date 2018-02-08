#include <SFML\Graphics.hpp>
#include "Rigidbody2D.h"


class Ball : public sf::Sprite, public Rigidbody2D
{
	public:
		/**setPosition(postion) for the CircleShape and setting m_radius to radius.
		Then the ball will create a b2BodyDef, b2CircleShape and b2FixtureDef inside of this
		constructor, give the bodyDef its type and position and then using the b2World passed
		in via Game, it will set this rigidbody's body via world->CreateBody(bodyDef), where bodyDef is
		the previously created bodyDef. It will then set the fixtureDef's values so that they are equal
		to the private attributes (density, friction and restitution) on the rigidbody and then set the
		fixture of the body via body->CreateFixture()*/
		
		Ball(const sf::Vector2f& position, const float radius, const float orientation, b2World * world);
		
		/**Sets the position of this ball (ie. its sf::CircleShape setPosition()) to be
		equal to the current position of the Rigidbody2D and the rotation of this ball to be
		equal to the -current rotation of the Rigidbody2D*/
		void update();
	
	private:
		float m_radius;
}