#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Panel.h"

/*! /class UI
*	\brief The class that holds all of the 'Verticles' UI.
*
*	A storage class, if anything, that holds all of the UI that
*	is specific to the game, this is a non-modular class as the
*	components that make up the UI are meant to be modular instead.
*/
class UI : public sf::Drawable
{
private:
	Text m_titleText; //!< Text for the main menu title.
	Text m_controlsText; //!< Text showing the game's controls.
	Text m_ballsText; //!< Text showing number of goals scored.
	Text m_platformsText; //!< Text showing number of platforms left.
	

	Panel m_menuPanel; //!< The panel that sits behind the main menu.
	Panel m_controlsPanel; //!< the panel that sits behind the controls text.
	Panel m_textPanel; //!< The panel that sits behind the balls/platforms information.
	Panel m_endScreenPanel; //!< The panel that sits behind the loss/win screen at the end of each level.
	
	sf::Vector2f m_mousePos; //!< The position of the mouse.

	sf::Font * m_font; //!< The font that the UI should use, given during construction.

public:
	/*! \brief The constructor sets up all of the UI.
	*	\param font The font the UI should use.
	*/
	UI(sf::Font * font);

	/*! \brief Updates the balls/platform information.
	*	\param ballsText The new text showing number of goals scored.
	*	\param platformsText The new text showing number of platforms left.
	*/
	void m_updateText(std::string ballsText, std::string platformsText);

	/*! \brief The virtual draw function taken from sf::Drawable.*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*! \brief Updates the mouse position relative to the window.
	*	\param relativeTo The window that this position is relative to.
	*/
	void m_updateMousePosition(sf::RenderWindow * relativeTo);

	/*! \brief Called when the mouse is clicked.*/
	void m_mouseClicked();

	bool m_showControls = false; //!< Whether the controls should be drawn.
	bool m_showMainMenu = true; //!< Whether the main menu should be drawn.

	bool m_showEndScreenWin = false; //!< Whether the end screen win should be drawn.
	bool m_showEndScreenLoss = false; //!< Whether the end screen loss should be drawn.

	//Buttons
	Button m_platformPlacementButton; //!< The button that starts platform placement.
	Button m_menuPlayButton; //!< The button that starts the game.
	Button m_pauseButton; //!< The button that pauses/resumes the game.
	Button m_resetLevelButton; //!< The button that resets a level.

	Button m_endScreenLossButton; //!< The button that retries the current level when you lose.
	Button m_endScreenWinButton; //!< The button that moves onto the next level when you win.

	Text m_endScreenText; //!< The You Lose/You Win text shown at the end of a level.

};