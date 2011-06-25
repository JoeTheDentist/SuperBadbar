#ifndef _BABAR_OPTIONS_MENU_H
#define _BABAR_OPTIONS_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/ListMenuActions.h"


class OptionsMenu: public Menu {
	protected:



	public:
	OptionsMenu(Menu *parent = NULL);
	~OptionsMenu();
	virtual void update();

	protected:
	virtual void launch_keyconfig();
	virtual void treat_choice(int choice);
};


#endif
