/**
 * 	@file MenuActionKeyconfig.cpp
 * 	@brief Implementation de la classe MenuActionKeyconfig
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "MenuActionKeyconfig.h"
#include "../control/EventOrderer.h"
#include "../control/Keyboard.h"
#include "../control/KeyboardConfig.h"
#include "../util/globals.h"
#include <sstream>

MenuActionKeyconfig::MenuActionKeyconfig(std::string str, int i, std::string val, key k):
	MenuAction(str, i),
	m_value(val),
	m_EventOrderer(NULL),
	m_key(k)
{

}

void MenuActionKeyconfig::change_value()
{
	m_EventOrderer = new EventOrderer();
	m_EventOrderer->order_event(gKeyboard);
}

void MenuActionKeyconfig::update()
{
	if (m_EventOrderer && m_EventOrderer->event_recieved()) {
		m_value = m_EventOrderer->get_string_event();
		gKeyboardConfig->setConfigKey(m_key, m_value);
		delete m_EventOrderer;
		m_EventOrderer = NULL;
	}
	MenuAction::update();
}

void MenuActionKeyconfig::update_text()
{
	std::ostringstream oss;
	oss << m_text << " < " <<  m_value << " >";
	m_text_to_display = oss.str();
}

void MenuActionKeyconfig::enter_pressed()
{
	change_value();
}

std::string MenuActionKeyconfig::get_string() const
{
	return m_value;
}
