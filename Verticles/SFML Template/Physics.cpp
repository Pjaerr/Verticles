#include "Physics.h"

Physics::Physics()
{

}

/*!
*	The constructor stores the gravity, velocity iterations and position iterations
*	and then sets up a new b2World with the given gravity.
*/
Physics::Physics(b2Vec2 gravity, int iVelocityIterations, int iPositionIterations)
{
	mk_gravity = gravity;
	m_iVelocityIterations = iVelocityIterations;
	m_iPositionIterations = iPositionIterations;

	m_world = new b2World(mk_gravity);
}

/*!
*	updateWorld calls b2World::Step() with the given elapsed time and the stored number of
*	velocity and position iterations. This should be called every frame at a constant FPS.
*/
void Physics::updateWorld(float fElapsedTime)
{
	m_world->Step(fElapsedTime, m_iVelocityIterations, m_iPositionIterations);
}

/*! Returns the b2World that this object uses.*/
b2World* Physics::getWorld()
{
	return m_world;
}