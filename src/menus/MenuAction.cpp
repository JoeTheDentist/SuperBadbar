#include "MenuAction.h"
#include "../video/SurfaceText.h"
#include "../param/param_menus.h"
#include <iostream>

MenuAction::MenuAction(std::string str, int i):
	m_surface_text(NULL),
	m_surface_text_selected(NULL),
	m_text(str),
	m_index(i),
	m_selected(false),
	m_size_sup(0)
{
	update();
}

MenuAction::~MenuAction()
{
	delete m_surface_text;
	delete m_surface_text_selected;
}

void MenuAction::update()
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

void MenuAction::select()
{
	m_selected = true;
	m_size_sup = MENU_TEXT_OFFSET_SIZE;
	update();
}

void MenuAction::incr_value(int value)
{
	
}

int MenuAction::width() const
{
	return get_surface()->w();
}

int MenuAction::height() const
{
	return get_surface()->h();
}

void MenuAction::update_text()
{
	m_text_to_display = m_text;
}

void MenuAction::update_pic(std::string str)
{
	delete m_surface_text;
	delete m_surface_text_selected;
	m_surface_text = new SurfaceText(str, MENU_TEXT_SIZE + m_size_sup, MENU_TEXT_R, MENU_TEXT_G, MENU_TEXT_B);
	m_surface_text_selected = new SurfaceText(str, MENU_TEXT_SELECTED_SIZE + m_size_sup, MENU_TEXT_SELECTED_R,
			MENU_TEXT_SELECTED_G, MENU_TEXT_SELECTED_B);
}

void MenuAction::treatEvent(EventKeyboard *eventKeyboard)
{
	
}

