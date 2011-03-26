#ifndef _BABAR_MENU_H
#define _BABAR_MENU_H

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"

class Surface_uniform;


class Menu {
	protected:	
	List_menu_actions m_menu_actions;
	Rect m_pos_menu;

	
	public:
	Menu();
	~Menu();
	virtual void loop();
	
	protected:
	virtual void refresh_screen();
	virtual bool treat_choice(int choice) = 0;
};


#endif
