#pragma once
#include <Box2D\Box2D.h>
#include "ContactListener.h"

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
		Physics(b2Vec2 gravity, int iVelocityIterations, int iPositionIterations);

		/*! \brief The function that updates the physics world when called.*/
		/*!
		\param fElapsedTime The time that has elapsed since it was last called.
		*/
		void updateWorld(float fElapsedTime);

		/*! \brief Returns the b2World being used.*/
		b2World* getWorld();

	private:
		int m_iVelocityIterations; //!< The number of velocity iterations on each world update.
		int m_iPositionIterations; //!< The number of position iterations on each world update.
		ContactListener m_contactListener;
		b2Vec2 mk_gravity; //!< The gravity this b2World uses.
		b2World *m_world = nullptr; //!< Pointer to the b2World the game uses.
};