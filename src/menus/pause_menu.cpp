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

Pause_menu::Pause_menu(bool &leave) :
	Menu(),
	m_leave(leave)
{
	m_menu_actions.add_action("Resume Game", 1);
	m_menu_actions.add_action("Options", 2);
	m_menu_actions.add_action("Leave Game", 3);
	loop();
}

Pause_menu::~Pause_menu()
{
}

void Pause_menu::refresh_screen(bool flip)
{
	Menu::refresh_screen(flip);
}

bool Pause_menu::treat_choice(int choice)
{
	switch(choice) {
		case 1:
			return false;
		case 2:
			launch_options();
			return true;
		case 3:
			m_leave = true;
			return false;
		default:
			return true;
		
	}
}


void Pause_menu::launch_options()
{
	Options_menu *om = new Options_menu(this);
	delete om;	
}
