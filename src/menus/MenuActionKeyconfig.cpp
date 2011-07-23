/**
 * 	@file MenuActionKeyconfig.cpp
 * 	@brief Implementation de la classe MenuActionKeyconfig
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "MenuActionKeyconfig.h"
#include "../control/Keyboard.h"
#include "../control/KeyboardConfig.h"
#include "../util/globals.h"
#include <sstream>

MenuActionKeyconfig::MenuActionKeyconfig(std::string str, int i, std::string val, key k):
	MenuAction(str, i),
	m_value(val),
	m_key(k),
	m_waitingForInput(false)
{

}

// A ENLEVER
void MenuActionKeyconfig::change_value()
{
}

// s'en inspirer
void MenuActionKeyconfig::update()
{
	/*
	if (m_EventOrderer && m_EventOrderer->event_recieved()) {
		m_value = m_EventOrderer->get_string_event();
		gKeyboardConfig->setConfigKey(m_key, m_value);
		delete m_EventOrderer;
		m_EventOrderer = NULL;
	}*/
	MenuAction::update();
}

void MenuActionKeyconfig::update_text()
{
	std::ostringstream oss;
	oss << m_text << " < " <<  m_value << " >";
	m_text_to_display = oss.str();
}

std::string MenuActionKeyconfig::get_string() const
{
	return m_value;
}

void MenuActionKeyconfig::treatEvent(EventKeyboard *eventKeyboard)
{
	if (!m_waitingForInput) {
		if (eventKeyboard->isEnterPressed()) {
			m_waitingForInput = true;
			eventKeyboard->markTreated();
		}
	} else {
		if (eventKeyboard->keyPressed()) {
			m_value = eventKeyboard->getKeyString();
			gKeyboardConfig->setConfigKey(m_key, m_value);
			eventKeyboard->markTreated();
			m_waitingForInput = false;
		}
	}
}
