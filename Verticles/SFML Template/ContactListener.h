#pragma once
#include <Box2D\Box2D.h>


class ContactListener : public b2ContactListener
{
	public:
		/*Functions that get called when a contact occurs, these are overidden via b2ContactListener*/
		virtual void BeginContact(b2Contact * contact);
		virtual void EndContact(b2Contact * contact);


	private:
};