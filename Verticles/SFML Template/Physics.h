#pragma once
#include <Box2D\Box2D.h>
#include "ContactListener.h"

/*!\class Physics
*	\brief The cass responsible for the b2World used to update physics in the game.
*
*	Holds the b2World, and contains functionality for updating the world as well as returning
*	the world. It also holds the contact listener used to listen for object.
*/
class Physics
{
	public:
		~Physics();

		/*! \brief The constructor for the Physics class. Sets up the b2World.*/
		/*!
		\param gravity The gravity on the x and y that the b2World will use.
		\param iVelocityIterations The number of velocity iterations on each world update.
		\param iPositionIterations The number of position iterations on each world update.
		*/
		Physics(b2Vec2 gravity, int iVelocityIterations, int iPositionIterations, b2Vec2 worldSize);

		/*! \brief The function that updates the physics world when called.*/
		/*!
		\param fElapsedTime The time that has elapsed since it was last called.
		*/
		void m_updateWorld(float fElapsedTime);

		/*! \brief Returns the b2World being used.*/
		b2World* m_getWorld();

		b2Vec2 m_worldSize;

		b2Vec2 m_getWorldSize();

	private:
		int m_iVelocityIterations; //!< The number of velocity iterations on each world update.
		int m_iPositionIterations; //!< The number of position iterations on each world update.
		ContactListener m_contactListener;
		b2Vec2 m_gravity; //!< The gravity this b2World uses.
		b2World *m_world = nullptr; //!< Pointer to the b2World the game uses.
};