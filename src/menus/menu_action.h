#ifndef _BABAR_MENU_ACTION_H_
#define _BABAR_MENU_ACTION_H_

#include <string>

class Surface_text;

class Menu_action {
	protected:
	Surface_text *m_surface_text;
	Surface_text *m_surface_text_selected;
	std::string m_text;
	std::string m_text_to_display;
	int m_index;

	bool m_selected;
	int m_size_sup; // valeur qu'on ajoute a la taille de la police en fonction des interactions
	
	public:
	Menu_action(std::string str, int i);
	
	~Menu_action();
	
	virtual void update();
	
	virtual int get_index() { return m_index; }
	
	virtual int get_value() {return 0;}
	
	virtual void select();

	virtual void deselect() {m_selected = false;}
	
	virtual Surface_text *get_surface(bool selected = false) 
	{
		return (m_selected ? m_surface_text_selected : m_surface_text);
	}
	
	virtual int width();
	
	virtual int height();
	
	virtual void incr_value(int value);
	
protected:
	virtual void update_text();
	virtual void update_pic(std::string str);
};


#endif
