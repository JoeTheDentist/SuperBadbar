#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Main_menu {
	private:
	Surface *m_menu_background;
	Rect m_pos_background;
	
	List_menu_actions m_menu_actions;
	Rect m_pos_menu;

	
	public:
	Main_menu();
	~Main_menu();
	void loop();
	
	private:
	void refresh_screen();
	void launch_game();
};


#endif
