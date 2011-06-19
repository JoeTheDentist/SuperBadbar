#include "keyconfig_menu.h"

#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../menus/menu_action.h"
#include "../menus/list_menu_actions.h"

Keyconfig_menu::Keyconfig_menu(Menu *parent) :
	Menu(parent)
{
	m_menu_actions.add_action_keyconfig("left", 1, gKeyboard->get_string_key(k_left), k_left);
	m_menu_actions.add_action_keyconfig("right", 2, gKeyboard->get_string_key(k_right), k_right);
	m_menu_actions.add_action_keyconfig("jump", 3, gKeyboard->get_string_key(k_jump), k_jump);
	m_menu_actions.add_action_keyconfig("down", 4, gKeyboard->get_string_key(k_down), k_down);
	m_menu_actions.add_action_keyconfig("fire", 5, gKeyboard->get_string_key(k_fire), k_fire);
	m_menu_actions.add_action_keyconfig("prev_weapon", 6, gKeyboard->get_string_key(k_next_weapon), k_next_weapon);
	m_menu_actions.add_action_keyconfig("next_weapon", 7, gKeyboard->get_string_key(k_prev_weapon), k_prev_weapon);
	m_menu_actions.add_action_classic("Return", 8);
}

Keyconfig_menu::~Keyconfig_menu()
{
}

void Keyconfig_menu::update()
{
	Menu::update();
}

void Keyconfig_menu::treat_choice(int choice)
{
	switch(choice) {
		case 8: // return
			set_leave_menu_true();
			break;
		default:
			break;
	}
}


