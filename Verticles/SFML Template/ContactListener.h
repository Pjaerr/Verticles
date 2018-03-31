#pragma once

/*!
\file ContactListener.h
*/

#include <iostream>
#include "Body.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};