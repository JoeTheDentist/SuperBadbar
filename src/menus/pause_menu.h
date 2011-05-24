#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Pause_menu: public Menu {

	public:
	Pause_menu();
	~Pause_menu();
	
	protected:
	void launch_options();
	virtual void treat_choice(int choice);
};


#endif
