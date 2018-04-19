#pragma once

/*!
\file ContactListener.h
*/

#include <iostream>
#include "Body.h"

/*!\class ContactListener
*	\brief The class that is reponsible for listening for a contact between two Body objects.
*	
*	Calls the OnCollisionEnter/Exit function of both of the Body's involved in the contact
*	whilst passing the other Body involved to each Body.
*/
class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};