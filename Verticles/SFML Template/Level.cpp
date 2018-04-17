#include "Level.h"

/*! The default constructor. Initializes the physics object.*/
Level::Level()
{
	m_physics = new Physics(b2Vec2(0.0f, 1.5f), 7, 5); //Setup the Physics object, creating the b2World.

	//Temporary Testing Stuff
	m_testPlatform = new Platform(b2Vec2(2.0f, 3.0f), b2Vec2(6.0f, 0.5f), 14.0f, m_physics->getWorld());
}

/*! The deconstructor, deletes pointers to the balls, platforms and goals.*/
Level::~Level()
{
	for (int i = m_balls.size() - 1; i > 0; i--)
	{
		delete m_balls.at(i);
	}

	for (int i = m_platforms.size() - 1; i > 0; i--)
	{
		delete m_platforms.at(i);
	}

	for (int i = m_goals.size() - 1; i > 0; i--)
	{
		delete m_goals.at(i);
	}

	delete m_testPlatform;
}

/*! Creates a new level with the given parameters that is paused, but all of the objects are setup and positioned
*	according to the values passed in.*/
void Level::m_newLevel(int iNumberOfBalls, int iNumberOfBallsToWin, std::vector<b2Vec2> entryPoints, std::vector<b2Vec2> goals)
{
	m_iNumberOfBalls = iNumberOfBalls;
	m_iNumberOfBallsToWin = iNumberOfBallsToWin;

	m_entryPoints = entryPoints;

	int iEntryPointIndex = 1;
	for (int i = 0; i < iNumberOfBalls; i++)
	{
		/*Evenly distribute the balls between all of the available entry points by
		checking if we have looped through a section of the evenly split number
		of balls.*/
		if (i == (int)((iNumberOfBalls / m_entryPoints.size() * iEntryPointIndex)))
		{
			iEntryPointIndex++;
		}

		float rnd = rand() % 6000 - 4000;

		float xOffset = rnd / 10000.0f;

		rnd = rand() % 68000 - 66000;

		float yOffset = rnd / 10000.0f;

		std::cout <<"X Offset: "<< xOffset << std::endl;
		std::cout << "Y Offset: " << yOffset << std::endl;

		b2Vec2 pos = b2Vec2(m_entryPoints.at(iEntryPointIndex - 1).x + xOffset, m_entryPoints.at(iEntryPointIndex - 1).y + yOffset);

		//Create a new Ball object and push it to the collection of balls at the given position in m_entryPoints.
		m_balls.push_back(new Ball("./resources/Textures/ball.png", pos, 0.1f, m_physics->getWorld()));

		std::cout << "Creating Ball " << i << " at (" << pos.x << ", " << pos.y << ")." << std::endl;
	}

	for (int i = 0; i < goals.size(); i++)
	{
		m_goals.push_back(new Goal("./resources/Textures/redBlock.png", goals.at(i), 0.5f, m_physics->getWorld()));
	}
}

/*! Resumes the game by setting m_bIsPaused to false.*/
void Level::m_resume()
{
	m_bIsPaused = false;
}

/*! Pauses the game by setting m_bIsPaused to true.*/
void Level::m_pause()
{
	m_bIsPaused = true;
}

/*! The sf::Drawable virtual draw function. Draws all of the balls, platforms and goals this level uses.*/
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_balls.size(); i++)
	{
		target.draw(*m_balls.at(i));
	}

	for (int i = 0; i < m_platforms.size(); i++)
	{
		target.draw(*m_platforms.at(i));
	}

	for (int i = 0; i < m_goals.size(); i++)
	{
		target.draw(*m_goals.at(i));
	}

	target.draw(*m_testPlatform);

	for (int i = 0; i < m_entryPoints.size(); i++)
	{
		sf::RectangleShape rekt = sf::RectangleShape(sf::Vector2f(0.1f, 0.1f));
		rekt.setPosition(sf::Vector2f(m_entryPoints.at(i).x, m_entryPoints.at(i).y));
		target.draw(rekt);
	}
}

/*! The update function keeps the physics b2World* up to date, as well as any other moving objects such as balls.
*	It should be called every frame via the game loop and be given the elapsed time since its last call. The code inside
*	of the update function will only run if the game is not paused.
*/
void Level::m_update(float fElapsedTime)
{
	if (!m_bIsPaused)
	{
		m_physics->updateWorld(fElapsedTime);

		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls.at(i)->m_update();
		}

		if (m_balls.empty())
		{
			if (m_iGoalsScored >= m_iNumberOfBallsToWin)
			{
				levelOver(true);
			}
			else
			{
				levelOver(false);
			}
		}
		



		for (int i = m_balls.size() - 1; i >= 0; i--)
		{
			if (m_balls.at(i)->m_bHasHitGoal)
			{
				//Delete the ball that is safe to delete here.
				//Increment the number of goals scored here. (potentially works, only tested shortly).

				m_balls.at(i) = nullptr;
				delete m_balls.at(i);
				m_balls.erase(m_balls.begin() + i);
				m_iGoalsScored++;
			}
			else if (m_balls.at(i)->getPosition().y > 8.0f)
			{
				m_balls.at(i) = nullptr;
				delete m_balls.at(i);
				m_balls.erase(m_balls.begin() + i);
			}
		}

		std::cout << "Goals Scored: " << m_iGoalsScored << std::endl;
	}
}

void Level::levelOver(bool bLevelIsWon)
{
	m_pause();

	if (bLevelIsWon)
	{
		std::cout << "You win!" << std::endl;
	}
	else
	{
		std::cout << "You lose!" << std::endl;
	}
	
}
