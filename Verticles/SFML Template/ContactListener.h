#pragma once
#include <Box2D\Box2D.h>

/*! \file ContactListener.h
* Checks for a contact between a Ball and a Hoop. When this contact occurs tell the
* Hoop involved to mark itself for deletion, and then at the end of the game loop, any
* Hoops involved will be deleted. (Managed by Level.h)
*/

class ContactListener : public b2ContactListener
{
	public:
		//! BeginContact gets called when a contact has occured, this is overidden by b2ContactListener
		virtual void BeginContact(b2Contact * contact);

		//! EndContact gets called when a contact has ended, this is overidden by b2ContactListener
		virtual void EndContact(b2Contact * contact);
};