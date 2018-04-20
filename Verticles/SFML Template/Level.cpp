#include "Level.h"

/*! The default constructor. Initializes the physics object.*/
Level::Level(b2Vec2 worldSize)
{
	m_physics = new Physics(b2Vec2(0.0f, 2.5f), 15, 15, worldSize); //Setup the Physics object, creating the b2World.

	m_createTexture("./resources/Textures/redBlock.png", "goal");
	m_createTexture("./resources/Textures/ball.png", "ball");
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
}

void Level::m_clearData()
{
	for (int i = m_balls.size() - 1; i >= 0; i--)
	{
		m_balls.at(i)->m_destroySelf();
		m_balls.at(i) = nullptr;
		delete m_balls.at(i);
	}

	m_balls.clear();

	for (int i = m_goals.size() - 1; i >= 0; i--)
	{
		m_goals.at(i)->m_destroySelf();
		m_goals.at(i) = nullptr;
		delete m_goals.at(i);
	}

	m_goals.clear();

	for (int i = m_platforms.size() - 1; i >= 0; i--)
	{
		m_platforms.at(i)->m_destroySelf();
		m_platforms.at(i) = nullptr;
		delete m_platforms.at(i);
	}

	m_platforms.clear();
	m_entryPoints.clear();

	m_iGoalsScored = 0;
	m_iPlatformsPlaced = 0;
	m_bIsPlacingPlatform = false;
	m_bLevelHasStarted = false;
	
}

void Level::m_resetLevel()
{
	m_clearData();

	m_newLevel(m_levels.at(m_currentLevel).c_str());
}

void Level::m_addLevel(std::string filePath, std::string name)
{
	m_levels.insert(std::pair<std::string, std::string>(name, filePath));
}

void Level::m_startLevel(std::string name) 
{
	if (m_levels.find(name) != m_levels.end())
	{
		m_currentLevel = name;
		m_newLevel(m_levels.at(name).c_str());
	}
	else 
	{
		std::cout << "A level doesn't exist with the name " << name << std::endl;
	}
}

/*! Creates a new level from the given filepath by looping through each line and grabbing the relevant data.

	File Structure
	--------------
	balls 50 // The number of balls in the level.
	score 20 // The number of balls needed to go into a goal to win.

	g 2/4 0.5 //Creates a goal at a given position 2/4 (x/y) and with a radius 0.5

	p 2/3 6/0.5 14 // Creates a platform at a given 2/3 (x/y) with a given 6/0.5 (width/height) rotated at angle 14 (degrees)

*/
void Level::m_newLevel(const char * filePath)
{
	m_clearData();

	//Default Entry Points on all levels.
	m_entryPoints.push_back(b2Vec2(2.0f, 0.0f));
	m_entryPoints.push_back(b2Vec2(6.0f, 0.0f));

	FILE * file;
	fopen_s(&file, filePath, "r"); //Open the file at filePath in read mode.

	if (file == NULL)
	{
		throw std::invalid_argument("Level file doesn't exist.");
	}

	/*Read each line of the file until end of file is reached.*/
	while (1)
	{
		char line[128]; //Assumes first word of a line isn't longer than 128 characters.

		int res = fscanf_s(file, "%s", line, 128); //Read the first word of the line.

		if (res == EOF) //If we've reached the end of the file, exit the loop.
		{
			break;
		}

		if (strcmp(line, "balls") == 0) //A file reference has been found.
		{
			int balls;

			fscanf_s(file, "%d\n", &balls);

			m_iNumberOfBalls = balls;
		}
		else if (strcmp(line, "score") == 0) //A file reference has been found.
		{
			int score;

			fscanf_s(file, "%d\n", &score);

			m_iNumberOfBallsToWin = score;
		}
		else if (strcmp(line, "limit") == 0) //A file reference has been found.
		{
			int limit;

			fscanf_s(file, "%d\n", &limit);

			m_iPlatformLimit = limit;
		}
		else if (strcmp(line, "g") == 0)
		{
			b2Vec2 pos;
			float radius;

			int n = fscanf_s(file, "%f/%f %f\n", &pos.x, &pos.y, &radius);

			m_goals.push_back(new Goal(m_textures.at("goal"), pos, radius, m_physics->m_getWorld()));
		}
		else if (strcmp(line, "p") == 0)
		{
			b2Vec2 pos;
			b2Vec2 size;
			float rotation;

			int n = fscanf_s(file, "%f/%f %f/%f %f\n", &pos.x, &pos.y, &size.x, &size.y, &rotation);

			m_platforms.push_back(new Platform(pos, size, rotation, m_physics->m_getWorld()));
		}
	}

	int iEntryPointIndex = 1;
	for (int i = 0; i < m_iNumberOfBalls; i++)
	{
		/*Evenly distribute the balls between all of the available entry points by
		checking if we have looped through a section of the evenly split number
		of balls.*/

		std::cout << "i: "<< i << std::endl;
		std::cout << "Not i: " << (int)((m_iNumberOfBalls / m_entryPoints.size() * iEntryPointIndex)) << std::endl;

		if (i == (int)((m_iNumberOfBalls / m_entryPoints.size() * iEntryPointIndex)))
		{
			iEntryPointIndex = 2;
		}

		float rnd = rand() % 6000 - 4000;

		float xOffset = rnd / 10000.0f;

		rnd = rand() % 68000 - 66000;

		float yOffset = rnd / 10000.0f;

		b2Vec2 pos = b2Vec2(m_entryPoints.at(iEntryPointIndex - 1).x + xOffset, m_entryPoints.at(iEntryPointIndex - 1).y + yOffset);

		//Create a new Ball object and push it to the collection of balls at the given position in m_entryPoints.
		m_balls.push_back(new Ball(m_textures.at("ball"), pos, 0.1f, m_physics->m_getWorld()));
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
	if (!m_bIsPlacingPlatform && m_iPlatformsPlaced < m_iPlatformLimit)
	{
		m_bIsPlacingPlatform = true;

		m_tempPlatform = sf::RectangleShape(sf::Vector2f(4.0f, 0.5f));
		
		m_tempPlatform.setOrigin(sf::Vector2f(m_tempPlatform.getGlobalBounds().width / 2, m_tempPlatform.getGlobalBounds().height / 2));

		m_tempPlatform.setPosition(sf::Vector2f(m_physics->m_getWorldSize().x / 2, m_physics->m_getWorldSize().y / 2));

		m_tempPlatform.setFillColor(sf::Color::Transparent);
		m_tempPlatform.setOutlineThickness(0.1f);
		m_tempPlatform.setOutlineColor(sf::Color::Blue);

		m_iPlatformsPlaced++;
	}
	else
	{
		//Change from console log to HUD text.
		std::cout << "Cannot place a platform!" << std::endl;
	}
	
}

void Level::m_createTexture(std::string filePath, std::string name)
{
	m_textures.insert(std::pair<std::string, std::string>(name, filePath));
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //Restart level.
	{
		m_pause();

		m_resetLevel();
	}

	if (!m_bIsPaused)
	{
		m_physics->m_updateWorld(fElapsedTime);

		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls.at(i)->m_update();
		}

		if (m_iGoalsScored >= m_iNumberOfBallsToWin)
		{
			m_levelOver(true);
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
				m_balls.at(i)->m_destroySelf();
				m_balls.at(i) = nullptr;
				delete m_balls.at(i);
				m_balls.erase(m_balls.begin() + i);
				m_iGoalsScored++;
			}
			else if (m_balls.at(i)->m_getPosition().y > 8.0f)
			{
				m_balls.at(i)->m_destroySelf();
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

		auto current = m_levels.find(m_currentLevel);
		auto next = std::next(current, 1);

		if (next != m_levels.end())
		{
			m_startLevel(next->first);
		}
	}
	else
	{
		std::cout << "You lose!" << std::endl;
		m_resetLevel();
	}
}
