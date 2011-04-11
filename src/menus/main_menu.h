#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Main_menu: public Menu {
	protected:
	Surface *m_menu_background;
	Rect m_pos_background;


	
	public:
	Main_menu();
	~Main_menu();
	
	protected:
	virtual void refresh_screen();
	void launch_game();
	void launch_options();
	virtual bool treat_choice(int choice);
};


#endif
