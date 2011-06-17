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
	int m_valmin;
	int m_valmax;
	bool m_has_value;
	bool m_selected;
	int m_size_sup; // valeur qu'on ajoute a la taille de la police en fonction des interactions
	
	public:
	Menu_action(std::string str, int i, int val = -1, int valmin = 0, int valmax = 99);
	~Menu_action();
	
	virtual void update();
	
	int get_index() { return m_index; }
	
	int get_value() {return m_value;}
	
	void select();

	void deselect() {m_selected = false;}
	
	Surface_text *get_surface(bool selected = false) 
	{
		return (m_selected ? m_surface_text_selected : m_surface_text);
	}
	
	int width();
	int height();
	
	virtual void incr_value(int value);
};


#endif
