/**
 * 	@file menu_action_keyconfig.cpp
 * 	@brief Implementation de la classe Menu_action_keyconfig
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "menu_action_keyconfig.h"
#include "../control/event_orderer.h"
#include "../control/keyboard.h"
#include "../util/globals.h"
#include <sstream>

Menu_action_keyconfig::Menu_action_keyconfig(std::string str, int i, std::string val, key k):
	Menu_action(str, i),
	m_value(val),
	m_event_orderer(NULL),
	m_key(k)
{
	
}

void Menu_action_keyconfig::change_value()
{
	m_event_orderer = new Event_orderer();
	m_event_orderer->order_event(gKeyboard);
}

void Menu_action_keyconfig::update()
{
	if (m_event_orderer && m_event_orderer->event_recieved()) {
		m_value = m_event_orderer->get_string_event();
		gKeyboard->set_config_key(m_key, m_value);
		delete m_event_orderer;
		m_event_orderer = NULL;
	}
	Menu_action::update();
}

void Menu_action_keyconfig::update_text()
{
	std::ostringstream oss;
	oss << m_text << " < " <<  m_value << " >";	
	m_text_to_display = oss.str();
}

void Menu_action_keyconfig::enter_pressed()
{
	change_value();
}

std::string Menu_action_keyconfig::get_string()
{
	return m_value;
}
