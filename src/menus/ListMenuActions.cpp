/**
 * 	@file ListMenuActions.cpp
 * 	@brief Implementation de la classe ListMenuActions
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "ListMenuActions.h"
#include "../menus/MenuAction.h"
#include "../menus/MenuActionClassic.h"
#include "../menus/MenuActionInteger.h"
#include "../menus/MenuActionString.h"
#include "../menus/MenuActionKeyconfig.h"
#include "../menus/MenuActionSelectMap.h"
#include "../video/Camera.h"
#include "../video/Surface.h"
#include "../video/SurfaceText.h"
#include "../util/globals.h"
#include "../sound/SoundEngine.h"
#include <algorithm>

ListMenuActions::ListMenuActions():
	m_actions(),
	m_iterator(0)
{
	PRINT_CONSTR(2, "Construction d'une liste d'actions (ListMenuActions)")
}

ListMenuActions::~ListMenuActions()
{
	for (std::list<MenuAction *>::iterator it = m_actions.begin(); it != m_actions.end(); ++it) {
		delete (*it);
	}
	PRINT_CONSTR(2, "Destruction d'une liste d'actions (ListMenuActions)")
}

void ListMenuActions::update()
{
	for(std::list<MenuAction*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		(*it)->update();
	}
}

void ListMenuActions::add_action(MenuAction *action)
{
	m_actions.push_back(action);
	m_iterator = m_actions.begin();
	(*m_iterator)->select();
}

void ListMenuActions::add_action_classic(std::string action, int num)
{
	add_action(new MenuActionClassic(action, num));
}

void ListMenuActions::add_action_integer(std::string action, int num, int val)
{
	add_action(new MenuActionInteger(action, num, val));
}

void ListMenuActions::add_action_keyconfig(std::string action, int num, std::string val, key k)
{
	add_action(new MenuActionKeyconfig(action, num, val, k));
}

void ListMenuActions::add_action_string(std::string action_name, int action_num, std::string value)
{
	add_action(new MenuActionString(action_name, action_num, value));
}

void ListMenuActions::add_action_selectmap(int action_num)
{
	add_action(new MenuActionSelectMap(action_num));
}

void ListMenuActions::incr_curs(int dep)
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

void ListMenuActions::display(Camera *camera, Rect pos) const
{
	Surface *surf;
	Rect temp;
	for(std::list<MenuAction*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		surf = (*it)->get_surface();
		temp = pos;
		temp.x += (pos.w - (*it)->width()) / 2;
		camera->display_picture(surf, &temp, true);
		pos.y += surf->h();
	}
}

int ListMenuActions::get_selected_action()
{
	if (m_actions.empty()) {
		PRINT_DEBUG(1, "Actions list is empty, default value returned")
		return 0;
	}
	return (*m_iterator)->get_index();
}

int ListMenuActions::getSelectedActionValInteger()
{
	if (m_actions.empty()) {
		PRINT_DEBUG(1, "Actions list is empty, default value returned")
		return 0;
	}
	return (*m_iterator)->getValueInteger();
}

int ListMenuActions::width() const
{
	int res = 0;
	for(std::list<MenuAction*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res = std::max(res, (*it)->width());
	}
	return res;
}

int ListMenuActions::height() const
{
	int res = 0;
	for(std::list<MenuAction*>::const_iterator it = m_actions.begin(); it != m_actions.end(); it++) {
		res += (*it)->height();
	}
	return res;
}

void ListMenuActions::treatEvent(EventKeyboard *eventKeyboard)
{
	(*m_iterator)->treatEvent(eventKeyboard);
}

