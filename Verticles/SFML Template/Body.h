#pragma once
#include <Box2D\Box2D.h>
#include <iostream>

/*! \file Body.h
* The class that interfaces with Box2D and acts as a 'container' for objects
* in the physical game world.
*
* This class should be inherited by objects which require physics, passing in their b2BodyType
* as a parameter on setup.
*/

#define DEG2RAD 0.017453f; //!< To convert degrees to radians.
#define RAD2DEG 57.29577f; //!< To convert radians to degrees.

/*! \class Body
*	\brief The class that interfaces with Box2D and acts as a 'container' for objects in the physical game world.
*
* This class should be inherited by objects which require physics, passing in their b2BodyType
* as a parameter on setup.
*/
class Body
{
public:
	/*! \brief Destroys the b2Body associated with this object.*/
	void m_destroySelf();

	/*! \brief Returns the position of the protected b2Body.*/
	b2Vec2 m_getPosition();

	/*! \brief Returns the rotation of the protected b2Body.*/
	float m_fGetRotation();

	/*! \brief Returns the radius set when the body was created.*/
	float m_fGetRadius();

	/*! \brief Returns the size set when the body was created.*/
	b2Vec2 getSize();

	/*! Should be overwritten by child class. Whatever is inside of the function will be called when
	the body inherited by the child collides with another body.
	*\param otherBody The other body involved in the collision.*/
	virtual void onCollisionEnter(Body * otherBody);

	/*! Should be overwritten by child class. Whatever is inside of the function will be called when
	the body inherited by the child collides with another body.
	*\param otherBody The other body involved in the collision.*/
	virtual void onCollisionExit(Body * otherBody);

	bool m_bIsSensor = false; //!< Is the b2Body this Body uses a sensor?

	std::string m_tag = ""; //!< The tag that will identify this Body if assigned.

	private:
		float m_fDensity = 1.0f; //!< The density to be applied to the fixture that m_body uses.
		float m_fFriction = 0.4f; //!< The friction to be applied to the fixture that m_body uses.
		float m_fRestitution = 0.4f; //!< The restitution to be applied to the fixture that m_body uses.

		float m_fRadius = 0.0f; //!< The radius to set this body to (if a circle shape).

		b2Vec2 m_size; //!< the size to set this body to (if a box shape).

		b2Body *m_body = nullptr; //!< The box2D body that controls all of the physics for the object inheriting this class.

		/*! \brief Sets up the fixture, shape and body of this class.
		*	\param bodyType b2BodyType enum referring to the type of this body.
		*	\param shape The b2Shape referring to the shape of this body.
		*	\param position The b2Vec2 (x, y) position the body should be placed at.
		*	\param fRotation The angle at which the body should be rotated.
		*	\param world The b2World that this body should work within.
		*	\param self A pointer to the class that this body is created on.
		*/
		void m_setupBody(b2BodyType bodyType, const b2Shape* shape, b2Vec2 position, float fRotation, b2World * world, void * self, bool isSensor);

	protected:
		/*! \brief Sets the density, friction and restitution of this body.
		*	\param fDensity The density of this body.
		*	\param fFriction The friction of this body.
		*	\param fRestitution The restitution of this body.
		*/
		void m_setAttributes(float fDensity, float fFriction, float fRestitution);

		/*! \brief Sets up this body as a box.
		*	\param bodyType b2BodyType enum referring to the type of this body.
		*	\param position The b2Vec2 (x, y) position the body should be placed at.
		*	\param size The width and height of this body.
		*	\param fRotation The angle at which the body should be rotated.
		*	\param world The b2World that this body should work within.
		*	\param self A pointer to the class that this body is created on.
		*	\param isSensor Whether this body is a sensor or not.
		*/
		void m_setupBodyAsBox(b2BodyType bodyType, b2Vec2 position, b2Vec2 size, float fRotation, b2World * world, void * self, bool isSensor);

		/*! \brief Sets up this body as a circle.
		*	\param bodyType b2BodyType enum referring to the type of this body.
		*	\param position The b2Vec2 (x, y) position the body should be placed at.
		*	\param radius The radius of this body.
		*	\param world The b2World that this body should work within.
		*	\param self A pointer to the class that this body is created on.
		*	\param isSensor Whether this body is a sensor or not.
		*/
		void m_setupBodyAsCircle(b2BodyType bodyType, b2Vec2 position, float fRadius, b2World * world, void * self, bool isSensor);

		/*! \brief Sets the tag that this Body should be associated with.
		*	\param tag The tag.
		*/
		void m_setTag(std::string tag);
};

