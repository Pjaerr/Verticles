#include "Physics.h"

/*! The deconstructor deallocates memory for the b2World.*/
Physics::~Physics()
{
	delete m_world;
}

/*!
*	The constructor stores the gravity, velocity iterations and position iterations
*	and then sets up a new b2World with the given gravity.
*/
Physics::Physics(b2Vec2 gravity, int iVelocityIterations, int iPositionIterations, b2Vec2 worldSize)
{
	m_worldSize = worldSize;

	m_gravity = gravity;
	m_iVelocityIterations = iVelocityIterations;
	m_iPositionIterations = iPositionIterations;

	m_world = new b2World(m_gravity);

	m_world->SetContactListener(&m_contactListener);
}

/*!
*	updateWorld calls b2World::Step() with the given elapsed time and the stored number of
*	velocity and position iterations. This should be called every frame at a constant FPS.
*/
void Physics::m_updateWorld(float fElapsedTime)
{
	m_world->Step(fElapsedTime, m_iVelocityIterations, m_iPositionIterations);
}

/*! Returns the b2World that this object uses.*/
b2World* Physics::m_getWorld()
{
	return m_world;
}

/*! Returns m_worldSize.*/
b2Vec2 Physics::m_getWorldSize()
{
	return m_worldSize;
}
