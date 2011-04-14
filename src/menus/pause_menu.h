#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Pause_menu: public Menu {

	public:
	Pause_menu(bool &leave);
	~Pause_menu();
	
	protected:
	bool &m_leave;
	virtual void refresh_screen(bool flip = true);
	void launch_options();
	virtual bool treat_choice(int choice);
};


#endif
