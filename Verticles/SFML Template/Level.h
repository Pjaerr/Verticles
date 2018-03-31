#pragma once

#include "Ball.h"
#include "Platform.h"

class Level
{
private:
	std::vector<Ball*> m_balls;
	std::vector<Platform *> m_platforms;
	//std::vector<Goal *> m_goals;

	std::vector<sf::Vector2f> m_entryPoints; //If more than 1 entry point, evenly distribute balls between them.



public:
	Level();

	/*Should create a new level that is 'frozen' waiting to be started, albeit allowing
	platforms to be placed. It should just set up the data the level uses.*/
	void newLevel(int iNumberOfBalls, int iNumberOfGoals, std::vector<sf::Vector2f> entryPoints);

	void start();
};