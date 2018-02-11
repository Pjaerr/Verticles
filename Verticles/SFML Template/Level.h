#pragma once
#include "Hoop.h"
#include <vector>

/*! \file Level.h
* The class used to manage the level and level objects. Will randomly place a number of Hoop objects as well as
* creating new ones when a contact occurs between the Ball and the Hoop.
*/

class Level
{
	public:
		//! This object's constructor. Will initialise the hoops.
		Level();

		//! The number of hoops within the level.
		int m_numberOfHoops;

		//! Returns the private hoops vector.
		std::vector<Hoop> getHoops();

	private:
		//! A vector of Hoop objects.
		std::vector<Hoop> hoops;
};