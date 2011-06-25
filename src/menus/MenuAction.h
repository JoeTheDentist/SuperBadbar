#ifndef _BABAR_MENU_ACTION_H_
#define _BABAR_MENU_ACTION_H_

#include <string>

class SurfaceText;

class MenuAction {
	protected:
	SurfaceText *m_surface_text;
	SurfaceText *m_surface_text_selected;
	std::string m_text;
	std::string m_text_to_display;
	int m_index;

	bool m_selected;
	int m_size_sup; // valeur qu'on ajoute a la taille de la police en fonction des interactions

	public:
	MenuAction(std::string str, int i);

	~MenuAction();

	virtual void update();

	virtual int get_index() { return m_index; }

	virtual int get_value() {return 0;}

	virtual void select();

	virtual void deselect() {m_selected = false;}

	virtual SurfaceText *get_surface(bool selected = false)
	{
		return (m_selected ? m_surface_text_selected : m_surface_text);
	}

	virtual int width();

	virtual int height();

	virtual void incr_value(int value);

	virtual void enter_pressed() {}

	virtual std::string get_string() {return "";}

protected:
	virtual void update_text();
	virtual void update_pic(std::string str);
};


#endif
