#include "menu_action.h"
#include "../video/surface_text.h"
#include <sstream>
#include <iostream>

Menu_action::Menu_action(std::string str, int i, int value, int valmin, int valmax):
	m_surface_text(NULL),
	m_surface_text_selected(NULL),
	m_text(str),
	m_index(i),
	m_value(value),
	m_valmin(valmin),
	m_valmax(valmax),
	m_has_value(value!=-1)	
{
	if (!m_has_value){
		m_surface_text = new Surface_text(m_text);
		m_surface_text_selected = new Surface_text(m_text, 30, 0, 0, 0);
	} else {
		std::ostringstream oss;
		oss << m_text << " < " <<  m_value << " >";
		m_surface_text = new Surface_text(oss.str());	
		m_surface_text_selected = new Surface_text(oss.str(), 30, 0, 0, 0);
		std::cout << oss.str() << std::endl;
	}
}

Menu_action::~Menu_action()
{
	
}

void Menu_action::incr_value(int value)
{
	m_value += value;
	if (m_value > m_valmax)
		m_value = m_valmax;
	if (m_value < m_valmin)
		m_value = m_valmin;
	delete m_surface_text;
	delete m_surface_text_selected;
	if (!m_has_value){
		m_surface_text = new Surface_text(m_text);
		m_surface_text_selected = new Surface_text(m_text, 30, 0, 0, 0);
	} else {
		std::ostringstream oss;
		oss << m_text << " < " <<  m_value << " >";
		m_surface_text = new Surface_text(oss.str());	
		m_surface_text_selected = new Surface_text(oss.str(), 30, 0, 0, 0);
	}	
}
