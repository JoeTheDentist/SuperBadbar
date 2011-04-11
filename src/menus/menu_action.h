#ifndef _BABAR_MENU_ACTION_H_
#define _BABAR_MENU_ACTION_H_

#include <string>

class Surface_text;

class Menu_action {
	private:
	Surface_text *m_surface_text;
	Surface_text *m_surface_text_selected;
	std::string m_text;
	int m_index;
	int m_value;
	bool m_has_value;
	
	public:
	Menu_action(std::string str, int i, int val = -1);
	~Menu_action();
	
	int get_index() { return m_index; }
	
	
	Surface_text *get_surface(bool selected = false) 
	{
		return (selected ? m_surface_text_selected : m_surface_text);
	}
	
	virtual void incr_value(int value);
};


#endif
