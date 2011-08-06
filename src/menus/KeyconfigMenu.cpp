#include "KeyconfigMenu.h"

#include "util/repertories.h"
#include "util/globals.h"
#include "control/Keyboard.h"
#include "menus/MenuAction.h"
#include "menus/ListMenuActions.h"
#include "control/KeyboardConfig.h"

KeyconfigMenu::KeyconfigMenu(Menu *parent) :
	Menu(parent)
{
	m_menu_actions.add_action_keyconfig("left", 1, gKeyboardConfig->getStringKey(k_left), k_left);
	m_menu_actions.add_action_keyconfig("right", 2, gKeyboardConfig->getStringKey(k_right), k_right);
	m_menu_actions.add_action_keyconfig("jump", 3, gKeyboardConfig->getStringKey(k_jump), k_jump);
	m_menu_actions.add_action_keyconfig("down", 4, gKeyboardConfig->getStringKey(k_down), k_down);
	m_menu_actions.add_action_keyconfig("fire", 5, gKeyboardConfig->getStringKey(k_fire), k_fire);
	m_menu_actions.add_action_keyconfig("prev_weapon", 6, gKeyboardConfig->getStringKey(k_next_weapon), k_next_weapon);
	m_menu_actions.add_action_keyconfig("next_weapon", 7, gKeyboardConfig->getStringKey(k_prev_weapon), k_prev_weapon);
	m_menu_actions.add_action_classic("Return", 8);
}

KeyconfigMenu::~KeyconfigMenu()
{
}

void KeyconfigMenu::update()
{
	Menu::update();
}

void KeyconfigMenu::treat_choice(int choice)
{
	switch(choice) {
		case 8: // return
			set_leave_menu_true();
			break;
		default:
			break;
	}
}


