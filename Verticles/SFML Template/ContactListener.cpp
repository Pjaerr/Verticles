#include "ContactListener.h"

/*! Called when two bodies begin to touch.*/
void ContactListener::BeginContact(b2Contact * contact)
{
	b2Body* b2bodyA = contact->GetFixtureA()->GetBody();
	b2Body* b2bodyB = contact->GetFixtureB()->GetBody();

	Body * bodyA = static_cast<Body*>(b2bodyA->GetUserData());
	Body * bodyB = static_cast<Body*>(b2bodyB->GetUserData());

	if (bodyA != nullptr && bodyB != nullptr)
	{
		bodyA->onCollisionEnter(bodyB);
		bodyB->onCollisionEnter(bodyA);
	}
	else
	{
		std::cout << "BeginContact: One of the bodies involved in the collision was a nullptr" << std::endl;
	}
}

/*! Called when two bodies stop touching.*/
void ContactListener::EndContact(b2Contact * contact)
{
	b2Body* b2bodyA = contact->GetFixtureA()->GetBody();
	b2Body* b2bodyB = contact->GetFixtureB()->GetBody();

	Body * bodyA = static_cast<Body*>(b2bodyA->GetUserData());
	Body * bodyB = static_cast<Body*>(b2bodyB->GetUserData());

	if (bodyA != nullptr && bodyB != nullptr)
	{
		bodyA->onCollisionExit(bodyB);
		bodyB->onCollisionExit(bodyA);
	}
	else
	{
		std::cout << "EndContact: One of the bodies involved in the collision was a nullptr" << std::endl;
	}
}
