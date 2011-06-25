#include "menu.h"


#include "../video/Camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/Keyboard.h"
#include "../game/game.h"
#include "../game/LevelsManager.h"
#include "../menus/MenuAction.h"
#include "../video/SurfaceUniform.h"
#include "../video/SurfaceFrame.h"


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
	gKeyboard->enable_key_repeat();
}

Menu::~Menu()
{
	gKeyboard->disable_all_keys();
	gKeyboard->disable_key_repeat();
}

void Menu::update()
{
	if (m_son) {
		if (m_son->end_menu()) {
			delete m_son;
			m_son = NULL;
			return;
		}
		m_son->update();
	} else {
		m_menu_actions.update();
		while (gKeyboard->is_next_menu_key()) {
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
				m_menu_actions.enter_pressed();
				break;
			default:
				break;
			}
		}
	}
}

void Menu::update_graphics() const
{
	// on n'affiche que le menu fils s'il y en a un
	if (!m_son) {
		Camera *camera = gGraphics->get_camera();
		int w = 2 * MENU_OFFSET_W + m_menu_actions.width();
		int h = 2 * MENU_OFFSET_H + m_menu_actions.height();
		SurfaceUniform grey(camera->width(), camera->height(),
				MENU_GREY_LEVEL, MENU_GREY_LEVEL, MENU_GREY_LEVEL);
		grey.set_alpha(MENU_GREY_ALPHA);
		Rect posNull;
		if (can_display_grey_background())
			camera->display_picture(&grey, &posNull, true);
		SurfaceUniform background(w, h, MENU_BACKGROUND_R, MENU_BACKGROUND_G, MENU_BACKGROUND_B);
		background.set_alpha(MENU_BACKGROUND_ALPHA);
		Rect pos;
		pos.w = w;
		pos.h = h;
		pos.x = (camera->width() - pos.w) / 2;
		pos.y = (camera->height() - pos.h) / 2;
		camera->display_picture(&background, &pos, true);
		SurfaceFrame frame(pos,  MENU_FRAME_R, MENU_FRAME_G, MENU_FRAME_B);
		camera->display_picture(&frame, &pos, true);
		pos.y += MENU_OFFSET_H;
		m_menu_actions.display(camera, pos);
	} else {
		m_son->update_graphics();
	}
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
