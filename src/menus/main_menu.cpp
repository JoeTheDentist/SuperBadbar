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
	m_menu_actions.add_action_classic("New game", 1);
	m_menu_actions.add_action_classic("Options", 2);
	m_menu_actions.add_action_classic("Leave", 3);
	gSound->load_music("main_menu.mp3");
	gSound->play_music();
	loop();
}

Main_menu::~Main_menu()
{
//~ 	delete m_menu_background;
}

void Main_menu::update_graphics()
{
	Camera *camera = gGraphics->get_camera();
	camera->display_picture(m_menu_background, &m_pos_background, true);
	Menu::update_graphics();	
	gGraphics->flip_camera();
}

void Main_menu::loop()
{
	while(!end_menu() &	 !end_game()) {
		std::cout << "plop" << std::endl;
		gKeyboard->update_events();
		update();
		update_graphics();
	}
}

void Main_menu::treat_choice(int choice)
{
	switch(choice) {
		case 1: // nouvelle partie
			launch_game();
			gSound->load_music("main_menu.mp3");
			gSound->play_music();
			break;
		case 2: // options
			launch_options();
			break;
		case 3: // quitter le jeu
			set_leave_game_true();
			break;
		default:
			break;
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
	set_son(new Options_menu(this));
}

