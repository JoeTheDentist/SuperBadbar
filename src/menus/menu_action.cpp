#include "menu_action.h"
#include "../video/surface_text.h"
#include "../param/param_menus.h"
#include <iostream>

Menu_action::Menu_action(std::string str, int i):
	m_surface_text(NULL),
	m_surface_text_selected(NULL),
	m_text(str),
	m_index(i),
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
	if (m_size_sup > (MENU_TEXT_OFFSET_ATTENUATION - 1))
		m_size_sup -= MENU_TEXT_OFFSET_ATTENUATION;
	else if (m_size_sup < -(MENU_TEXT_OFFSET_ATTENUATION - 1))
		m_size_sup += MENU_TEXT_OFFSET_ATTENUATION;
	else
		m_size_sup = 0;
	update_text();
	update_pic(m_text_to_display);
}

void Menu_action::select() 
{
	m_selected = true; 
	m_size_sup = MENU_TEXT_OFFSET_SIZE; 
	update();	
}

void Menu_action::incr_value(int value)
{
}

int Menu_action::width() 
{
	return get_surface()->w();
}

int Menu_action::height() 
{
	return get_surface()->h();
}

void Menu_action::update_text()
{
	m_text_to_display = m_text;
}

void Menu_action::update_pic(std::string str)
{
	delete m_surface_text;
	delete m_surface_text_selected;
	m_surface_text = new Surface_text(str, MENU_TEXT_SIZE + m_size_sup, MENU_TEXT_R, MENU_TEXT_G, MENU_TEXT_B);	
	m_surface_text_selected = new Surface_text(str, MENU_TEXT_SELECTED_SIZE + m_size_sup, MENU_TEXT_SELECTED_R,
			MENU_TEXT_SELECTED_G, MENU_TEXT_SELECTED_B);	
}
