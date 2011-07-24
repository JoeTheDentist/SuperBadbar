/**
 * 	@file MenuActionString.cpp
 * 	@brief Implementation de la classe MenuActionString
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "MenuActionString.h"
#include "../control/Keyboard.h"
#include "../util/globals.h"
#include <sstream>

MenuActionString::MenuActionString(std::string str, int i, std::string val):
	MenuAction(str, i),
	m_currentString(str + " : " + val),
	m_backupString(str + " : " + val),
	m_waitingForInput(false)
{
	
}

void MenuActionString::update_text()
{
	m_text_to_display = m_currentString.getString();
}

void MenuActionString::update()
{
	MenuAction::update();
	update_text();
}

std::string MenuActionString::get_string() const
{
	return m_currentString.getString();
}

void MenuActionString::treatEvent(EventKeyboard *eventKeyboard)
{
	if (!m_waitingForInput) {
		if (eventKeyboard->enterMenuPressed()) {
			m_waitingForInput = true;
			eventKeyboard->markTreated();
		}
	} else {
		if (eventKeyboard->keyPressed()) {
			if (eventKeyboard->enterPressed()) {
				m_waitingForInput = false;
			} else if (eventKeyboard->isMenuKey() && eventKeyboard->getMenuKey() == mk_escape) {
				m_waitingForInput = false;
			} else {
				m_currentString.treatEvent(*eventKeyboard);
			}
			eventKeyboard->markTreated();
		}
	}
}
