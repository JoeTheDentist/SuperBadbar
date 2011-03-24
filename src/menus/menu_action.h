#ifndef _BABAR_MENU_ACTION_H_
#define _BABAR_MENU_ACTION_H_

#include <string>

class Surface_text;

class Menu_action {
	private:
	Surface_text *m_surface_text;
	Surface_text *m_surface_text_selected;
	int m_index;
	
	public:
	Menu_action(std::string str, int i);
	~Menu_action();
	int get_index() { return m_index; }
	Surface_text *get_surface(bool selected = false) 
	{
		return (selected ? m_surface_text_selected : m_surface_text);
	}
};


#endif
