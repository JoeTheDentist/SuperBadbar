#include "options_menu.h"

#include "../video/camera.h"
#include "../sound/sound_engine.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"
#include "../game/levels_manager.h"
#include "../menus/menu_action.h"
#include "../video/surface_text.h"

Options_menu::Options_menu(Menu *parent) :
	Menu(parent)
{
	m_menu_actions.add_action("Sounds", 1, gSound->get_sounds_volume());
	m_menu_actions.add_action("Music", 2, gSound->get_music_volume());
	m_menu_actions.add_action("Keyboard", 3);
	m_menu_actions.add_action("Return", 4);
	loop();
}

Options_menu::~Options_menu()
{
}

void Options_menu::aux_loop()
{
	switch(m_menu_actions.get_selected_action()) {
	case 1:
		gSound->set_sounds_volume(m_menu_actions.get_selected_action_value());
		break;
	case 2:
		gSound->set_music_volume(m_menu_actions.get_selected_action_value());
		break;
	default:
		break;
		
	
	}
}

bool Options_menu::treat_choice(int choice)
{
	switch(choice) {
		case 1:
			return true;
		case 2:
			return true;
		case 3:
			return true;
		case 4:
			return false;
		default:
			return true;
		
	}
}

