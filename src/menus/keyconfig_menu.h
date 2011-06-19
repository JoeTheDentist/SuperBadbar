#ifndef _KEYCONFIG_MENU_H
#define _KEYCONFIG_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"


class Keyconfig_menu: public Menu {
	protected:


	
	public:
	Keyconfig_menu(Menu *parent = NULL);
	~Keyconfig_menu();
	virtual void update();
	
	protected:
	virtual void treat_choice(int choice);
};


#endif
