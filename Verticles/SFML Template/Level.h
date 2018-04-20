#pragma once

#include "Ball.h"
#include "Platform.h"
#include "Goal.h"
#include "Physics.h"

#include <map> //For texture management.


/*!\class Level
*	\brief The class responsible for creating a 'scene' within the game.
*
*	Creates a level or 'scene' within a game, contains functionality for placing platforms
*	as well as resuming or pausing the game as well as keeping track of the score.
*/
class Level : public sf::Drawable
{
private:
	//Level Attributes
	bool m_bIsPaused = true; //!< False if no longer in the platform placement phase where balls can fall.
	bool m_bIsPlacingPlatform = false; //!< True if a platform is currently being placed.
	bool m_bLevelHasStarted = false; //!< True once m_resume() has been called once. (stops platform placement)

	int m_iNumberOfBalls; //!< The number of balls that exist within the level.
	int m_iNumberOfBallsToWin; //!< The number of balls that need to go into a goal to win the level.
	int m_iGoalsScored = 0;
	int m_iPlatformsPlaced = 0;
	int m_iPlatformLimit = 2;

	float m_fBallDeviationAmt = 0.3f;

	//Objects
	std::vector<Ball*> m_balls; //!< The balls that will fall when a level is started/resumed.
	std::vector<Platform *> m_platforms; //!< The platforms that are either placed into the level by the user, or start in the level.
	std::vector<Goal *> m_goals; //!< The goals that the balls must fall into in order to score points.
	std::vector<b2Vec2> m_entryPoints; //!< The entry points that the balls will fall from. Evenly distributed if more than 1 point.

	sf::RectangleShape m_tempPlatform; //!< The temporary platform that shows where the actual platform will be placed.

	void m_levelOver(bool bLevelIsWon);
	void m_platformPlacement();

	/*! \brief Creates a new level from the given filepath.
	*	\param filePath A string referencing a filepath from which to load the level.
	*/
	void m_newLevel(const char * filePath);

	std::map<std::string, std::string> m_textures;

	std::map<std::string, std::string> m_levels;
	std::string m_currentLevel;

public:
	Level(b2Vec2 worldSize); //!< The default constructor.
	~Level(); //!< The deconstructor, deletes pointers that have been allocated via the new keyword.

	void m_clearData();

	void m_resetLevel();

	void m_createTexture(std::string filePath, std::string name);

	Physics * m_physics = nullptr; //!< The Physics object that keeps track of Box2D and updates the b2World* being used.


	void m_addLevel(std::string filePath, std::string name);
	void m_startLevel(std::string name);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*! \brief The function responsible for keeping physical and non-physical objects up to date. Should be called every frame.
	*	\param fElapsedTime The time that has elapsed since the previous call.
	*/
	void m_update(float fElapsedTime);

	/*! \brief Sets m_bIsPaused to false.*/
	void m_resume();

	/*! \brief Sets m_bIsPaused to true.*/
	void m_pause();

	/*! \brief Starts the platform placement.*/
	void m_intiatePlatformPlacement();
};