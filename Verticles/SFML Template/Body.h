#pragma once
#include <Box2D\Box2D.h>


/*! \file Body.h
* The class that interfaces with Box2D and acts as a 'container' for objects
* in the physical game world.
*
* This class should be inherited by objects which require physics, passing in their b2BodyType
* as a parameter on setup.
*/

#define DEG2RAD 0.017453f; //!< To convert degrees to radians.
#define RAD2DEG 57.29577f; //!< To convert radians to degrees.

class Body
{
	public:
		/*! \brief Returns the position of the protected b2Body.*/
		b2Vec2 getPosition();
		float getRotation();
		float getRadius();
		b2Vec2 getSize();

	private:
		float m_fDensity = 1.0f; //!< The density to be applied to the fixture that m_body uses.
		float m_fFriction = 0.4f; //!< The friction to be applied to the fixture that m_body uses.
		float m_fRestitution = 0.6f; //!< The restitution to be applied to the fixture that m_body uses.

		float m_fRadius = 0.0f;
		b2Vec2 m_size;

		b2Body *m_body = nullptr; //!< The box2D body that controls all of the physics for the object inheriting this class.

		void setupBody(b2BodyType bodyType, const b2Shape* shapeb2Vec2, b2Vec2 position, float fRotation, b2World * world, void * self, bool isSensor);

	protected:
		/*! \brief Sets the density, friction and restitution of this body.
		*	\param fDensity The density of this body.
		*	\param fFriction The friction of this body.
		*	\param fRestitution The restitution of this body.
		*/
		void setAttributes(float fDensity, float fFriction, float fRestitution);

		void setupBodyAsBox(b2BodyType bodyType, b2Vec2 position, b2Vec2 size, float fRotation, b2World * world, void * self, bool isSensor);
		void setupBodyAsCircle(b2BodyType bodyType, b2Vec2 position, float fRadius, b2World * world, void * self, bool isSensor);
};

