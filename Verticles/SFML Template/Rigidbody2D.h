#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>


/*! \file Rigidbody2D.h
* The class that interfaces with Box2D and acts as a 'container' for objects
* in the game world that need to be used as if they were physical dynamic
* bodies. Contains a Box2D body and functions to provide a level of abstraction
* from that Box2D body.
*
* The Rigidbody2D class should be inherited by an object that needs to be affected by physics and should
* initialise the Box2D body in its own constructor.
*/

#define DEG2RAD 0.017453f; //!< To convert degrees to radians.
#define RAD2DEG 57.29577f; //!< To convert radians to degrees.

class Rigidbody2D
{
	public:
		/*! \brief Returns the position of the protected b2Body.*/
		sf::Vector2f getPosition();

		/*! \brief Applies a force to the b2Body.
		/*!
		\param x The intensity of the force on the x.
		\param y The intensity of the force on the y.
		*/
		void applyForce(float x, float y);
	
	private:
		const float mk_fDensity = 1.0f; //!< The density to be applied to the fixture that m_body uses.
		const float mk_fFriction = 0.4f; //!< The friction to be applied to the fixture that m_body uses.
		const float mk_fRestitution = 0.6f; //!< The restitution to be applied to the fixture that m_body uses.

	protected:
		b2Body *m_body = nullptr; //!< The box2D body that controls all of the physics for the object inheriting this class.

		/*! \brief Applies the member density, friction and resitution to the referenced fixture.
		/*!
		\param &fixture A reference to the fixture on which to apply density, friction and resitution.
		*/
		void setupFixtureAttributes(b2FixtureDef &fixture);
};