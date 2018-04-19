#include "Level.h"

/*! The default constructor. Initializes the physics object.*/
Level::Level(b2Vec2 worldSize)
{
	m_physics = new Physics(b2Vec2(0.0f, 2.5f), 15, 15, worldSize); //Setup the Physics object, creating the b2World.

	//Temporary Testing Stuff
	m_testPlatform = new Platform(b2Vec2(2.0f, 3.0f), b2Vec2(6.0f, 0.5f), 14.0f, m_physics->m_getWorld());
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
	m_balls.clear();
	m_goals.clear();
	m_entryPoints.clear();
	m_platforms.clear();
	m_iGoalsScored = 0;

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
		m_balls.push_back(new Ball("./resources/Textures/ball.png", pos, 0.1f, m_physics->m_getWorld()));

		std::cout << "Creating Ball " << i << " at (" << pos.x << ", " << pos.y << ")." << std::endl;
	}

	for (int i = 0; i < goals.size(); i++)
	{
		m_goals.push_back(new Goal("./resources/Textures/redBlock.png", goals.at(i), 0.5f, m_physics->m_getWorld()));
	}
}

/*! Resumes the game by setting m_bIsPaused to false.*/
void Level::m_resume()
{
	m_bLevelHasStarted = true;
	m_bIsPaused = false;
}

/*! Pauses the game by setting m_bIsPaused to true.*/
void Level::m_pause()
{
	m_bIsPaused = true;
}

void Level::m_intiatePlatformPlacement()
{
	if (!m_bIsPlacingPlatform)
	{
		m_bIsPlacingPlatform = true;

		m_tempPlatform = sf::RectangleShape(sf::Vector2f(4.0f, 0.5f));
		
		m_tempPlatform.setOrigin(sf::Vector2f(m_tempPlatform.getGlobalBounds().width / 2, m_tempPlatform.getGlobalBounds().height / 2));

		m_tempPlatform.setPosition(sf::Vector2f(m_physics->m_getWorldSize().x / 2, m_physics->m_getWorldSize().y / 2));

		m_tempPlatform.setFillColor(sf::Color::Transparent);
		m_tempPlatform.setOutlineThickness(0.1f);
		m_tempPlatform.setOutlineColor(sf::Color::Blue);
	}
	else
	{
		//Change from console log to HUD text.
		std::cout << "Finish placing current platform first!" << std::endl;
	}
	
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

	if (!m_bLevelHasStarted && m_bIsPlacingPlatform)
	{
		target.draw(m_tempPlatform);
	}
}

void Level::m_platformPlacement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_tempPlatform.move(sf::Vector2f(0.03f, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_tempPlatform.move(sf::Vector2f(-0.03f, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_tempPlatform.move(sf::Vector2f(0, -0.03f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_tempPlatform.move(sf::Vector2f(0, 0.03f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_tempPlatform.rotate(1.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_tempPlatform.rotate(-1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		if (m_tempPlatform.getScale().x < m_physics->m_getWorldSize().x * 0.2f)
		{
			m_tempPlatform.setScale(sf::Vector2f(m_tempPlatform.getScale().x + 0.1f, m_tempPlatform.getScale().y));
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
	{
		if (m_tempPlatform.getScale().x > 0.3f)
		{
			m_tempPlatform.setScale(sf::Vector2f(m_tempPlatform.getScale().x - 0.1f, m_tempPlatform.getScale().y));
		}

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_bIsPlacingPlatform = false;

		m_platforms.push_back(new Platform(b2Vec2(m_tempPlatform.getPosition().x, m_tempPlatform.getPosition().y),
			b2Vec2(m_tempPlatform.getSize().x * m_tempPlatform.getScale().x, m_tempPlatform.getSize().y),
			m_tempPlatform.getRotation(), m_physics->m_getWorld()));
	}
}

/*! The update function keeps the physics b2World* up to date, as well as any other moving objects such as balls.
*	It should be called every frame via the game loop and be given the elapsed time since its last call. The code inside
*	of the update function will only run if the game is not paused.
*/
void Level::m_update(float fElapsedTime)
{
	if (!m_bLevelHasStarted && m_bIsPlacingPlatform) //If the game hasn't started yet.
	{
		m_platformPlacement();
	}

	//Undo the last platform that was placed.
	if (!m_bLevelHasStarted)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //Will be a button
		{
			if (!m_platforms.empty())
			{
				m_platforms.pop_back();
			}
		}
	}

	if (!m_bIsPaused)
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //Restart level.
		{
			m_pause();

			std::vector<b2Vec2> goalLocations;

			for (int i = 0; i < m_goals.size(); i++)
			{
				goalLocations.push_back(m_goals.at(i)->m_getPosition());
			}

			m_newLevel(m_iNumberOfBalls, m_iNumberOfBallsToWin, m_entryPoints, goalLocations);
		}

		m_physics->m_updateWorld(fElapsedTime);

		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls.at(i)->m_update();
		}

		if (m_balls.empty())
		{
			if (m_iGoalsScored >= m_iNumberOfBallsToWin)
			{
				m_levelOver(true);
			}
			else
			{
				m_levelOver(false);
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
			else if (m_balls.at(i)->m_getPosition().y > 8.0f)
			{
				m_balls.at(i) = nullptr;
				delete m_balls.at(i);
				m_balls.erase(m_balls.begin() + i);
			}
		}

		std::cout << "Goals Scored: " << m_iGoalsScored << std::endl;
	}
}

void Level::m_levelOver(bool bLevelIsWon)
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
