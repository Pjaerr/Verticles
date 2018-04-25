#pragma once

#include "Ball.h"
#include "Platform.h"
#include "Goal.h"
#include "Physics.h"

#include "DataManager.h"
#include "HUD.h"

#include <memory>
#include <map>


/*!\class Level
*	\brief The class responsible for creating a 'scene' within the game.
*
*	Creates a level or 'scene' within a game, contains functionality for placing platforms
*	as well as resuming or pausing the game as well as keeping track of the score.
*/
class Level : public sf::Drawable
{
private:

	DataManager m_dataManager; //!< Used to access textures and fonts.

	//Level Attributes
	bool m_bIsPaused = true; //!< False if no longer in the platform placement phase where balls can fall.
	bool m_bIsPlacingPlatform = false; //!< True if a platform is currently being placed.
	bool m_bLevelHasStarted = false; //!< True once m_resume() has been called once. (stops platform placement)

	int m_iNumberOfBalls; //!< The number of balls that exist within the level.
	int m_iNumberOfBallsToWin; //!< The number of balls that need to go into a goal to win the level.
	int m_iGoalsScored = 0; //!< The number of goals that have been scored.
	int m_iPlatformsPlaced = 0; //!< The number of user-placed platforms currently in the level.
	int m_iPlatformLimit = 2; //!< The maximum number of platforms that are allowed to be placed.

	float m_fBallDeviationAmt = 0.3f; //!< The range a ball can be placed within (-3.0f - 3.0f)

	//Objects
	std::vector<std::unique_ptr<Ball>> m_balls; //!< The balls that will fall when a level is started/resumed.
	std::vector<std::unique_ptr<Platform>> m_platforms; //!< The platforms that are either placed into the level by the user, or start in the level.
	std::vector<std::unique_ptr<Goal>> m_goals; //!< The goals that the balls must fall into in order to score points.
	std::vector<b2Vec2> m_entryPoints; //!< The entry points that the balls will fall from. Evenly distributed if more than 1 point.

	sf::RectangleShape m_tempPlatform; //!< The temporary platform that shows where the actual platform will be placed.

	/*! \brief Starts the relevant ending scenarios.
	*	\param bLevelIsWon True if won, false if loss.
	*/
	void m_levelOver(bool bLevelIsWon);

	void m_platformPlacement(); //!< Allows a temporary platform to be moved around and placed in the level.

	/*! \brief Creates a new level from the given filepath.
	*	\param filePath A string referencing a filepath from which to load the level.
	*/
	void m_newLevel(const char * filePath);

	std::map<std::string, std::string> m_textures;

	std::map<std::string, std::string> m_levels; //!< Holds level filepaths and corresponding names.

	std::string m_currentLevel; //!< Name of current level in the m_levels map.

public:
	Level(b2Vec2 worldSize); //!< The default constructor.
	~Level(); //!< The deconstructor, deletes pointers that have been allocated via the new keyword.

	void m_clearData(); //!< Clears and deletes all data structures being used.

	void m_resetLevel(); //!< Re-loads the current level.

	Physics * m_physics = nullptr; //!< The Physics object that keeps track of Box2D and updates the b2World* being used.

	HUD * m_hud = nullptr;

	/*! \brief Adds a level to the m_levels map.
	*	\param filePath The filepath to associate this level with.
	*	\param name The name that will point to the filePath.
	*/
	void m_addLevel(std::string filePath, std::string name);

	/*! \brief Starts a level with the given name if it within the m_levels map.
	*	\param name The name of the level to start.
	*/
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