#include "menu.h"


#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/game.h"
#include "../game/levels_manager.h"
#include "../menus/menu_action.h"
#include "../video/surface_text.h"
#include "../video/surface_uniform.h"


Menu::Menu() :
	m_menu_actions(),
	m_pos_menu()
{
	m_pos_menu.x = 200;
	m_pos_menu.y = 300;
}

Menu::~Menu()
{
}

void Menu::loop()
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
		case mk_down:
			m_menu_actions.incr_curs(1);
			break;
		case mk_up:
			m_menu_actions.incr_curs(-1);
			break;
		case mk_enter:
			go_on = treat_choice(m_menu_actions.get_selected_action());
			break;
		default:
			break;		
		}
	}
	delete keyboard;
}

void Menu::refresh_screen()
{
	Camera *camera = gGraphics->get_camera();
	Surface_uniform *frame = new Surface_uniform(m_menu_actions.width(), m_menu_actions.height(), 255, 0, 255);
	camera->display_picture(frame, &m_pos_menu, true);
	m_menu_actions.display(camera, m_pos_menu);
	camera->flip_camera();
}


