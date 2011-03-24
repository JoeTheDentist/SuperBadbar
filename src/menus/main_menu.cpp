#include "main_menu.h"

#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"
#include "../game/levels_manager.h"
#include "../menus/menu_action.h"
#include "../video/surface_text.h"

Main_menu::Main_menu() :
	m_menu_background(new Surface(PIC_MAINMENU_R + "mainmenu.png")),
	m_pos_background(),
	m_menu_action(new Menu_action("plop", 1)),
	m_pos_menu()
{
	m_pos_background.x = 0;
	m_pos_background.y = 0;
	m_pos_menu.x = 200;
	m_pos_menu.y = 300;
	loop();
}

Main_menu::~Main_menu()
{
	delete m_menu_background;
}

void Main_menu::loop()
{
	bool go_on = true;
	Keyboard *keyboard = new Keyboard();
	while (go_on) {
		this->refresh_screen();
		menu_key key = keyboard->get_menu_key();
		switch (key) {
		case mk_exit:
			go_on = false;
			break;
		case mk_enter:
			launch_game();
			break;
		default:
			break;		
		}
	}
	delete keyboard;
}

void Main_menu::refresh_screen()
{
	Camera *camera = gGraphics->get_camera();
	camera->display_picture(m_menu_background, &m_pos_background, true);
	camera->display_picture(m_menu_action->get_surface(false), &m_pos_menu, true);
	camera->flip_camera();
}

void Main_menu::launch_game()
{
	Levels_manager *levels_manager = new Levels_manager();
	levels_manager->play();
	delete levels_manager;	
}
