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
#include "../control/SdlKeyConverter.h"
#include "../util/globals.h"
#include <sstream>

MenuActionKeyconfig::MenuActionKeyconfig(std::string str, int i, std::string val, key k):
	MenuAction(str, i),
	m_value(val),
	m_key(k),
	m_waitingForInput(false)
{

}

void MenuActionKeyconfig::update_text()
{
	std::ostringstream oss;
	std::string value = m_value;
	oss << m_text << " < " <<  gKeyboardConfig->getStringKey(m_key) << " >";
	m_text_to_display = oss.str();
}

void MenuActionKeyconfig::update()
{
	MenuAction::update();
	update_text();
}

std::string MenuActionKeyconfig::get_string() const
{
	return m_value;
}

void MenuActionKeyconfig::treatEvent(EventKeyboard *eventKeyboard)
{
	if (!m_waitingForInput) {
		if (eventKeyboard->enterMenuPressed()) {
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
