#pragma once
#include "Hoop.h"
#include <vector>

class Level
{
	public:
		Level();
		int m_numberOfHoops;
		std::vector<Hoop> getHoops();

	private:
		std::vector<Hoop> hoops;
};