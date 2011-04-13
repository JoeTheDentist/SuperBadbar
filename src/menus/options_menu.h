#ifndef _BABAR_OPTIONS_MENU_H
#define _BABAR_OPTIONS_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Options_menu: public Menu {
	protected:


	
	public:
	Options_menu(Menu *parent = NULL);
	~Options_menu();
	virtual void aux_loop();
	
	protected:
	virtual bool treat_choice(int choice);
};


#endif
