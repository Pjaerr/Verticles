#pragma once

#include <SFML\Graphics.hpp>
#include "Trigger.h"

class Hoop : public sf::Sprite, public Trigger
{
	public:
		Hoop(sf::Vector2f& position, sf::Vector2f limitMin, sf::Vector2f limitMax);
		
		bool m_bCanBeDestroyed; //Marked for deletion as a contact has occurred.
		void destroy(); //Will delete the object
	
	private:
		float m_fWidth;
		float m_fHeight;
}