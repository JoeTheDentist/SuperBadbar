#include "main_menu.h"

#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"

Main_menu::Main_menu()
{
	m_menu_background = new Surface(PIC_MAINMENU_R + "mainmenu.png");
	m_pos_background.x = 0;
	m_pos_background.y = 0;
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
	gGraphics->get_camera()->display_picture(m_menu_background, &m_pos_background, true);
	gGraphics->get_camera()->flip_camera();
}

void Main_menu::launch_game()
{
	Game *game = new Game();
	game->game_loop();
	delete game;	
}
