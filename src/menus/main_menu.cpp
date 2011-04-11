#include "main_menu.h"

#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"
#include "../game/levels_manager.h"
#include "../menus/menu_action.h"
#include "../menus/options_menu.h"
#include "../video/surface_text.h"

Main_menu::Main_menu() :
	Menu(),
	m_menu_background(new Surface(PIC_MAINMENU_R + "mainmenu.png")),
	m_pos_background()
{
	m_pos_background.x = 0;
	m_pos_background.y = 0;
	m_menu_actions.add_action("New game", 1);
	m_menu_actions.add_action("Options", 2);
	m_menu_actions.add_action("Leave", 3);
	loop();
}

Main_menu::~Main_menu()
{
//~ 	delete m_menu_background;
}

void Main_menu::refresh_screen()
{
	Camera *camera = gGraphics->get_camera();
	camera->display_picture(m_menu_background, &m_pos_background, true);
	Menu::refresh_screen();
}

bool Main_menu::treat_choice(int choice)
{
	switch(choice) {
		case 1:
			launch_game();
			return true;
		case 2:
			launch_options();
			return true;
		case 3:
			return false;
		default:
			return true;
		
	}
}

void Main_menu::launch_game()
{
	Levels_manager *levels_manager = new Levels_manager();
	levels_manager->play();
	delete levels_manager;	
}

void Main_menu::launch_options()
{
	Options_menu *om = new Options_menu();
	delete om;	
}
