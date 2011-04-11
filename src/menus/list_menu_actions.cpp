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

void List_menu_actions::add_action(std::string action, int action_num, int action_value)
{
	m_actions.push_back(new Menu_action(action, action_num, action_value));
	m_iterator = m_actions.begin();
}

void List_menu_actions::incr_curs(int dep)
{
	dep = (dep + m_actions.size()) % m_actions.size(); // si le deplacement est negatif..
	for (int i = 0; i < dep; i++) {
		m_iterator++;
		if (m_iterator == m_actions.end()) 
			m_iterator = m_actions.begin();
	}
	gSound->play_sound(MENU_SOUNDS_R + "move_selection.wav");
}

void List_menu_actions::incr_value(int value)
{
	(*m_iterator)->incr_value(value);
	gSound->play_sound(MENU_SOUNDS_R + "move_selection.wav");
}



void List_menu_actions::display(Camera *camera, Rect pos)
{
	Surface *surf;
	for(std::list<Menu_action*>::iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		surf = (*it)->get_surface(it == m_iterator);
		camera->display_picture(surf, &pos, true);
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

int List_menu_actions::width()
{
	int res = 0;
	for(std::list<Menu_action*>::iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res = std::max(res, (*it)->get_surface()->w());
	}
	return res;
}

int List_menu_actions::height()
{
	int res = 0;
	for(std::list<Menu_action*>::iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res += (*it)->get_surface()->h();
	}
	return res;
}


