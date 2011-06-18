#include "menu_action.h"
#include "../video/surface_text.h"
#include "../param/param_menus.h"
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
	m_has_value(value!=-1),
	m_selected(false),
	m_size_sup(0)
{
	update();
}

Menu_action::~Menu_action()
{
	
}

void Menu_action::update()
{
	delete m_surface_text;
	delete m_surface_text_selected;
	if (m_size_sup > (MENU_TEXT_OFFSET_ATTENUATION - 1))
		m_size_sup -= MENU_TEXT_OFFSET_ATTENUATION;
	else if (m_size_sup < -(MENU_TEXT_OFFSET_ATTENUATION - 1))
		m_size_sup += MENU_TEXT_OFFSET_ATTENUATION;
	else
		m_size_sup = 0;
	if (!m_has_value){
		m_surface_text = new Surface_text(m_text, MENU_TEXT_SIZE + m_size_sup, MENU_TEXT_R, MENU_TEXT_G, MENU_TEXT_B);	
		m_surface_text_selected = new Surface_text(m_text, MENU_TEXT_SELECTED_SIZE + m_size_sup, MENU_TEXT_SELECTED_R,
				MENU_TEXT_SELECTED_G, MENU_TEXT_SELECTED_B);
	} else {
		std::ostringstream oss;
		oss << m_text << " < " <<  m_value << " >";
		m_surface_text = new Surface_text(oss.str(), MENU_TEXT_SIZE + m_size_sup, MENU_TEXT_R, MENU_TEXT_G, MENU_TEXT_B);	
		m_surface_text_selected = new Surface_text(oss.str(), MENU_TEXT_SELECTED_SIZE + m_size_sup,		
			MENU_TEXT_SELECTED_R, MENU_TEXT_SELECTED_G, MENU_TEXT_SELECTED_B);
		std::cout << oss.str() << std::endl;
	}
}

void Menu_action::select() 
{
	m_selected = true; 
	m_size_sup = MENU_TEXT_OFFSET_SIZE; 
	update();	
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
	update();
}

int Menu_action::width() 
{
	return get_surface()->w();
}

int Menu_action::height() 
{
	return get_surface()->h();
}
