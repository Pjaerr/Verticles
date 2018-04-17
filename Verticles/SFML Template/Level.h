#pragma once

#include "Ball.h"
#include "Platform.h"
#include "Goal.h"
#include "Physics.h"

class Level : public sf::Drawable
{
private:
	//Level Attributes
	bool m_bIsPaused = true; //!< False if no longer in the platform placement phase where balls can fall.
	int m_iNumberOfBalls; //!< The number of balls that exist within the level.
	int m_iNumberOfBallsToWin; //!< The number of balls that need to go into a goal to win the level.
	int m_iGoalsScored = 0;

	float m_fBallDeviationAmt = 0.3f;

	//Objects
	std::vector<Ball*> m_balls; //!< The balls that will fall when a level is started/resumed.
	std::vector<Platform *> m_platforms; //!< The platforms that are either placed into the level by the user, or start in the level.
	std::vector<Goal *> m_goals; //!< The goals that the balls must fall into in order to score points.
	std::vector<b2Vec2> m_entryPoints; //!< The entry points that the balls will fall from. Evenly distributed if more than 1 point.

	//Temporary Testing Stuff
	Platform * m_testPlatform = nullptr;

	void levelOver(bool bLevelIsWon);

public:
	Level(); //!< The default constructor.
	~Level(); //!< The deconstructor, deletes pointers that have been allocated via the new keyword.

	Physics * m_physics = nullptr; //!< The Physics object that keeps track of Box2D and updates the b2World* being used.

	/*! \brief Creates a new, frozen, level using the given parameters.
	*	\param iNumberOfBalls The number of balls that this level has.
	*	\param iNumberOfBallsToWin The minimum number of balls that must fall into a goal in order to win.
	*	\param entryPoints The position[s] from which the balls will fall when a level is started.
	*	\param goals The positions that the balls must come into contact with in order to score a point.
	*/
	void m_newLevel(int iNumberOfBalls, int iNumberOfBallsToWin, std::vector<b2Vec2> entryPoints, std::vector<b2Vec2> goals);

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
};