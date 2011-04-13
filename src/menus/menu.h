#ifndef _BABAR_MENU_H
#define _BABAR_MENU_H

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"

class Surface_uniform;


class Menu {
	protected:	
	List_menu_actions m_menu_actions;
	Rect m_pos_menu;
	Menu *m_parent;

	
	public:
	Menu(Menu *parent = NULL);
	~Menu();
	virtual void loop();
	
	protected:
	virtual void refresh_screen(bool flip = true);
	virtual bool treat_choice(int choice) = 0;
};


#endif
