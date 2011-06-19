/**
 * 	@file list_menu_actions.cpp
 * 	@brief Implementation de la classe List_menu_actions
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */
 
#include "list_menu_actions.h"
#include "../menus/menu_action.h"
#include "../menus/menu_action_classic.h"
#include "../menus/menu_action_integer.h"
#include "../menus/menu_action_keyconfig.h"
#include "../video/camera.h"
#include "../video/surface.h"
#include "../video/surface_text.h"
#include "../util/globals.h"
#include "../sound/sound_engine.h"
#include <algorithm>

List_menu_actions::List_menu_actions():
	m_actions(),
	m_iterator(0)
{
	PRINT_CONSTR(2, "Construction d'une liste d'actions (List_menu_actions)")
}

List_menu_actions::~List_menu_actions()
{
	PRINT_CONSTR(2, "Destruction d'une liste d'actions (List_menu_actions)")
}

void List_menu_actions::update()
{
	for(std::list<Menu_action*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		(*it)->update();
	}
}

void List_menu_actions::add_action(Menu_action *action)
{
	m_actions.push_back(action);
	m_iterator = m_actions.begin();
	(*m_iterator)->select();	
}

void List_menu_actions::add_action_classic(std::string action, int num)
{
	add_action(new Menu_action_classic(action, num));
}

void List_menu_actions::add_action_integer(std::string action, int num, int val)
{
	add_action(new Menu_action_integer(action, num, val));
}

void List_menu_actions::add_action_keyconfig(std::string action, int num, std::string val, key k)
{
	add_action(new Menu_action_keyconfig(action, num, val, k));
}

void List_menu_actions::incr_curs(int dep)
{
	(*m_iterator)->deselect();
	dep = (dep + m_actions.size()) % m_actions.size(); // si le deplacement est negatif..
	for (int i = 0; i < dep; i++) {
		m_iterator++;
		if (m_iterator == m_actions.end()) 
			m_iterator = m_actions.begin();
	}
	(*m_iterator)->select();
	gSound->play_sound(MENU_SOUNDS_R + "move_selection.wav");
}

void List_menu_actions::incr_value(int value)
{
	(*m_iterator)->incr_value(value);
	gSound->play_sound(MENU_SOUNDS_R + "move_selection.wav");
}

void List_menu_actions::enter_pressed()
{
	(*m_iterator)->enter_pressed();
}

void List_menu_actions::display(Camera *camera, Rect pos) const
{
	Surface *surf;
	Rect temp;
	for(std::list<Menu_action*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		surf = (*it)->get_surface();
		temp = pos;
		temp.x += (pos.w - (*it)->width()) / 2;
		camera->display_picture(surf, &temp, true);
		pos.y += surf->h();
	}		
}

int List_menu_actions::get_selected_action()
{
	if (m_actions.empty()) {
		PRINT_DEBUG(1, "Actions list is empty, default value returned")
		return 0;
	}
	return (*m_iterator)->get_index();
}

int List_menu_actions::get_selected_action_value()
{
	if (m_actions.empty()) {
		PRINT_DEBUG(1, "Actions list is empty, default value returned")
		return 0;
	}
	return (*m_iterator)->get_value();
}

int List_menu_actions::width() const
{
	int res = 0;
	for(std::list<Menu_action*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res = std::max(res, (*it)->width());
	}
	return res;
}

int List_menu_actions::height() const
{
	int res = 0;
	for(std::list<Menu_action*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res += (*it)->height();
	}
	return res;
}


