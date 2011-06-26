#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

#include "../menus/Menu.h"

#include "../video/Surface.h"
#include "../menus/ListMenuActions.h"


class PauseMenu: public Menu {

	public:
	PauseMenu();
	~PauseMenu();

	protected:
	void launch_options();
	virtual void treat_choice(int choice);
};


#endif
