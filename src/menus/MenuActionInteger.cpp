/**
 * 	@file MenuActionInteger.cpp
 * 	@brief Implementation de la classe MenuActionInteger
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "MenuActionInteger.h"
#include <sstream>
#include <control/EventKeyboard.h>

MenuActionInteger::MenuActionInteger(std::string str, int i, int val, int valmin, int valmax, int step):
	MenuAction(str, i),
	m_value(val),
	m_valmin(valmin),
	m_valmax(valmax),
	m_step(step)
{

}

void MenuActionInteger::incr_value(int value)
{
	m_value += m_step * value;
	if (m_value > m_valmax)
		m_value = m_valmax;
	if (m_value < m_valmin)
		m_value = m_valmin;
	update();
}

void MenuActionInteger::update_text()
{
	std::ostringstream oss;
	oss << m_text << " < " <<  m_value << " >";
	m_text_to_display = oss.str();
}

void MenuActionInteger::treatEvent(EventKeyboard *eventKeyboard)
{
	menu_key key = eventKeyboard->getMenuKey();
	switch (key) {
	case mk_left:
		incr_value(-1);
		eventKeyboard->markTreated();
		break;
	case mk_right:
		incr_value(1);
		eventKeyboard->markTreated();
		break;	
	default:
		break;
	}
}
