#include "PauseMenu.h"

#include "video/Camera.h"
#include "util/repertories.h"
#include "util/globals.h"
#include "control/Keyboard.h"
#include "game/Game.h"
#include "game/LevelsManager.h"
#include "menus/MenuAction.h"
#include "menus/OptionsMenu.h"
#include "video/SurfaceText.h"

PauseMenu::PauseMenu() :
	Menu()
{
	m_menu_actions.add_action_classic("Resume Game", 1);
	m_menu_actions.add_action_classic("Options", 2);
	m_menu_actions.add_action_classic("Leave Game", 3);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::treat_choice(int choice)
{
	switch(choice) {
		case 1: // resume game
			set_leave_menu_true();
			break;
		case 2: // options
			launch_options();
			break;
		case 3: // leave game
			set_leave_game_true();
			break;
		default:
			break;

	}
}


void PauseMenu::launch_options()
{
	set_son(new OptionsMenu(this));
}
