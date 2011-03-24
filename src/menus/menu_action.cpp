#include "menu_action.h"
#include "../video/surface_text.h"


Menu_action::Menu_action(std::string str, int i):
	m_surface_text(new Surface_text(str)),
	m_surface_text_selected(new Surface_text(str, 30, 0, 0, 0)),
	m_index(i)
{
}

Menu_action::~Menu_action()
{
	
}
