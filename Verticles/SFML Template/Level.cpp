#include "Level.h"

/*! The default constructor. Initializes the physics object.*/
Level::Level()
{
	m_physics = new Physics(b2Vec2(0.0f, 10.0f), 7, 5); //Setup the Physics object, creating the b2World.

	//Temporary Testing Stuff
	m_testBall = new Ball("./resources/Textures/ball.png", b2Vec2(0.0f, -3.0f), 0.1f, m_physics->getWorld());
	m_testPlatform = new Platform(b2Vec2(0.0f, 0.0f), b2Vec2(4.0f, 0.5f), 4.0f, m_physics->getWorld());
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

	delete m_testBall;
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

		//Create a new Ball object and push it to the collection of balls at the given position in m_entryPoints.
		m_balls.push_back(new Ball("./resources/Textures/ball.png", m_entryPoints.at(iEntryPointIndex - 1), 0.1f, m_physics->getWorld()));

		std::cout << "Creating Ball " << i << " at (" << m_entryPoints.at(iEntryPointIndex - 1).x << ", " << m_entryPoints.at(iEntryPointIndex - 1).y << ")." << std::endl;
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

	target.draw(*m_testBall);
	target.draw(*m_testPlatform);
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

		m_testBall->m_update();
	}
}
