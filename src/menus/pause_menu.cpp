#include "pause_menu.h"

#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"
#include "../game/levels_manager.h"
#include "../menus/menu_action.h"
#include "../menus/options_menu.h"
#include "../video/surface_text.h"

Pause_menu::Pause_menu() :
	Menu()
{
	m_menu_actions.add_action("Resume Game", 1);
	m_menu_actions.add_action("Options", 2);
	m_menu_actions.add_action("Leave Game", 3);
}

Pause_menu::~Pause_menu()
{
}

void Pause_menu::refresh_screen(bool flip)
{
	Menu::refresh_screen(flip);
}

void Pause_menu::treat_choice(int choice)
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


void Pause_menu::launch_options()
{
	set_son(new Options_menu(this));
}
