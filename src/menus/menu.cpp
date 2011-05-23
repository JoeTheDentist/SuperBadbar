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


Menu::Menu(Menu *parent) :
	m_menu_actions(),
	m_pos_menu(),
	m_parent(parent),
	m_son(NULL),
	m_leave_game(false),
	m_leave_menu(false)
	
{
	m_pos_menu.x = 200;
	m_pos_menu.y = 300;
	gKeyboard->disable_all_keys();
	gKeyboard->reset_menu_keys();

}

Menu::~Menu()
{
	gKeyboard->disable_all_keys();
}

void Menu::loop()
{
	bool go_on = true;
	Keyboard *keyboard = gKeyboard;
	keyboard->enable_key_repeat();
	while (go_on) {
		aux_loop();
		this->refresh_screen();
		menu_key key = keyboard->wait_menu_key();
		switch (key) {
		case mk_exit: case mk_escape:
			go_on = false;
			break;
		case mk_down:
			m_menu_actions.incr_curs(1);
			break;
		case mk_up:
			m_menu_actions.incr_curs(-1);
			break;
		case mk_left:
			m_menu_actions.incr_value(-1);
			break;
		case mk_right:
			m_menu_actions.incr_value(1);
			break;
		case mk_enter:
			treat_choice(m_menu_actions.get_selected_action());
			break;
		default:
			break;		
		}
	}
	keyboard->disable_key_repeat();
}

void Menu::update()
{
	if (m_son) {
		if (m_son->end_menu()) {
			delete m_son;
			m_son = NULL;
			std::cout <<"yeapea" << std::endl;
			return;
		}
		m_son->update();
	} else {
		while (gKeyboard->is_next_menu_key()) {
			std::cout << "key pressed" << std::endl;
			menu_key key = gKeyboard->pop_menu_key();
			switch (key) {
			case mk_exit: 
				m_leave_menu = true;
				m_leave_game = true;
			case mk_escape:
				m_leave_menu = true;
				break;
			case mk_down:
				m_menu_actions.incr_curs(1);
				break;
			case mk_up:
				m_menu_actions.incr_curs(-1);
				break;
			case mk_left:
				m_menu_actions.incr_value(-1);
				break;
			case mk_right:
				m_menu_actions.incr_value(1);
				break;
			case mk_enter:
				treat_choice(m_menu_actions.get_selected_action());
				break;
			default:
				break;		
			}
		}
	}
}

void Menu::update_graphics() const
{
	// mon rafraichissement
	Camera *camera = gGraphics->get_camera();
	Surface_uniform *frame = new Surface_uniform(m_menu_actions.width(), m_menu_actions.height(), 255, 0, 255);
	Rect pos = m_pos_menu; // variable intermediaire pour assurer le const
	camera->display_picture(frame, &pos, true);
	m_menu_actions.display(camera, m_pos_menu);
	// le rafraichissement de mon fils
	if (m_son)
		m_son->update_graphics();
}

void Menu::refresh_screen(bool flip) 
{
	if (m_parent)
		m_parent->refresh_screen(false);
	Camera *camera = gGraphics->get_camera();
	Surface_uniform *frame = new Surface_uniform(m_menu_actions.width(), m_menu_actions.height(), 255, 0, 255);
	camera->display_picture(frame, &m_pos_menu, true);
	m_menu_actions.display(camera, m_pos_menu);
	if (flip)
		camera->flip_camera();
}

void Menu::set_leave_menu_true()
{
	m_leave_menu = true;
}

void Menu::set_leave_game_true()
{
	m_leave_game = true;
	m_leave_menu = true;
	if (m_parent) {
		m_parent->set_leave_game_true();
	}
}

void Menu::set_son(Menu *menu)
{
	m_son = menu;
}
