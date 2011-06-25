#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "../menus/menu.h"

#include "../video/surface.h"
#include "../menus/ListMenuActions.h"

class MainTitle;

class MainMenu: public Menu {
	protected:
	Surface *m_menu_background;
	Rect m_pos_background;
	MainTitle *m_main_title;


	public:
	MainMenu();
	~MainMenu();
	virtual void update_graphics();
	virtual bool can_display_grey_background() const {return false;}
	protected:
	void loop();
	void launch_game();
	void launch_options();
	virtual void treat_choice(int choice);
};


#endif
